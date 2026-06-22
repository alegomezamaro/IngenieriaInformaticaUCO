#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <esp_log.h>
static const char* TAG = "P2_3_3b";
// Tarea
void task_function(void *pvParameters)
{
    // Parámetros de configuración
    SemaphoreHandle_t semaphore = (SemaphoreHandle_t) pvParameters;
    while (1)
    {
        // Esperar al semáforo
        if (xSemaphoreTake(semaphore, portMAX_DELAY) == pdTRUE)
        {
            ESP_LOGI(TAG, "task_function: Tick");
        }
        else
        {
            ESP_LOGI(TAG,"task_function: Demasiada espera. Continúo con otra cosa ...");
        }
    }
}

void app_main()
{
    // Crear un semáforo binario
    SemaphoreHandle_t semaphore = xSemaphoreCreateBinary();
    // Creación de las tareas
    xTaskCreate(task_function, "Task 1", 2048, semaphore, 1, NULL);
    while(1)
    {
        vTaskDelay(1000/portTICK_PERIOD_MS);
        xSemaphoreGive(semaphore);
    }
}