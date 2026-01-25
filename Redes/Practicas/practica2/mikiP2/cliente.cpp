#include "funciones.h"

// Función principal del cliente
int main()
{
    int sd;
    struct sockaddr_in sockname;
    char buffer[250];
    socklen_t len_sockname;
    fd_set readfds, auxfds;
    int salida;
    int fin = 0;

    // Crear un socket TCP
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1)
    {
        perror("No se puede abrir el socket cliente\n");
        exit(1);
    }

    // Configurar la dirección del servidor
    sockname.sin_family = AF_INET;                     // Usar IPv4
    sockname.sin_port = htons(2000);                   // Establecer el puerto a 2000
    sockname.sin_addr.s_addr = inet_addr("127.0.0.1"); // Establecer la dirección IP a localhost

    len_sockname = sizeof(sockname);

    // Intentar conectarse al servidor
    if (connect(sd, (struct sockaddr *)&sockname, len_sockname) == -1)
    {
        perror("Error de conexión");
        exit(1);
    }

    printf("Conectado al servidor.\n");

    FD_ZERO(&auxfds);
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);  // stdin
    FD_SET(sd, &readfds); // socket

    do
    {
        auxfds = readfds;
        salida = select(sd + 1, &auxfds, NULL, NULL, NULL);

        // Mensaje desde el servidor
        if (FD_ISSET(sd, &auxfds))
        {
            bzero(buffer, sizeof(buffer));
            int bytesReceived = recv(sd, buffer, sizeof(buffer) - 1, 0);

            if (bytesReceived > 0)
            {
                buffer[bytesReceived] = '\0'; // Asegúrate de que está terminado en nulo
                printf("\n%s\n", buffer);

                if (strcmp(buffer, "Demasiados clientes conectados\n") == 0)
                    fin = 1;

                if (strcmp(buffer, "Desconexión servidor\n") == 0)
                    fin = 1;
            }
            else if (bytesReceived == 0)
            {
                printf("El servidor ha cerrado la conexión.\n");
                fin = 1;
            }
            else
            {
                perror("Error en recv");
                fin = 1;
            }
        }
        else
        { // Entrada del usuario
            if (FD_ISSET(0, &auxfds))
            {
                bzero(buffer, sizeof(buffer));
                fgets(buffer, sizeof(buffer), stdin);

                if (strcmp(buffer, "SALIR\n") == 0)
                {
                    fin = 1;
                    printf("+OK. Saliendo del cliente...\n");
                }

                send(sd, buffer, sizeof(buffer), 0); // Enviar al servidor
            }
        }
    } while (fin == 0);

    // Cerrar el socket antes de salir
    close(sd);
    printf("Conexión cerrada. Saliendo...\n");
    return 0;
}
