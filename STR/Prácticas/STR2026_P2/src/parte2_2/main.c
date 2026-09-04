#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
static const char* TAG ="P2_2_2";

// Código de la Tarea 1 original
void task_function(void *pvParameters)
{
    ESP_LOGI(TAG, "task_function: inicio de la tarea");
    printf("Ejecución de Task: ");
    while(1)
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);
        printf(".");
        fflush(stdout);
    }
}

// Función auxiliar para imprimir el estado
void print_task_state (TaskHandle_t handler)
{
    TaskStatus_t task_status;
    // Comprobación de seguridad por si el manejador es nulo
    if (handler == NULL) return; 
    
    vTaskGetInfo(handler, &task_status, pdTRUE, eInvalid);
    printf("\nTask STATE: ");
    switch (task_status.eCurrentState)
    {
        case eRunning:   printf("RUNNING\n");   break;
        case eReady:     printf("READY\n");     break;
        case eBlocked:   printf("BLOCKED\n");   break;
        case eSuspended: printf("SUSPENDED\n"); break;
        case eDeleted:   printf("DELETED\n");   break;
        default:         printf("UNKNOWN\n");   break;
    }
}

// NUEVA: Tarea 2 que monitoriza a la Tarea 1
void task2_function(void *pvParameters)
{
    // Recuperamos el manejador que pasamos como argumento
    TaskHandle_t handle_task1 = (TaskHandle_t)pvParameters;
    
    while(1)
    {
        print_task_state(handle_task1);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Espera de 1 segundo
    }
}

void app_main()
{
    TaskHandle_t task_handler; // Manejador de Task1
    ESP_LOGI(TAG, "app_main: despliegue de las tareas.");

    // 1. Creación de Task1
    xTaskCreate(task_function, "Task", 2048, NULL, 1, &task_handler);

    // 2. Creación de Task2 (pasamos el task_handler de Task1 como argumento)
    xTaskCreate(task2_function, "Task2", 2048, (void*)task_handler, 1, NULL);

    // Secuencia de cambios de estado (sin los print originales)
    vTaskDelay(3000 / portTICK_PERIOD_MS);

    // Tarea en suspensión
    vTaskSuspend(task_handler);
    vTaskDelay(3000 / portTICK_PERIOD_MS);

    // Reanudación
    vTaskResume(task_handler);
    vTaskDelay(3000 / portTICK_PERIOD_MS);

    // Suspensión
    vTaskSuspend(task_handler);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    
    // Eliminación
    vTaskDelete(task_handler);
    
    // Pequeña pausa antes de finalizar el main
    vTaskDelay(100 / portTICK_PERIOD_MS);
}