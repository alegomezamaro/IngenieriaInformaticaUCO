#include "funciones.h"

void salirCliente(int socket, fd_set *readfds, int *numClientes, struct cliente *listaclientes, partida **listapartidas, int *partidas)
{
    char buffer[250];
    int i, j;

    // Cerrar el socket del cliente que sale
    close(socket);

    // Eliminar el socket del conjunto de descriptores de lectura (readfds)
    FD_CLR(socket, readfds);

    struct cliente *clienteDesconectado = nullptr;
    struct partida *partidaActual = nullptr;

    // Buscar la posición del cliente en el array de clientes
    for (i = 0; i < *numClientes; i++)
    {
        if (listaclientes[i].sd == socket)
        {
            clienteDesconectado = &listaclientes[i];
            break; // Encontrado el cliente a eliminar
        }
    }

    // Comprobar si el cliente desconectado está en alguna partida
    for (int k = 0; k < *partidas; k++)
    {
        if (listapartidas[k]->jugador1->sd == socket || listapartidas[k]->jugador2->sd == socket)
        {
            partidaActual = listapartidas[k];
            break; // Partida encontrada
        }
    }

    // Si el jugador estaba en una partida, notificar al adversario y cerrar la partida
    if (partidaActual != nullptr)
    {
        struct cliente *adversario;

        // Identificar al adversario
        if (partidaActual->jugador1->sd == socket)
        {
            adversario = partidaActual->jugador2;
        }
        else
        {
            adversario = partidaActual->jugador1;
        }

        // Notificar al adversario que su oponente se ha desconectado
        bzero(buffer, sizeof(buffer));
        sprintf(buffer, "El oponente se ha desconectado. La partida ha sido terminada.\n");

        // Asegurarse de que el adversario sigue conectado antes de enviar el mensaje
        if (FD_ISSET(adversario->sd, readfds))
        {
            send(adversario->sd, buffer, strlen(buffer), 0);
        }

        // Finalizar la partida y liberar los recursos
        finalizarPartida(listapartidas, *partidas, partidaActual, clienteDesconectado, adversario);
    }

    // Desplazar los elementos restantes del array de clientes hacia atrás
    for (j = i; j < (*numClientes) - 1; j++)
    {
        listaclientes[j] = listaclientes[j + 1]; // Sobrescribir el cliente eliminado
    }

    // Reducir el número de clientes
    (*numClientes)--;

    // Preparar el mensaje de desconexión
    bzero(buffer, sizeof(buffer));
    sprintf(buffer, "Desconexión del cliente <%d>", socket);

    // Notificar a todos los clientes restantes sobre la desconexión
    for (i = 0; i < *numClientes; i++)
    {
        if (listaclientes[i].sd != socket && listaclientes[i].estado == 1)
        {                                                         // Evitar enviar el mensaje al socket cerrado
            send(listaclientes[i].sd, buffer, strlen(buffer), 0); // Usar strlen para evitar enviar el buffer completo
        }
    }
}

void manejador(int signum)
{
    printf("\nSe ha recibido la señal sigint\n");
    signal(SIGINT, manejador);

    // Implementar lo que se desee realizar cuando ocurra la excepciÃ³n de ctrl+c en el servidor
}

// FUNCION PARA COMPROBAR SI EL NOMBRE SE ENCUENTRA EN EL FICHERO

bool comprobarfiche(char *nombrefiche, char *nombresesion)
{
    FILE *file = fopen(nombrefiche, "r");
    char line[MSG_SIZE];
    int found = 0;

    if (file == NULL)
    {
        printf("El fichero no existe. \n");
        return false;
    }

    // Leer lÃ­nea por lÃ­nea para comprobar si el nombre de sesiÃ³n estÃ¡ en el archivo
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Eliminar el salto de lÃ­nea de la lÃ­nea leÃ­da
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }

        // Separar el nombre de usuario y la contraseña (antes del primer espacio)
        // char *usuario = strtok(line, " ");
        char usuario1[100];
        char password1[100];
        sscanf(line, "%s %s", usuario1, password1);
        printf("%s\n", usuario1);

        // Comprobar si el nombre coincide con alguna lÃ­nea en el archivo
        if (strcmp(usuario1, nombresesion) == 0)
        {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found)
    {
        printf("El usuario %s existe en el fichero.\n", nombresesion);
        return true;
    }
    else
    {
        printf("El usuario %s no estÃ¡ en el fichero.\n", nombresesion);
        return false;
    }
}

bool comprobarfiche_contrasena(char *nombrefiche, char *usuario_input, char *contrasena_input)
{
    FILE *file = fopen(nombrefiche, "r");
    char line[MSG_SIZE];
    int found = 0;

    if (file == NULL)
    {
        printf("El fichero no existe.\n");
        return false;
    }

    // Leer línea por línea para comprobar si el usuario y la contraseña coinciden
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Eliminar el salto de línea de la línea leída
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }

        // Separar el nombre de usuario y la contraseña (después del primer espacio)
        char *usuario = strtok(line, " ");
        char *pass = strtok(NULL, " ");

        // Comprobar si el nombre de usuario y la contraseña coinciden
        if (usuario != NULL && pass != NULL && strcmp(usuario, usuario_input) == 0 && strcmp(pass, contrasena_input) == 0)
        {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found)
    {
        printf("El usuario y la contraseña coinciden.\n");
        return true;
    }
    else
    {
        printf("El usuario o la contraseña no coinciden.\n");
        return false;
    }
}


char *registrar(char *nombrefiche, char *nombre, char *contraseña)
{
    char *salida = (char *)malloc(150 * sizeof(char)); 
    FILE *file;

    // Comprobar si el nombre tiene espacios
    if (strchr(nombre, ' ') != NULL)
    {
        strcpy(salida, "El nombre de usuario no puede contener espacios.\n");
        printf("%s", salida);
        return salida;
    }

    // Comprobar si el usuario ya está registrado
    if (comprobarfiche(nombrefiche, nombre) == true)
    {
        strcpy(salida, "Usuario ya registrado. Pruebe con otro nombre de usuario\n");
        printf("%s", salida);
        return salida;
    }

    // Comprobar si la contraseña tiene espacios
    if (strchr(contraseña, ' ') != NULL)
    {
        strcpy(salida, "La contraseña no puede contener espacios.\n");
        printf("%s", salida);
        return salida;
    }

    // Abrir el archivo en modo lectura y escritura ("r+")
    file = fopen(nombrefiche, "r+");
    if (file == NULL)
    {
        // Si no existe el archivo, crearlo en modo "w" y abrirlo en modo "a"
        file = fopen(nombrefiche, "a");
        if (file == NULL)
        {
            strcpy(salida, "Error al abrir el fichero para escritura.\n");
            printf("%s", salida);
            return salida;
        }
    }
    else
    {
        // Posicionar el puntero del archivo al final
        fseek(file, 0, SEEK_END);

        // Revisar si el archivo termina con un salto de línea
        long fileSize = ftell(file);
        if (fileSize > 0)
        {
            fseek(file, -1, SEEK_END);
            char lastChar;
            fread(&lastChar, 1, 1, file);

            // Si el último carácter no es un salto de línea, añadir uno
            if (lastChar != '\n')
            {
                fprintf(file, "\n");
            }
        }
    }

    // Escribir el nombre de usuario y la contraseña
    fprintf(file, "%s %s", nombre, contraseña);
    fclose(file);

    strcpy(salida, "Usuario y contraseña registrados correctamente.\n");
    printf("%s", salida);
    return salida;
}

struct cliente crearcliente(int sd)
{
    //

    // creamos un aux del cliente nuevo para asignarle su sd y no perderlo en la concurrencia con lo demas
    struct cliente nuevo;

    // le asignamos su sd
    nuevo.sd = sd;

    // le ponemos su estado a 0 que significa que esta dentro del sistema
    nuevo.estado = 0;

    printf("Se ha añadido el cliente con el socket %d \n", sd);
    return nuevo;
}

struct cliente *reservarmemoriajugador()
{
    struct cliente *aux = (struct cliente *)malloc(MAX_CLIENTS * sizeof(struct cliente));
    if (aux == NULL)
    {
        printf("Error a la hora de reservar memoria.\n");
        return NULL;
    }
    return aux;
}

struct partida *rspartida()
{
    struct partida *aux = (struct partida *)malloc(MAX_PARTIDA * sizeof(struct partida));
    if (aux == NULL)
    {
        printf("Error a la hora de reservar memoria.\n");
        return NULL;
    }
    return aux;
}

void anadircliente(struct cliente *listaclientes, int numClientes, struct cliente nuevo)
{
    if (numClientes < MAX_CLIENTS)
    {
        listaclientes[numClientes] = nuevo;
    }
    else
    {
        printf("Limite de clientes alcanzado"); // creo que esto lo podemos quitar pero la verdad que no estoy nada seguro
    }
}

struct cliente *bcliente(struct cliente *array, int n, int sd)
{
    struct cliente *aux;

    for (int i = 0; i < n; i++)
    {
        if (array[i].sd == sd)
        {
            return &array[i];
        }
    }

    return NULL;
}

struct cliente *actualizarcliente(struct cliente *listaclientes, int numClientes, struct cliente *actualizado)
{
    for (int i = 0; i < numClientes; i++)
    {
        if (listaclientes[i].sd == actualizado->sd)
        {                                    // compara con el socket del cliente actualizado
            listaclientes[i] = *actualizado; // desreferencia para copiar los datos al cliente en la lista
            break;
        }
    }
    return actualizado;
}

/*
void actualizarnombrecliente(struct cliente *listaclientes, int numClientes, int sd, char *nombre, char *contrasena) {
    for (int i = 0; i < numClientes; i++) {
        if (listaclientes[i].sd == sd) {  // Find the client by their socket descriptor
            // Update the name and password
            strcpy(listaclientes[i].nombre, nombre);
            strcpy(listaclientes[i].contraseña, contrasena);
            printf("Cliente con sd %d actualizado con nuevo nombre: %s y nueva contraseña: %s\n", sd, nombre, contrasena);
            return;
        }
    }
    printf("Cliente con sd %d no encontrado.\n", sd); // Error if the client is not found
}
*/

struct cliente *buscarcontringante(struct cliente *listaclientes, int numClientes)
{
    for (int i = 0; i < numClientes; i++)
    {
        if (listaclientes[i].estado == 2)
        {
            return &listaclientes[i];
        }
    }
    return NULL;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/

// Generar una carta aleatoria
struct carta generarCartaAleatoria()
{
    std::string numeros[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    std::string palos[] = {"Corazones", "Diamantes", "Tréboles", "Picas"};

    int numIndex = rand() % 13;
    int paloIndex = rand() % 4;

    struct carta nuevaCarta;
    nuevaCarta.valor = numeros[numIndex];
    nuevaCarta.palo = palos[paloIndex];
    return nuevaCarta;
}

// Obtener el valor de una carta en puntos
int obtenerValorCarta(const std::string &valor)
{
    if (valor == "J" || valor == "Q" || valor == "K")
        return 10;
    if (valor == "A")
        return 11;
    return std::stoi(valor); // Convertir los números "2" a "10" a enteros
}

// Buscar y eliminar una carta del vector
bool buscarYEliminarCarta(std::vector<struct carta> &cartas, const std::string &paloCartaBuscada, std::string valorCartaBuscada)
{
    bool encontrada = false;

    // Iteramos sobre el vector de cartas
    for (auto it = cartas.begin(); it != cartas.end(); ++it)
    {
        if (it->palo == paloCartaBuscada && it->valor == valorCartaBuscada)
        {
            // Si encontramos la carta, la eliminamos del vector
            cartas.erase(it);
            encontrada = true;
            break; // Salimos del bucle ya que hemos eliminado la carta
        }
    }

    return encontrada; // Retornamos si la carta fue encontrada o no
}

// Sacar una carta válida (que esté en el mazo)
struct carta sacar_carta(std::vector<struct carta> &cartas)
{
    struct carta cartaGenerada;
    bool cartaEncontrada = false;

    // Generar cartas hasta que se encuentre una que esté en el archivo
    while (!cartaEncontrada)
    {
        cartaGenerada = generarCartaAleatoria();
        cartaEncontrada = buscarYEliminarCarta(cartas, cartaGenerada.palo, cartaGenerada.valor);
    }

    return cartaGenerada;
}

// Asignar una carta a un jugador
struct carta asignarCarta(std::vector<struct carta> &cartas, struct cliente *jugador)
{
    struct carta nuevaCarta = sacar_carta(cartas); // Corregido para llamar a sacar_carta correctamente
    jugador->mazo.push_back(nuevaCarta);           // push_back es el método correcto para agregar una carta al vector
    return nuevaCarta;
}

// Función auxiliar para asignar cartas y notificar al jugador y a su oponente
void asignarCartasYNotificar(std::vector<carta> &mazo, struct cliente *jugador1, struct cliente *jugador2)
{
    // Asignar dos cartas a jugador1
    carta carta1 = asignarCarta(mazo, jugador1);
    carta carta2 = asignarCarta(mazo, jugador1);

    // Asignar dos cartas a jugador2
    carta carta3 = asignarCarta(mazo, jugador2);
    carta carta4 = asignarCarta(mazo, jugador2);

    char buffer[256];

    // Notificar a jugador1 sus cartas y las cartas de jugador2
    bzero(buffer, sizeof(buffer));
    sprintf(buffer, "+Ok. Empieza la partida. TUS-CARTAS:[%s,%s][%s,%s]. OPONENTE:[%s,%s]\n",
            carta1.palo.c_str(), carta1.valor.c_str(),
            carta2.palo.c_str(), carta2.valor.c_str(),
            carta3.palo.c_str(), carta3.valor.c_str());
    send(jugador1->sd, buffer, strlen(buffer), 0);

    // Notificar a jugador2 sus cartas y las cartas de jugador1
    bzero(buffer, sizeof(buffer));
    sprintf(buffer, "+Ok. Empieza la partida. TUS-CARTAS:[%s,%s][%s,%s]. OPONENTE:[%s,%s]\n",
            carta3.palo.c_str(), carta3.valor.c_str(),
            carta4.palo.c_str(), carta4.valor.c_str(),
            carta1.palo.c_str(), carta1.valor.c_str());
    send(jugador2->sd, buffer, strlen(buffer), 0);
}

// Función auxiliar para iniciar el turno de un jugador
void iniciarTurno(struct cliente *jugador)
{
    char buffer[256];
    bzero(buffer, sizeof(buffer));
    sprintf(buffer, "Es tu turno, jugador %d.\n", jugador->sd);
    send(jugador->sd, buffer, strlen(buffer), 0);
}

int calcularValorTotal(const std::vector<carta> &mazo)
{
    int total = 0;
    int ases = 0;

    // Iterar sobre todas las cartas del mazo
    for (const auto &c : mazo)
    {
        // Convertir el valor de la carta (string) a un valor numérico
        if (c.valor == "J" || c.valor == "Q" || c.valor == "K")
        {
            // Las figuras (J, Q, K) valen 10 puntos
            total += 10;
        }
        else if (c.valor == "A")
        {
            // Los Ases inicialmente valen 11 puntos
            total += 11;
            ases++; // Llevar la cuenta de los Ases
        }
        else
        {
            // Para las cartas numéricas (2-10), convertimos el valor de string a entero
            total += std::stoi(c.valor);
        }
    }

    // Ajustar el valor de los Ases si el total supera los 21 puntos
    while (total > 21 && ases > 0)
    {
        total -= 10; // Convertir un As de 11 a 1
        ases--;
    }

    return total;
}

// Función que verifica si la partida debe continuar o finalizar
bool partidaContinua(struct cliente *actual, struct cliente *adversario, struct cliente *listaclientes, int numClientes)
{
    bool actu = false;
    bool adver = false;
    char buffer[250];

    // Revisar si los jugadores siguen conectados
    for (int i = 0; i < numClientes; i++)
    {
        if (listaclientes[i].sd == actual->sd)
        {
            actu = true; // Jugador 1 sigue activo
        }
        if (listaclientes[i].sd == adversario->sd)
        {
            adver = true; // Jugador 2 sigue activo
        }
    }

    // Si alguno de los jugadores no está activo, finalizar la partida
    if (!actu || !adver)
    {
        if (actu)
        {
            // Si el jugador 1 sigue activo, notificarle que la partida termina porque el jugador 2 se desconectó
            sprintf(buffer, "El jugador 2 ha salido. La partida ha terminado.");
            send(actual->sd, buffer, strlen(buffer), 0);
        }
        else if (adver)
        {
            // Si el jugador 2 sigue activo, notificarle que la partida termina porque el jugador 1 se desconectó
            sprintf(buffer, "El jugador 1 ha salido. La partida ha terminado.");
            send(adversario->sd, buffer, strlen(buffer), 0);
        }

        return false;
    }

    return true;
}

std::vector<carta> inicializarMazo(const std::string &nombreFichero)
{
    std::vector<carta> mazo;              // Vector para almacenar las cartas
    std::ifstream fichero(nombreFichero); // Abrir el fichero

    if (!fichero.is_open())
    {
        std::cerr << "Error: No se pudo abrir el fichero " << nombreFichero << std::endl;
        exit(EXIT_FAILURE); // Salir si no se puede abrir el fichero
    }

    std::string linea;
    while (std::getline(fichero, linea))
    {
        std::istringstream iss(linea);
        carta nuevaCarta;
        std::string palabraIntermedia;

        // Leer el tipo y el palo de la carta
        if (iss >> nuevaCarta.valor >> palabraIntermedia >> nuevaCarta.palo)
        {
            // Añadir la carta al mazo si se leyó correctamente
            mazo.push_back(nuevaCarta);
        }
        else
        {
            std::cerr << "Error al leer la línea: " << linea << std::endl;
        }
    }

    fichero.close(); // Cerrar el fichero

    return mazo; // Devolver el mazo
}

void finalizarPartida(partida **listapartidas, int &partidas, partida *partidaActual, struct cliente *actual, struct cliente *adversario)
{
    if (partidas <= 0)
    {
        std::cerr << "Error: No hay partidas activas para finalizar." << std::endl;
        return;
    }

    // Vaciar el vector de cartas de ambos jugadores
    actual->mazo.clear();     // Vacia el mazo del jugador actual
    adversario->mazo.clear(); // Vacia el mazo del adversario

    // Restablecer el estado de ambos jugadores
    actual->estado = 1;     // Cliente desconectado vuelve al estado inicial
    adversario->estado = 1; // Adversario también vuelve al estado inicial, en espera de una nueva partida

    // Buscar la partida actual y eliminarla
    for (int i = 0; i < partidas; i++)
    {
        if (listapartidas[i] == partidaActual)
        {
            // Liberar memoria de la partida actual
            delete listapartidas[i]; // Usamos delete ya que fue creada con new, no free
            listapartidas[i] = nullptr;

            // Reorganizar el array de partidas eliminando el hueco
            for (int j = i; j < partidas - 1; j++)
            {
                listapartidas[j] = listapartidas[j + 1];
            }

            // Actualizar el número de partidas activas
            partidas--;

            std::cout << "Partida finalizada y eliminada correctamente." << std::endl;
            return;
        }
    }

    std::cerr << "Error: La partida no se encontró en la lista de partidas activas." << std::endl;
}

bool comprobarlog(struct cliente * listaclientes, char* nombre, int numClientes){
    for(int i=0; i<numClientes; i++){
        if(listaclientes[i].nombre==nombre){
            return false;
        }
    }
    return true;
}