#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
static const char* TAG = "P2_2_3";

void memory_allocation_task(void *pvParameters)
{
    while (1)
    {
        // Reservar memoria dinámica
        void *ptr = pvPortMalloc(1024);
        // Verificar si la asignación de memoria fue exitosa
        if (ptr == NULL)
        {
            ESP_LOGE(TAG, "No se pudo reservar más memoria");
            vTaskDelete(NULL); // Eliminar la tarea si no se pudo reservar memoria
        }
        ESP_LOGI(TAG, "Reserva de 1024 bytes");
        // Simular un poco de trabajo
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void app_main()
{
    // Crear tarea para la asignación de memoria
    xTaskCreate(memory_allocation_task, "Memory Allocation Task", 2048, NULL, 1, NULL);
    // No es necesario mantener la tarea app_main, la tarea Memory Allocation Task
    // continuará su ejecución indefinidamente
}