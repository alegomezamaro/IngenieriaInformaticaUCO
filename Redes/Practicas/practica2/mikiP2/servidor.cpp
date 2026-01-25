#include "funciones.h"

int main()
{

    /*----------------------------------------------------
        Descriptor del socket y buffer de datos
    -----------------------------------------------------*/
    int sd, new_sd;
    struct sockaddr_in sockname, from;
    char buffer[MSG_SIZE];
    socklen_t from_len;
    fd_set readfds, auxfds;
    int salida;
    // int arrayClientes[MAX_CLIENTS]; //con la lista de cliente que hemos creado abajo podemos quitar esto de todo el codigo, preguntar a amelia
    int numClientes = 0;
    // contadores
    int i, j, k;
    int recibidos;
    char identificador[250];
    char bufferaux[MSG_SIZE];

    // para llevar una cuenta del numero de partidas que hay iniciadas
    int partidas = 0;

    struct cliente *listaclientes = reservarmemoriajugador();
    struct partida **listapartidas = (struct partida **)malloc(10 * sizeof(struct partida *));

    int on, ret;

    /* --------------------------------------------------
        Se abre el socket
    ---------------------------------------------------*/
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1)
    {
        perror("No se puede abrir el socket cliente\n");
        exit(1);
    }

    // Activaremos una propiedad del socket para permitirÂ· que otros
    // sockets puedan reutilizar cualquier puerto al que nos enlacemos.
    // Esto permiteÂ· en protocolos como el TCP, poder ejecutar un
    // mismo programa varias veces seguidas y enlazarlo siempre al
    // mismo puerto. De lo contrario habrÃŒa que esperar a que el puerto
    // quedase disponible (TIME_WAIT en el caso de TCP)
    on = 1;
    ret = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    sockname.sin_family = AF_INET;
    sockname.sin_port = htons(2000);
    sockname.sin_addr.s_addr = INADDR_ANY;

    if (bind(sd, (struct sockaddr *)&sockname, sizeof(sockname)) == -1)
    {
        perror("Error en la operación bind");
        exit(1);
    }

    /*---------------------------------------------------------------------
        Del las peticiones que vamos a aceptar sÃ³lo necesitamos el
        tamaño de su estructura, el resto de informaciÃ³n (familia, puerto,
        ip), nos la proporcionarÃ¡ el mÃ©todo que recibe las peticiones.
    ----------------------------------------------------------------------*/
    from_len = sizeof(from);

    if (listen(sd, 1) == -1)
    {
        perror("Error en la operación de listen");
        exit(1);
    }

    printf("El servidor está esperando conexiones...\n"); // Inicializar los conjuntos fd_set

    FD_ZERO(&readfds);
    FD_ZERO(&auxfds);
    FD_SET(sd, &readfds);
    FD_SET(0, &readfds);

    // Capturamos la señal SIGINT (Ctrl+c)
    signal(SIGINT, manejador);

    /*-----------------------------------------------------------------------
        El servidor acepta una petición
    ------------------------------------------------------------------------ */
    while (1)
    {

        // Esperamos recibir mensajes de los clientes (nuevas conexiones o mensajes de los clientes ya conectados)

        auxfds = readfds;

        salida = select(FD_SETSIZE, &auxfds, NULL, NULL, NULL);

        if (salida > 0)
        {

            for (i = 0; i < FD_SETSIZE; i++)
            {

                // Buscamos el socket por el que se ha establecido la comunicaciÃ³n
                if (FD_ISSET(i, &auxfds))
                {

                    if (i == sd)
                    {

                        if ((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1)
                        {
                            perror("Error aceptando peticiones");
                        }
                        else
                        {
                            if (numClientes < MAX_CLIENTS)
                            {
                                // esto creo que no nos hace falta pero bueno lo podemos usar igualmente
                                listaclientes[numClientes].sd = new_sd;

                                struct cliente nuevo = crearcliente(new_sd);
                                anadircliente(listaclientes, numClientes, nuevo);
                                numClientes++;

                                strcpy(buffer, "+0k. Usuario conectado\n\n");
                                strcat(buffer, "========================== MENÚ ==========================\n\n"); // Encabezado del menú
                                strcat(buffer, "REGISTRAR\n");                                                    // Opción de registrarse
                                strcat(buffer, "USUARIO y PASSWORD \n");                                          // Opción de iniciar sesión
                                strcat(buffer, "SALIR\n");

                                FD_SET(new_sd, &readfds);
                                send(new_sd, buffer, sizeof(buffer), 0);

                                for (j = 0; j < (numClientes - 1); j++)
                                {
                                    if (listaclientes[j].estado == 1)
                                    {
                                        bzero(buffer, sizeof(buffer));
                                        sprintf(buffer, "Nuevo Cliente conectado en <%d>", new_sd);
                                        send(listaclientes[j].sd, buffer, sizeof(buffer), 0);
                                    }
                                }
                            }
                            else
                            {
                                bzero(buffer, sizeof(buffer));
                                strcpy(buffer, "Demasiados clientes conectados\n");
                                send(new_sd, buffer, sizeof(buffer), 0);
                                close(new_sd);
                            }
                        }
                    }
                    else if (i == 0) // en este else if habla el servidor
                    {
                        // Se ha introducido informaciÃ³n de teclado
                        bzero(buffer, sizeof(buffer));
                        fgets(buffer, sizeof(buffer), stdin);

                        // Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor. (implementar)
                        if (strcmp(buffer, "SALIR\n") == 0)
                        {

                            for (j = 0; j < numClientes; j++)
                            {
                                bzero(buffer, sizeof(buffer));
                                strcpy(buffer, "Desconexión servidor\n");
                                send(listaclientes[j].sd, buffer, sizeof(buffer), 0);
                                close(listaclientes[j].sd);
                                FD_CLR(listaclientes[j].sd, &readfds);
                            }
                            close(sd);
                            exit(-1);
                        }
                        // Mensajes que se quieran mandar a los clientes (implementar)
                    }
                    else // en este else ya esta hablando uno de los clientes, pero un cliente que no es nuevo
                    {
                        bzero(buffer, sizeof(buffer));

                        recibidos = recv(i, buffer, sizeof(buffer), 0);

                        if (recibidos > 0)
                        {

                            /*ASIGNACION DE ESTADO PARA CAPAR LO QUE PUEDA ESCRIBIR -------------------------------------------------------------------------*/

                            // aqui estoy buscando el cliente que esta interactuando con el servidor dentro de la lista de clientes para conseguir su estado
                            struct cliente *actual = bcliente(listaclientes, numClientes, i);

                            // vamos a declara un estado auxiliar para la gestion de los estados de los clientes
                            int estadoAux = actual->estado;

                            // REVISAR
                            // posible codigo que se puede quitar RE
                            if (buffer[strlen(buffer) - 1] == '\n')
                            {
                                buffer[strlen(buffer) - 1] = '\0';
                            }

                            printf("Jugador[%d] con estado[%d]-->COMUNICA: %s\n", i, estadoAux, buffer);

                            /*-------------------------------------------------------------------------------------------------------------------------------*/

                            if (strcmp(buffer, "SALIR") == 0) // Cambiado para evitar la nueva línea
                            {
                                printf("Jugador[%d] desea salir.\n", i);
                                salirCliente(i, &readfds, &numClientes, listaclientes, listapartidas, &partidas);
                            }
                            else if (estadoAux == 0) // aqui solo pueden acceder los clientes que no estan iniciados sesion
                            {
                                if (strncmp(buffer, "USUARIO", 7) == 0)
                                {
                                    char *nombre = buffer + 8;
                                    char nombrefiche[150] = "BBDD.txt";
                                    char passwordEsperada[MSG_SIZE] = {0}; // Para guardar la contraseña esperada

                                    if (strlen(nombre) > 0)
                                    {
                                        // Eliminar el salto de línea si está presente
                                        size_t len = strlen(nombre);
                                        if (nombre[len - 1] == '\n')
                                        {
                                            nombre[len - 1] = '\0'; // Reemplazar el salto de línea con el carácter nulo
                                        }
                                        char nene[250];
                                        strcpy(nene, nombre);
                                        printf("Nombre de usuario recibido: %s, %s\n", nombre, nombrefiche);

                                        if (comprobarfiche(nombrefiche, nombre))
                                        {
                                            printf("BIEN\n");

                                            if (!comprobarlog(listaclientes, nombre, numClientes))
                                            {
                                                printf("MAL\n");
                                                strcpy(buffer, "–Err. Usuario ya logueado\n");
                                                send(i, buffer, sizeof(buffer), 0);
                                            }

                                            strcpy(buffer, "+Ok. Usuario correcto.\n");
                                            send(i, buffer, sizeof(buffer), 0);

                                            // Ahora esperar a que el cliente envíe la contraseña
                                            bzero(buffer, sizeof(buffer));
                                            recibidos = recv(i, buffer, sizeof(buffer), 0);

                                            if (recibidos > 0 && strncmp(buffer, "PASSWORD", 8) == 0)
                                            {
                                                char *pass = buffer + 9;

                                                // Eliminar salto de línea en la contraseña
                                                len = strlen(pass);
                                                if (pass[len - 1] == '\n')
                                                {
                                                    pass[len - 1] = '\0';
                                                }

                                                // Comparar la contraseña
                                                if (comprobarfiche_contrasena(nombrefiche, nene, pass))
                                                {
                                                    printf("Contraseña correcta\n");

                                                    // Aqui lo que hacemos cambiar el estado de a dentro del sistema
                                                    actual->estado = 1;
                                                    actual->contraseña = pass;
                                                    actual->nombre = nombre;
                                                    // realizamos una funcion que lo que hace es actualizar tanto la lista de clientes como la estructura del cliente actual
                                                    actual = actualizarcliente(listaclientes, numClientes, actual);

                                                    strcpy(buffer, "+Ok. Usuario correcto\n\n");

                                                    // actualizarnombrecliente(listaclientes, numClientes, sd, nombre, pass);
                                                    strcat(buffer, "========================== MENÚ ==========================\n\n"); // Encabezado del menú
                                                    strcat(buffer, "INICIAR-PARTIDA\n");                                              // Opción de registrarse
                                                    strcat(buffer, "SALIR");
                                                }
                                                else
                                                {
                                                    printf("Contraseña incorrecta\n");
                                                    strcpy(buffer, "-Err. Error en la validación\n");
                                                }

                                                send(i, buffer, sizeof(buffer), 0);
                                            }
                                            else
                                            {
                                                // Comando no válido
                                                bzero(buffer, sizeof(buffer));
                                                strcpy(buffer, "-Err. Comando no válido, se esperaba la password, vuelve a escribir el usuario\n");
                                                send(i, buffer, sizeof(buffer), 0);
                                            }
                                        }
                                        else
                                        {
                                            printf("MAL\n");
                                            strcpy(buffer, "–Err. Usuario incorrecto\n");
                                            send(i, buffer, sizeof(buffer), 0);
                                        }
                                    }
                                    else
                                    {
                                        printf("Mensaje incompleto\n");
                                        strcpy(buffer, "-Err. Mensaje incompleto\n");
                                        send(new_sd, buffer, sizeof(buffer), 0);
                                    }
                                }
                                else if (strncmp(buffer, "REGISTRAR", 9) == 0)
                                {
                                    char nombrefiche[150] = "BBDD.txt";
                                    char usuario[50] = {0};    // Inicializa en vacÃ­o
                                    char contraseña[50] = {0}; // Inicializa en vacÃ­o
                                    char *token;

                                    // AsegÃºrate de usar un token separado para el comando
                                    token = strtok(buffer, " "); // los strok hay que explicarlos bien
                                    while (token != NULL)
                                    {
                                        if (strcmp(token, "-u") == 0)
                                        {
                                            token = strtok(NULL, " "); // Obtener el siguiente token (usuario)
                                            if (token != NULL && strchr(token, ' ') == NULL)
                                            { // Verifica que no haya espacios
                                                strcpy(usuario, token);
                                            }
                                            else
                                            {
                                                send(i, "Error: el usuario no puede contener espacios.\n", 50, 0);
                                                break; // Sale del bucle si hay un error
                                            }
                                        }
                                        else if (strcmp(token, "-p") == 0)
                                        {
                                            token = strtok(NULL, " "); // Obtener el siguiente token (contraseña)
                                            if (token != NULL && strchr(token, ' ') == NULL)
                                            { // Verifica que no haya espacios
                                                strcpy(contraseña, token);
                                            }
                                            else
                                            {
                                                send(i, "Error: la contraseña no puede contener espacios.\n", 50, 0);
                                                break; // Sale del bucle si hay un error
                                            }
                                        }
                                        token = strtok(NULL, " "); // Continuar con el siguiente token
                                    }
                                    char *r = registrar(nombrefiche, usuario, contraseña);
                                    // Solo llamar a la funciÃ³n registrar si se han obtenido usuario y contraseña
                                    if (strlen(usuario) > 0 && strlen(contraseña) > 0)
                                    {
                                        strcpy(buffer, r);
                                        send(i, buffer, sizeof(buffer), 0);
                                    }
                                    else
                                    {
                                        send(i, "Error: debe proporcionar un nombre de usuario y una contraseña.\n", 60, 0);
                                    }
                                }
                                else
                                {
                                    // Comando no válido
                                    bzero(buffer, sizeof(buffer));
                                    strcpy(buffer, "-Err. Comando no válido.\n");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                            }

                            else if (estadoAux == 1)
                            {

                                // Dentro del código del servidor en el manejo de clientes
                                if (strncmp(buffer, "INICIAR-PARTIDA", 15) == 0)
                                {

                                    struct cliente *adversario = buscarcontringante(listaclientes, numClientes);

                                    if (partidas < 10)
                                    { // Limitar a un máximo de 10 partidas simultáneas
                                        if (adversario != NULL)
                                        {
                                            // Cambiar el estado de ambos jugadores a "en partida"
                                            actual->estado = 3;
                                            adversario->estado = 3;

                                            // Inicializar la estructura de la partida
                                            struct partida *partidaActual = new partida(); // Usar 'new' en lugar de 'malloc'

                                            if (!partidaActual)
                                            {
                                                perror("Error al asignar memoria para la partida.");
                                                exit(EXIT_FAILURE);
                                            }

                                            // Asignar jugadores a la partida
                                            partidaActual->jugador1 = actual;
                                            partidaActual->jugador2 = adversario;

                                            // Inicializar el mazo desde el fichero
                                            partidaActual->mazo = inicializarMazo("Baraja.txt"); // Asegúrate de que esta función lea correctamente las cartas.

                                            // Añadir la partida a la lista de partidas activas
                                            listapartidas[partidas] = partidaActual; // Almacenar el puntero a la partida actual
                                            partidas++;

                                            // Enviar confirmación a ambos jugadores
                                            bzero(buffer, sizeof(buffer));
                                            sprintf(buffer, "+OK. Partida iniciada entre jugador %d y jugador %d.\n\n", actual->sd, adversario->sd);
                                            strcat(buffer, "========================== MENÚ ==========================\n\n"); // Encabezado del menú
                                            strcat(buffer, "PEDIR-CARTA\n");
                                            strcat(buffer, "PLANTARME\n"); // Opción de registrarse
                                            strcat(buffer, "SALIR\n");
                                            send(actual->sd, buffer, strlen(buffer), 0);
                                            send(adversario->sd, buffer, strlen(buffer), 0);

                                            // Asignar cartas a los jugadores
                                            asignarCartasYNotificar(partidaActual->mazo, actual, adversario);

                                            // Establecer los turnos iniciales
                                            actual->turno = true;
                                            adversario->turno = false;

                                            // Añadir a ambos jugadores al conjunto de lectura (readfds)
                                            FD_SET(actual->sd, &readfds);
                                            FD_SET(adversario->sd, &readfds);

                                            strcpy(buffer, "+Ok. Espera tu turno...\n");
                                            send(adversario->sd, buffer, strlen(buffer), 0);

                                            strcpy(buffer, "+Ok. Ahora es tu turno\n");
                                            send(actual->sd, buffer, strlen(buffer), 0);

                                            printf("Partida iniciada entre jugador %d y jugador %d\n", actual->sd, adversario->sd);
                                        }
                                        else
                                        {
                                            // Si no se encuentra un contrincante, actualizar el estado del jugador a "esperando"
                                            actual->estado = 2;
                                            bzero(buffer, sizeof(buffer));
                                            strcpy(buffer, "+Ok. Esperando a otro jugador\n");
                                            send(actual->sd, buffer, strlen(buffer), 0);
                                        }
                                    }
                                    else
                                    {
                                        // Limitar el número de partidas simultáneas
                                        bzero(buffer, sizeof(buffer));
                                        strcpy(buffer, "-Err. El servidor está lleno, no se pueden iniciar más partidas.\n");
                                        send(actual->sd, buffer, strlen(buffer), 0);
                                    }
                                }
                                else
                                {
                                    // Comando no válido
                                    bzero(buffer, sizeof(buffer));
                                    strcpy(buffer, "-Err. Comando no válido.\n");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                            }
                            else if (estadoAux == 3)
                            {
                                struct partida *partidaActual = NULL;
                                struct cliente *adversario = NULL;

                                // Buscar la partida actual
                                for (int i = 0; i < partidas; i++)
                                {
                                    if (listapartidas[i]->jugador1->sd == actual->sd || listapartidas[i]->jugador2->sd == actual->sd)
                                    {
                                        partidaActual = listapartidas[i];
                                        break; // Si se encuentra la partida, se sale del bucle
                                    }
                                }

                                // Si no se encontró la partida, devolver un error y salir
                                if (partidaActual == NULL)
                                {
                                    printf("ERROR: No se encontró la partida para el jugador.\n");
                                    strcpy(buffer, "-Err. No se encontró la partida.\n");
                                    send(actual->sd, buffer, strlen(buffer), 0);
                                    continue;
                                }

                                // Identificar al adversario
                                if (actual->sd == partidaActual->jugador1->sd)
                                {
                                    adversario = partidaActual->jugador2;
                                }
                                else
                                {
                                    adversario = partidaActual->jugador1;
                                }

                                // Manejar comandos del cliente
                                if (strncmp(buffer, "PEDIR-CARTA", 15) == 0)
                                {
                                    if (actual->turno)
                                    {
                                        // Obtener la carta asignada
                                        carta nuevaCarta = asignarCarta(partidaActual->mazo, actual);

                                        // Construir el mensaje en el formato "+Ok.[<PALO>,<NÚMERO>] Carta enviada."
                                        std::string mensaje = "+Ok.[" + nuevaCarta.palo + "," + nuevaCarta.valor + "] Carta enviada.\n";

                                        // Convertir std::string a const char* y enviar el mensaje al jugador actual
                                        send(actual->sd, mensaje.c_str(), mensaje.length(), 0);

                                        int total = calcularValorTotal(actual->mazo);
                                        if (total > 21)
                                        {
                                            strcpy(buffer, "Te has pasado de 21. Has perdido.\n");
                                            send(actual->sd, buffer, strlen(buffer), 0);

                                            strcpy(buffer, "El jugador rival se ha pasado de 21. Has ganado.\n");
                                            send(adversario->sd, buffer, strlen(buffer), 0);

                                            finalizarPartida(listapartidas, partidas, partidaActual, actual, adversario);
                                            continue; // Termina la ejecución si el jugador se ha pasado
                                        }

                                        // Cambiar de turno//ARREGLADO
                                        if (adversario->plantado == true)
                                        {
                                            adversario->turno = false;
                                            actual->turno = true;
                                            strcpy(buffer, "+Ok. Sigue siendo tu turno\n");
                                            send(actual->sd, buffer, strlen(buffer), 0);
                                        }
                                        else
                                        {
                                            adversario->turno = true;
                                            actual->turno = false;

                                            strcpy(buffer, "+Ok. Ahora es tu turno\n");
                                            send(adversario->sd, buffer, strlen(buffer), 0);
                                        }
                                    }
                                    else
                                    {
                                        strcpy(buffer, "-Err. No es tu turno.\n");
                                        send(actual->sd, buffer, strlen(buffer), 0);
                                    }
                                }
                                else if (strncmp(buffer, "PLANTARME", 9) == 0)
                                {
                                    if (actual->turno)
                                    {
                                        strcpy(buffer, "+Ok. Te plantas.\n");
                                        send(actual->sd, buffer, strlen(buffer), 0);

                                        actual->plantado = true;
                                        adversario->turno = true; // El adversario toma el turno
                                        actual->turno = false;

                                        strcpy(buffer, "+Ok. Ahora es tu turno\n");
                                        send(adversario->sd, buffer, strlen(buffer), 0);

                                        // Verificar si ambos jugadores se plantaron
                                        if (adversario->plantado)
                                        {
                                            int total1 = calcularValorTotal(actual->mazo);
                                            int total2 = calcularValorTotal(adversario->mazo);

                                            // Caso donde ambos jugadores se pasan de 21
                                            if (total1 > 21 && total2 > 21)
                                            {
                                                strcpy(buffer, "Ambos jugadores se han pasado de 21. Es un empate.\n");
                                                send(actual->sd, buffer, strlen(buffer), 0);
                                                send(adversario->sd, buffer, strlen(buffer), 0);
                                            }
                                            else if (total1 > 21)
                                            {
                                                strcpy(buffer, "Te has pasado de 21. Has perdido.\n");
                                                send(actual->sd, buffer, strlen(buffer), 0);

                                                strcpy(buffer, "El jugador rival se ha pasado de 21. Has ganado.\n");
                                                send(adversario->sd, buffer, strlen(buffer), 0);
                                            }
                                            else if (total2 > 21)
                                            {
                                                strcpy(buffer, "El jugador rival se ha pasado de 21. Has ganado.\n");
                                                send(actual->sd, buffer, strlen(buffer), 0);

                                                strcpy(buffer, "Te has pasado de 21. Has perdido.\n");
                                                send(adversario->sd, buffer, strlen(buffer), 0);
                                            }
                                            else
                                            {
                                                // Comparar quién está más cerca de 21
                                                if (total1 > total2)
                                                {
                                                    strcpy(buffer, "+Ok. Tienes el total más cercano a 21. Has ganado.\n");
                                                    send(actual->sd, buffer, strlen(buffer), 0);

                                                    strcpy(buffer, "-Err. El jugador rival tiene el total más cercano a 21. Has perdido.\n");
                                                    send(adversario->sd, buffer, strlen(buffer), 0);
                                                }
                                                else if (total2 > total1)
                                                {
                                                    strcpy(buffer, "-Err. El jugador rival tiene el total más cercano a 21. Has perdido.\n");
                                                    send(actual->sd, buffer, strlen(buffer), 0);

                                                    strcpy(buffer, "+Ok. Tienes el total más cercano a 21. Has ganado.\n");
                                                    send(adversario->sd, buffer, strlen(buffer), 0);
                                                }
                                                else
                                                {
                                                    strcpy(buffer, "+Ok. Empate. Ambos tienen el mismo valor.\n");
                                                    send(actual->sd, buffer, strlen(buffer), 0);
                                                    send(adversario->sd, buffer, strlen(buffer), 0);
                                                }
                                            }
                                            finalizarPartida(listapartidas, partidas, partidaActual, actual, adversario); // Finalizar la partida
                                            actual->plantado = false;
                                            adversario->plantado = false;
                                            continue;
                                        }
                                    }
                                    else
                                    {
                                        strcpy(buffer, "-Err. No es tu turno.\n");
                                        send(actual->sd, buffer, strlen(buffer), 0);
                                    }
                                }
                                else
                                {
                                    // Comando no válido
                                    bzero(buffer, sizeof(buffer));
                                    strcpy(buffer, "-Err. Comando no válido.\n");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                            }
                        }
                        // Si el cliente introdujo ctrl+c
                        else if (recibidos == 0)
                        {
                            printf("El socket %d, ha introducido ctrl+c\n", i);
                            // Eliminar ese socket
                            salirCliente(i, &readfds, &numClientes, listaclientes, listapartidas, &partidas);
                        }
                    }
                }
            }
        }
    }

    close(sd);
    return 0;
}

// capar las instrucciones para que solo se pueda usar pedir carta, creo que ya esta
// salir cuando estamos en estado de esperando y
// lo del registro