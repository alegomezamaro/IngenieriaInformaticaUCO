#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#define QUEUE_LENGTH 10
#define ITEM_SIZE sizeof(int)
static const char* TAG = "P2_3_1";
// Tarea del productor
void producer_task(void *pvParameters)
{
    QueueHandle_t xQueue = (QueueHandle_t) pvParameters;
    int i = 0;
    while (1)
    {
        // Genera un nuevo dato
        int item = i++;
        // Envía el dato a la cola
        ESP_LOGI(TAG, "Tarea productor: item %d producido", item);

        //MODIFICADO
        // Productor (fragmento)
        if (xQueueSend(xQueue, &item, 0) == pdPASS) {
            ESP_LOGI(TAG, "Tarea productor: item %d producido", item);
        } else {
            ESP_LOGW(TAG, "Cola llena. Descartando item %d", item);
        }

        // Simula una pausa entre envíos
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// Tarea del consumidor
void consumer_task(void *pvParameters)
{
    QueueHandle_t xQueue = (QueueHandle_t) pvParameters;
    while (1)
    {
        // Espera a que haya datos disponibles en la cola
        int item;

        //MODIFICADO
        // Consumidor (fragmento)
        if (xQueueReceive(xQueue, &item, 0) == pdPASS) {
            ESP_LOGI(TAG, "Tarea consumidor: item %d consumido", item);
        } else {
            ESP_LOGW(TAG, "Cola vacía. Haciendo otras cosas...");
        }

        // Recibe un ítem
        ESP_LOGI(TAG, "Tarea consumidor: item %d consumido", item);
        // Esta espera hace que el consumidor sea muy lento,
        // Para inducir al bloqueo de sincronización
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main()
{
    // Crea una cola con capacidad para 10 elementos de tipo entero
    QueueHandle_t xQueue;
    xQueue = xQueueCreate(QUEUE_LENGTH, ITEM_SIZE);
    // Crea las tareas del productor y consumidor
    xTaskCreate(producer_task, "producer_task", 2048, xQueue, 1, NULL);
    xTaskCreate(consumer_task, "consumer_task", 2048, xQueue, 1, NULL);
}