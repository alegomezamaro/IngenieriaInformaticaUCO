# Práctica 2 – Redes

**Autores:**  
- Alejandro Gómez Amaro  
- Javier Castilla Arroyo  

---

## Estructura del proyecto

| Archivo | Descripción |
|----------|--------------|
| `servidorP2.c` | Código fuente del servidor TCP (gestión de partidas y usuarios) |
| `clienteP2.c` | Código fuente del cliente TCP interactivo |
| `basedatos.txt` | Fichero generado automáticamente con los usuarios registrados |

---

## Comandos disponibles

| Comando | Descripción |
|----------|--------------|
| `REGISTRO -u <user> -p <pass>` | Crea un nuevo usuario en `basedatos.txt`. Si ya existe, muestra error. |
| `USUARIO <user>` | Indica el nombre del usuario que se autenticará. |
| `PASSWORD <pass>` | Valida la contraseña del usuario. |
| `INICIAR-PARTIDA` | Se une a la cola o inicia partida con otro jugador. |
| `TIRAR-DADOS <num>` | Tira 1 o 2 dados. |
| `NO-TIRAR-DADOS` | Pasa el turno sin tirar (máx. 3 veces). |
| `PLANTARME` | Se planta; el otro jugador puede seguir jugando sin esperarlo. |
| `SALIR` | Sale de la partida o cierra sesión. |

---

## Compilación

Ejecutar los siguientes comandos desde la terminal:

```bash
gcc -Wall -O2 -o servidorP2 servidorP2.c
gcc -Wall -O2 -o clienteP2 clienteP2.c
