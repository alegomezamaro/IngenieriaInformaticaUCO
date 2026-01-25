// ======================================================
// servidorP2.c
// Compilación: gcc -Wall -O2 -o servidorP2 servidorP2.c
// Ejecución: ./servidorP2
// ======================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdarg.h>

#define USER_DB_FILE "basedatos.txt"  // Fichero donde guardamos los usuarios
#define SERVER_PORT 1865              // Puerto indicado en el enunciado
#define MAX_CLIENTS 20                // Máximo de clientes conectados simultáneamente
#define MAX_GAMES   10                // Máximo de partidas simultáneas
#define MAX_MSG     200               // Longitud máxima de un comando


// ======================================================
// ESTADOS DEL CLIENTE
// ======================================================

typedef enum {
    ST_NEW = 0,      // Conectado pero sin autenticarse
    ST_USER_OK,      // Enviaron USUARIO, esperando PASSWORD
    ST_AUTHED,       // Autenticado correctamente
    ST_WAITING,      // Esperando rival
    ST_PLAYING,      // Jugando
    ST_PLANTED       // Se plantó en su partida
} ClState;


// ======================================================
// ESTRUCTURAS 
// ======================================================

typedef struct {
    char user[32];
    char pass[32];
    int used;
} User;

typedef struct {
    int in_use;
    int fd;
    struct sockaddr_in addr;
    char username[32];
    char pending_user[32];
    ClState state;
    int game_id;
    int total;
    int passes;
    int last_d1, last_d2;
} Client;

typedef struct {
    int in_use;
    int player_a;
    int player_b;
    int turn;
    int target;
    int someone_planted;
} Game;


// ======================================================
// VARIABLES GLOBALES
// ======================================================

static User users[64];
static Client clients[MAX_CLIENTS];
static Game games[MAX_GAMES];
static int waiting_queue = -1;


// ======================================================
// FUNCIONES AUXILIARES
// ======================================================

// Elimina saltos de línea al final de un mensaje
static void trim_newline(char *s){
    if(!s) return;
    size_t n=strlen(s);
    while(n>0 && (s[n-1]=='\n' || s[n-1]=='\r')) s[--n]='\0';
}

// Compara
static int starts_with(const char* s, const char* p){
    return strncmp(s,p,strlen(p))==0;
}

// Envío a un cliente
static int send_line(int fd, const char* fmt, ...){
    char buf[MAX_MSG+4];
    va_list ap; va_start(ap,fmt);
    vsnprintf(buf,sizeof(buf),fmt,ap);
    va_end(ap);
    size_t n=strlen(buf);

    if(n==0 || buf[n-1] != '\n'){
        buf[n]='\n';
        buf[n+1]='\0'; n++;
    }

    return (int)send(fd, buf, n, 0);
}


// ======================================================
// GESTIÓN DE USUARIOS
// ======================================================

// Busca un usuario existente
static int find_user(const char* u){
    for(int i=0;i<64;i++){
        if(users[i].used && strcmp(users[i].user,u)==0) return i;
    }
    return -1;
}

// Carga los usuarios guardados en el fichero
static void load_users_from_file(void) {
    FILE *f = fopen(USER_DB_FILE, "r");
    if (!f) return; // Si no existe sale

    char u[64], p[64];
    while (fscanf(f, "%63s %63s", u, p) == 2) {

        for (int i = 0; i < 64; i++) {

            if (!users[i].used) {
                users[i].used = 1;
                strncpy(users[i].user, u, 31);
                users[i].user[31] = '\0';
                strncpy(users[i].pass, p, 31);
                users[i].pass[31] = '\0';
                break;
            }
        }
    }
    fclose(f);
}

// Comprueba si un usuario ya está conectado
static void append_user_to_file(const char *u, const char *p) {
    FILE *f = fopen(USER_DB_FILE, "a");
    if (!f) return;
    fprintf(f, "%s %s\n", u, p);
    fclose(f);
}

//Registrar un usuario en el fichero base de datos
static int register_user(const char* u,const char* p){
    if (find_user(u) >= 0)
        return -1; // Usuario existente

    for (int i = 0; i < 64; i++) {
        if (!users[i].used) {
            users[i].used = 1;
            strncpy(users[i].user, u, 31); users[i].user[31] = '\0';
            strncpy(users[i].pass, p, 31); users[i].pass[31] = '\0';
            append_user_to_file(u, p);
            return 0;
        }
    }
    return -2;
}

// Valida usuario y contraseña
static int validate_user(const char* u,const char* p){
    int idx=find_user(u);
    if(idx<0) return 0;
    return strcmp(users[idx].pass,p)==0;
}

//Envio formateado a un cliente
static int is_user_logged_in(const char *u, int except_idx){
    for (int i = 0; i < MAX_CLIENTS; i++){
        if (!clients[i].in_use || i == except_idx) continue;
        if ((clients[i].state == ST_AUTHED ||
            clients[i].state == ST_WAITING ||
            clients[i].state == ST_PLAYING ||
            clients[i].state == ST_PLANTED) && strcmp(clients[i].username, u) == 0){
            return 1;
        }
    }
    return 0;
}

// ======================================================
// FUNCIONES DE PARTIDA
// ======================================================

// Devuelve el índice del indice del cliente rival
static int opponent_of(int game_id, int me){
    Game* g=&games[game_id];
    if(g->player_a==me) return g->player_b;
    else return g->player_a;
}

// Crea una nueva partida
static int create_game(int idx1, int idx2){
    for(int i=0;i<MAX_GAMES;i++)
        if(!games[i].in_use){
            games[i].in_use=1; games[i].player_a=idx1; games[i].player_b=idx2;
            games[i].target = 60 + rand()%141; // [60..200]
            games[i].someone_planted=0;
            games[i].turn = idx1;
            clients[idx1].state = ST_PLAYING;
            clients[idx2].state = ST_PLAYING;
            clients[idx1].game_id = clients[idx2].game_id = i;
            clients[idx1].total=clients[idx2].total=0;
            clients[idx1].passes=clients[idx2].passes=0;
            clients[idx1].last_d1=clients[idx1].last_d2=0;
            clients[idx2].last_d1=clients[idx2].last_d2=0;
            send_line(clients[idx1].fd,
                      "+Ok. Empieza la partida. NÚMERO OBJETIVO: [%d]. Te toca a ti.",
                      games[i].target);
            send_line(clients[idx2].fd,
                      "+Ok. Empieza la partida. NÚMERO OBJETIVO: [%d]. Espera tu turno.",
                      games[i].target);
        return i;
    }

    return -1; // no hay hueco
}

// Finaliza la partida
static void end_game(int game_id){
    if(game_id<0) return;
    Game* g=&games[game_id];
    if(!g->in_use) return;
    int a=g->player_a, b=g->player_b;

    if(a>=0 && clients[a].in_use){
        clients[a].game_id=-1; clients[a].state=ST_AUTHED;
    }

    if(b>=0 && clients[b].in_use){
        clients[b].game_id=-1;
        clients[b].state=ST_AUTHED;
    }

    g->in_use=0;
}

static void broadcast_game(int game_id, const char* msg){
    if(game_id<0) return;
    Game* g=&games[game_id];
    if(!g->in_use) return;
    int a=g->player_a, b=g->player_b;
    if(a>=0 && clients[a].in_use) send_line(clients[a].fd, "%s", msg);
    if(b>=0 && clients[b].in_use) send_line(clients[b].fd, "%s", msg);
}

// Decide el ganador de la partida
static void conclude_if_both_planted(int game_id){
    Game* g=&games[game_id];
    if(!g->in_use) return;
    int a=g->player_a, b=g->player_b; Client *A=&clients[a], *B=&clients[b];
    if((A->state==ST_PLANTED || A->total>=g->target) && (B->state==ST_PLANTED || B->total>=g->target)){
        int ta=A->total, tb=B->total, T=g->target;

        // Si ambos superan el numero no hay ganadores
        if(ta>T && tb>T){
            broadcast_game(game_id, "+Ok. No hay ganadores.");
            end_game(game_id); return;
        }

        // Empate exacto
        if(ta==tb){
            char msg[128];
            snprintf(msg,sizeof(msg), "+Ok. Jugador %s y Jugador %s habéis empatado la partida.", A->username, B->username);
            broadcast_game(game_id,msg);
            end_game(game_id);
            return;
        }

        // El más cercano sin pasarse
        int wa = (ta<=T) ? (T-ta) : 1000000; // distancia válida si no se pasa
        int wb = (tb<=T) ? (T-tb) : 1000000;
        int winner = (wa<wb)?a:b;
        char msg[128]; snprintf(msg,sizeof(msg), "+Ok. Jugador %s ha ganado la partida.", clients[winner].username);
        broadcast_game(game_id, msg); end_game(game_id); return;
    }
}


// ======================================================
// COMANDOS
// ======================================================

// Gestiona todos los comandos
static void handle_command(int idx, char *line){
    Client *C=&clients[idx]; trim_newline(line);
    if(strlen(line)==0) return;

    // REGISTRO –u <USUARIO> –p <PASSWORD>
    if(starts_with(line, "REGISTRO")){

        if (C->state != ST_NEW) {
            send_line(C->fd, "-Err. REGISTRO solo está disponible antes de autenticarse");
            return;
        }

        char u[64]={0}, p[64]={0};
        char *s=line;
        char *pu=strstr(s, "-u "); if(!pu) pu=strstr(s, "–u ");
        char *pp=strstr(s, "-p "); if(!pp) pp=strstr(s, "–p ");

        if(pu && pp){
            pu+=3; pp+=3;
            sscanf(pu, "%63s", u); sscanf(pp, "%63s", p);
            if(strlen(u)==0 || strlen(p)==0){ send_line(C->fd, "-Err. Formato REGISTRO incorrecto"); return; }
            int r=register_user(u,p);
            if(r==0) send_line(C->fd, "+Ok. Usuario registrado");
            else if(r==-1) send_line(C->fd, "-Err. Usuario ya existente");
            else send_line(C->fd, "-Err. Registro no disponible");
        } else{
            send_line(C->fd, "-Err. Formato REGISTRO incorrecto");
        }
        return;
    }

    // USUARIO <USUARIO>
    if (starts_with(line, "USUARIO ")){

        if (C->state != ST_NEW) {
            send_line(C->fd, "-Err. USUARIO no disponible tras autenticarse o en partida");
            return;
        }
        char u[32];

        if (sscanf(line+8, "%31s", u) == 1){

            if (find_user(u) < 0) {
                send_line(C->fd, "-Err. El usuario no existe. Use REGISTRO -u <usuario> -p <password>");
                C->pending_user[0] = '\0';
                C->state = ST_NEW;
                return;
            }
            strncpy(C->pending_user, u, 31);
            C->pending_user[31] = '\0';
            C->state = ST_USER_OK;
            send_line(C->fd, "+Ok. Usuario correcto");
        } else {
            send_line(C->fd, "-Err. Usuario incorrecto");
        }
        return;
    }


    // PASSWORD <PASSWORD>
    if (starts_with(line, "PASSWORD ")) {

    if (C->state != ST_USER_OK) {
        send_line(C->fd, "-Err. PASSWORD solo es válido tras USUARIO y antes de autenticarse");
        return;
    }

    char p[32];
    if (sscanf(line+9, "%31s", p) == 1) {

        if (strlen(C->pending_user) == 0) {
            send_line(C->fd, "-Err. Debe enviar USUARIO antes");
            C->state = ST_NEW;
            return;
        }

        if (is_user_logged_in(C->pending_user, idx)) {
            send_line(C->fd, "-Err. Usuario ya conectado desde otro cliente");
            C->pending_user[0] = '\0';
            C->state = ST_NEW;
            return;
        }

        if (validate_user(C->pending_user, p)) {
            strncpy(C->username, C->pending_user, sizeof(C->username));
            C->state = ST_AUTHED;
            send_line(C->fd, "+Ok. Usuario validado");
        } else {
            send_line(C->fd, "-Err. Error en la validación");
            C->pending_user[0] = '\0';
            C->state = ST_NEW;
        }

        } else {
            send_line(C->fd, "-Err. Formato PASSWORD incorrecto");
        }

        return;
    }

    // SALIR
    if (starts_with(line, "SALIR")) {

        if (waiting_queue == idx)
            waiting_queue = -1;

        if (C->state == ST_PLAYING || C->state == ST_PLANTED) {
            int gid = C->game_id;
            int opp = opponent_of(gid, idx);
            send_line(C->fd, "+Ok. Has salido de la partida.");

            if (opp >= 0 && clients[opp].in_use) {
                send_line(clients[opp].fd, "+Ok. Tu oponente ha salido. La partida ha terminado.");
                clients[opp].state = ST_AUTHED;
                clients[opp].game_id = -1;
                clients[opp].total = 0;
                clients[opp].passes = 0;
                clients[opp].last_d1 = clients[opp].last_d2 = 0;
            }

            end_game(gid);
            C->state = ST_AUTHED;
            C->game_id = -1;
            C->total = 0;
            C->passes = 0;
            C->last_d1 = C->last_d2 = 0;
            return;
        }
        send_line(C->fd, "+Ok. No estabas en partida.");
        return;
    }

    if(C->state==ST_NEW || C->state==ST_USER_OK){
        send_line(C->fd, "-Err. Debe autenticarse"); return;
    }

    // INICIAR-PARTIDA
    if(starts_with(line, "INICIAR-PARTIDA")){

        if(C->state!=ST_AUTHED && C->state!=ST_WAITING){
            send_line(C->fd, "-Err. No puede iniciar partida en este estado");
            return;
        }

        if(C->state==ST_PLAYING || C->state==ST_PLANTED){
            send_line(C->fd, "-Err. Ya está en una partida");
            return;
        }

        if(waiting_queue==-1){
            waiting_queue=idx;
            C->state=ST_WAITING;
            send_line(C->fd, "+Ok. Esperando otro jugador");
        }

        else if(waiting_queue==idx){
            send_line(C->fd, "+Ok. Ya está en cola. Esperando otro jugador");
        }

        else {
            int mate = waiting_queue;
            waiting_queue=-1;
            int g = create_game(mate, idx);
            if(g<0){
                send_line(C->fd, "-Err. No hay hueco para nuevas partidas");
                send_line(clients[mate].fd, "-Err. No hay hueco para nuevas partidas");
                clients[mate].state=ST_AUTHED;
            }
        }
        return;
    }

    if(!(C->state==ST_PLAYING || C->state==ST_PLANTED)){
        send_line(C->fd, "-Err. No está en una partida");
        return;
    }

    Game *G = &games[C->game_id];
    Client *O = &clients[opponent_of(C->game_id, idx)];

    // TIRAR-DADOS <NUMERO-DE-DADOS>
if (starts_with(line, "TIRAR-DADOS")) {
    if (G->turn != idx) {
        send_line(C->fd, "-Err. No es tu turno");
        return;
    }

    int nd = 0;
    sscanf(line+12, "%d", &nd);
    if (nd != 1 && nd != 2) {
        send_line(C->fd, "-Err. Debe indicar 1 o 2 dados");
        return;
    }

    if (C->state == ST_PLANTED) {
        send_line(C->fd, "-Err. Ya está plantado");
        return;
    }

    if (C->total >= G->target) {
        send_line(C->fd, "-Err. Excedido el valor de %d", G->target);
        return;
    }

    // Tiro de dados
    int d1 = 1 + rand()%6;
    int d2 = (nd == 2) ? (1 + rand()%6) : 0;
    int add = d1 + d2;

    C->last_d1 = d1;
    C->last_d2 = d2;
    C->total  += add;

    if (nd == 1)
        send_line(C->fd, "+Ok.[<DADO 1>,%d] TOTAL=%d Oponente:[%d,%d]",
                  d1, C->total, O->last_d1, O->last_d2);
    else
        send_line(C->fd, "+Ok.[<DADO 1>,%d; <DADO 2>,%d] TOTAL=%d Oponente:[%d,%d]",
                  d1, d2, C->total, O->last_d1, O->last_d2);

    if (C->total >= G->target && O->state == ST_PLANTED) {
        conclude_if_both_planted(C->game_id);
        return;
    }

    if (O->state == ST_PLANTED) {
        G->turn = idx;
        send_line(C->fd, "+Ok. Sigue tu turno. El rival ya está plantado.");
        return;
    }

    int next = (G->player_a == idx) ? G->player_b : G->player_a;
    G->turn = next;

    if (O && O->in_use)
        send_line(O->fd, "+Ok. Te toca a ti.");
    send_line(C->fd, "+Ok. Turno del rival.");
    return;
}

    // NO-TIRAR-DADOS
    if(starts_with(line, "NO-TIRAR-DADOS")){
        if (G->turn != idx) {
            send_line(C->fd, "-Err. No es tu turno");
            return;
        }
        if(C->state==ST_PLANTED){
            send_line(C->fd, "-Err. Ya está plantado");
            return;
        }
        if(C->passes>=3){
            send_line(C->fd, "-Err. Ya ha usado 3 NO-TIRAR-DADOS");
            return;
        }
        C->passes++;
        send_line(C->fd, "+Ok. Pasa turno (%d/3). Oponente:[%d,%d] TOTAL=%d", C->passes, O->last_d1, O->last_d2, C->total);
        int next = (G->player_a == idx) ? G->player_b : G->player_a;
        G->turn = next;
        if (O && O->in_use)
            send_line(O->fd, "+Ok. Te toca a ti.");
        send_line(C->fd, "+Ok. Turno del rival.");
        return;
    }

    // PLANTARME
    if(starts_with(line, "PLANTARME")){
        if (G->turn != idx) {
            send_line(C->fd, "-Err. No es tu turno");
            return;
        }
        if(C->state==ST_PLANTED){ send_line(C->fd, "+Ok. Ya estaba plantado. Esperando que finalice el otro jugador."); return; }
        C->state=ST_PLANTED;
        if(!G->someone_planted){
            G->someone_planted=1;
            // El otro jugador solo puede plantarse
            send_line(C->fd, "+Ok. Esperando que finalice el otro jugador.");
            send_line(O->fd, "+Ok. El oponente se ha plantado. Solo puede usar PLANTARME.");
        }else{
            // Segundo en plantarse
            conclude_if_both_planted(C->game_id);
            return;
        }
        int next = (G->player_a == idx) ? G->player_b : G->player_a;
        G->turn = next;
        if (O && O->in_use)
            send_line(O->fd, "+Ok. Te toca a ti.");
        send_line(C->fd, "+Ok. Turno del rival.");
        return;
    }
    send_line(C->fd, "-Err. Comando no reconocido");
}


// ======================================================
// ACEPTAR NUEVO CLIENTE
// ======================================================

static void accept_new(int server_fd, fd_set *allset, int *maxfd){
    struct sockaddr_in cli; socklen_t clen=sizeof(cli);
    int cfd = accept(server_fd, (struct sockaddr*)&cli, &clen);
    if(cfd<0){ perror("accept"); return; }
    int slot=-1;
    for(int i=0;i<MAX_CLIENTS;i++) if(!clients[i].in_use){
        slot=i;
        break;
    }
    if(slot<0){
        const char* msg="-Err. Servidor lleno\n";
        send(cfd,msg,strlen(msg),0);
        close(cfd);
        return;
    }
    clients[slot].in_use=1;
    clients[slot].fd=cfd;
    clients[slot].addr=cli;
    clients[slot].state=ST_NEW;
    clients[slot].game_id=-1;
    clients[slot].total=0;
    clients[slot].passes=0;
    clients[slot].last_d1=clients[slot].last_d2=0;
    clients[slot].username[0]=clients[slot].pending_user[0]=0;
    FD_SET(cfd, allset);
    if(cfd>*maxfd) *maxfd=cfd;
    send_line(cfd, "+Ok. Usuario conectado");
}


// ======================================================
// MAIN
// ======================================================

int main(void){
    srand((unsigned)time(NULL));
    memset(clients, 0, sizeof(clients));
    memset(games, 0, sizeof(games));
    waiting_queue = -1;
    load_users_from_file();
    int s = socket(AF_INET, SOCK_STREAM, 0); 
    if(s<0){ perror("socket"); return 1; }
    int opt=1; 
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in srv; 
    memset(&srv,0,sizeof(srv));
    srv.sin_family=AF_INET; 
    srv.sin_port=htons(SERVER_PORT); 
    srv.sin_addr.s_addr=INADDR_ANY;
    if(bind(s,(struct sockaddr*)&srv,sizeof(srv))<0){ perror("bind"); return 1; }
    if(listen(s, 10)<0){ perror("listen"); return 1; }
    fd_set allset, rset; 
    FD_ZERO(&allset); 
    FD_SET(s,&allset); 
    int maxfd=s;

    // Esperamos actividad en el socket en servidor o clientes
    for(;;){
        rset=allset; 
        int nready=select(maxfd+1,&rset,NULL,NULL,NULL); 
        if(nready<0){ 
            if(errno==EINTR) continue; 
            perror("select"); 
            break; 
        }

        // ¿Hay nuevas conexiones?
        if(FD_ISSET(s,&rset)){
            accept_new(s,&allset,&maxfd); 
            if(--nready<=0) continue;
        }

        // Recorremos todos los clientes buscando datos
        for(int i=0;i<MAX_CLIENTS;i++) if(clients[i].in_use){
            int fd=clients[i].fd; 
            if(FD_ISSET(fd,&rset)){
                char buf[MAX_MSG+1]; 
                int n=recv(fd,buf,MAX_MSG,0);
                if(n<=0){ // El cliente se ha desconectado
                    if(waiting_queue==i) waiting_queue=-1;
                    if(clients[i].state==ST_PLAYING || clients[i].state==ST_PLANTED){ // Avisamos al rival y cerramos partida
                        int gid=clients[i].game_id; 
                        int opp = opponent_of(gid, i);
                        if(opp>=0 && clients[opp].in_use) 
                            send_line(clients[opp].fd, "+Ok. Tu oponente ha terminado la partida");
                        end_game(gid);
                    }
                    close(fd); 
                    FD_CLR(fd,&allset); 
                    clients[i].in_use=0; 
                    continue;
                }
                buf[n]='\0';
                char *saveptr=NULL; 
                char *tok=strtok_r(buf,"\n",&saveptr);
                while(tok){ 
                    char line[MAX_MSG+1]; 
                    strncpy(line,tok,MAX_MSG); 
                    line[MAX_MSG]='\0'; 
                    handle_command(i,line); 
                    tok=strtok_r(NULL,"\n",&saveptr);
                }            
            }
        }
    }

    close(s); 
    return 0;
}




