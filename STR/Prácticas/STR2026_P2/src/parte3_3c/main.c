#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <esp_log.h>

#define NUM_TASKS 3 // Número N de instancias que vamos a crear

static const char* TAG = "P2_3_3c";

// 1. Estructura con argumentos para las tareas (Estrategia 3a)
typedef struct {
    char* task_name;
    SemaphoreHandle_t semaphore;
} Parameters_t;

// Variable global para que la memoria no se borre al salir del bloque
Parameters_t task_params[NUM_TASKS];

// Función de la Tarea (Misma para todas las instancias)
void task_function(void *parameters)
{
    // Casteamos y extraemos los parámetros
    Parameters_t *params = (Parameters_t *)parameters;
    SemaphoreHandle_t semaphore = params->semaphore;
    char* task_name = params->task_name;
    
    while (1)
    {
        // Esperar a que haya "fichas" en el semáforo contador
        if (xSemaphoreTake(semaphore, portMAX_DELAY) == pdTRUE)
        {
            ESP_LOGI(TAG, "%s: Tick", task_name);
        }
        else
        {
            ESP_LOGI(TAG,"%s: Demasiada espera. Continúo con otra cosa ...", task_name);
        }
    }
}

void app_main()
{
    ESP_LOGI(TAG, "Arrancando sistema con Semáforo Contador...");

    // 2. Crear un semáforo contador
    // Arg 1 (Max Count): Hasta cuántas "fichas" puede almacenar (NUM_TASKS)
    // Arg 2 (Initial Count): Con cuántas empieza (0, para que las tareas se bloqueen al nacer)
    SemaphoreHandle_t semaphore = xSemaphoreCreateCounting(NUM_TASKS, 0);

    char* nombres_tareas[NUM_TASKS] = {"Task 1", "Task 2", "Task 3"};

    // 3. Bucle para crear las N instancias de forma automática
    for (int i = 0; i < NUM_TASKS; i++)
    {
        // Rellenamos los datos específicos de esta instancia
        task_params[i].task_name = nombres_tareas[i];
        task_params[i].semaphore = semaphore;

        // Creamos la tarea pasándole su estructura correspondiente
        xTaskCreate(task_function, nombres_tareas[i], 2048, &task_params[i], 1, NULL);
    }

    // 4. app_main asume el rol de "Sincronizador Maestro"
    while(1)
    {
        // Esperamos 1 segundo
        vTaskDelay(pdMS_TO_TICKS(1000));
        
        ESP_LOGI(TAG, "--- app_main: Lanzando %d Ticks ---", NUM_TASKS);
        
        // Hacemos N "Gives" rápidos para incrementar el contador y despertar a todas
        for (int i = 0; i < NUM_TASKS; i++)
        {
            xSemaphoreGive(semaphore);
        }
    }
}