#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <esp_log.h>
static const char* TAG = "P2_3_3a";

// Estructura con argumentos para las tareas
typedef struct {
    char* task_name;
    uint32_t delay_outside;
    uint32_t delay_inside;
    SemaphoreHandle_t semaphore;
} Parameters_t;
// Tarea
void task_function(void *parameters)
{
    // Parámetros de configuración
    SemaphoreHandle_t semaphore = ((Parameters_t *)parameters)->semaphore;
    uint32_t delay_inside = ((Parameters_t *)parameters)->delay_inside;
    uint32_t delay_outside = ((Parameters_t *)parameters)->delay_outside;
    char* task_name = ((Parameters_t *)parameters)->task_name;
    while (1)
    {
        // Esperar al semáforo
        if (xSemaphoreTake(semaphore, portMAX_DELAY) == pdTRUE)
        {
            ESP_LOGI(TAG, "%s: Entro de la zona protegida", task_name);

            // Espera dentro de la zona protegida
            vTaskDelay(delay_inside);

            ESP_LOGI(TAG, "%s: Salgo de la zona protegida", task_name);
            // Liberar el semáforo
            xSemaphoreGive(semaphore);
        }
        else
        {
            ESP_LOGI(TAG,"%s: Demasiada espera. Continúo con otra cosa ...", task_name);
        }

        // Espera fuera de la zona protegida
        vTaskDelay(delay_outside);
    }
}

void app_main()
{
    // Crear un semáforo binario
    SemaphoreHandle_t semaphore = xSemaphoreCreateMutex();
    // Libera el semáforo
    xSemaphoreGive(semaphore);
    // Parámetros de configuración de las tareas
    // Añade 'static' antes de las variables en app_main()
    Parameters_t task1_params = 
    {
        .task_name = "Task 1",
        .delay_inside = 500/portTICK_PERIOD_MS,
        .delay_outside = 1000/portTICK_PERIOD_MS,
        .semaphore = semaphore
    };
    
    Parameters_t task2_params = 
    {
        .task_name = "Task 2",
        .delay_inside = 1000/portTICK_PERIOD_MS,
        .delay_outside = 500/portTICK_PERIOD_MS,
        .semaphore = semaphore
    };
    // Creación de las tareas
    xTaskCreate(task_function, "Task 1", 2048, &task1_params, 1, NULL);
    xTaskCreate(task_function, "Task 2", 2048, &task2_params, 1, NULL);

    //NECESITAMOS
    vTaskDelay(portMAX_DELAY); //Añadimos delay para que las tareas sigan ejecutándose indefinidamente
}