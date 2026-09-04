#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
// Macros para las máscaras de bits
#define BIT_0 (1 << 0)
#define BIT_1 (1 << 1)
// ...
//#define BIT_n (1 << n)
static const char* TAG = "P2_3_2a";
// Función que procesa los bits del grupo de eventos
void task_wait_for_event(void *pvParameters)
{
    EventGroupHandle_t event_group = (EventGroupHandle_t)pvParameters;
    EventBits_t bits;
    while (1)
    {

        // MODIFICACIÓN
        // Ahora la tarea solo esperará a que se active el BIT_0, ignorando el BIT_1
        bits = xEventGroupWaitBits(event_group, BIT_0, pdTRUE, pdFALSE, portMAX_DELAY);

        // Como resultado tenemos una palabra de 32 bits disponibles
        if (bits & BIT_0)
        {
            ESP_LOGI(TAG, "BIT_0 detectado");
        }
        if (bits & BIT_1)
        {
            ESP_LOGI(TAG, "BIT_1 detectado");
        }
    }
}

// Función de la tarea que establece el evento BIT_0 periódicamente
void task_set_bit_0(void *pvParameters)
{
    EventGroupHandle_t event_group = (EventGroupHandle_t)pvParameters;
    while (1)
    {
        // Establece el evento BIT_0
        xEventGroupSetBits(event_group, BIT_0);
        // Espera un tiempo antes de establecerlo nuevamente
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Función de la tarea que establece el evento BIT_1 periódicamente
void task_set_bit_1(void *pvParameters)
{
    EventGroupHandle_t event_group = (EventGroupHandle_t)pvParameters;
    while (1)
    {
        // Establece el evento BIT_1
        xEventGroupSetBits(event_group, BIT_1);
        // Espera un tiempo antes de establecerlo nuevamente
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main()
{
    // Crea el grupo de eventos
    EventGroupHandle_t event_group = xEventGroupCreate();
    // Crea las tareas
    xTaskCreate(task_wait_for_event, "task_wait_for_event", 2048, event_group, 1, NULL);
    xTaskCreate(task_set_bit_0, "task_set_bit_0", 2048, event_group, 1, NULL);
    xTaskCreate(task_set_bit_1, "task_set_bit_1", 2048, event_group, 1, NULL);
}