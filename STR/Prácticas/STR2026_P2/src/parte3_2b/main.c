#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

// Definimos un bit para cada tarea
#define TASK_1_BIT (1 << 0)
#define TASK_2_BIT (1 << 1)
#define TASK_3_BIT (1 << 2)

// Esta máscara incluye los bits de todas las tareas que deben sincronizarse
#define ALL_SYNC_BITS (TASK_1_BIT | TASK_2_BIT | TASK_3_BIT)

static const char* TAG = "P2_3_2b";
EventGroupHandle_t event_group;

// Función de tarea genérica a la que le pasaremos diferentes parámetros
void task_sync(void *pvParameters) {
    int task_num = (int)pvParameters;
    EventBits_t my_bit;
    int delay_ms;
    
    // Configuramos cada tarea con su propio bit y un tiempo de "trabajo" diferente
    if (task_num == 1) { 
        my_bit = TASK_1_BIT; 
        delay_ms = 1000; // Tarea rápida
    } else if (task_num == 2) { 
        my_bit = TASK_2_BIT; 
        delay_ms = 3000; // Tarea media
    } else { 
        my_bit = TASK_3_BIT; 
        delay_ms = 5000; // Tarea lenta
    }

    while (1) {
        ESP_LOGI(TAG, "Tarea %d trabajando durante %d ms...", task_num, delay_ms);
        vTaskDelay(pdMS_TO_TICKS(delay_ms)); // Simulamos que la tarea está trabajando
        
        ESP_LOGI(TAG, "Tarea %d llego al punto de encuentro. Esperando a las demas...", task_num);
        
        // --- PUNTO DE ENCUENTRO ---
        // Argumento 1: el grupo de eventos.
        // Argumento 2: el bit que establece ESTA tarea al llegar.
        // Argumento 3: los bits que DEBE ESPERAR (todas las tareas).
        // Argumento 4: el tiempo máximo de espera.
        xEventGroupSync(event_group, my_bit, ALL_SYNC_BITS, portMAX_DELAY);
        
        ESP_LOGI(TAG, "¡Tarea %d sincronizada! Iniciando nueva ronda...", task_num);
        vTaskDelay(pdMS_TO_TICKS(1000)); // Pequeña pausa antes de reiniciar el ciclo
    }
}

void app_main() {
    ESP_LOGI(TAG, "Iniciando prueba de xEventGroupSync...");
    
    // Creamos el grupo de eventos
    event_group = xEventGroupCreate();
    
    // Creamos las 3 tareas pasándoles un número (1, 2 o 3) como identificador
    xTaskCreate(task_sync, "Task 1", 2048, (void*)1, 1, NULL);
    xTaskCreate(task_sync, "Task 2", 2048, (void*)2, 1, NULL);
    xTaskCreate(task_sync, "Task 3", 2048, (void*)3, 1, NULL);
}