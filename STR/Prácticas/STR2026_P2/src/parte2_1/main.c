#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
static const char* TAG ="P2_2_2";
// Código de la tarea
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
// Función auxiliar para imprimir por pantalla el estado de una tarea
void print_task_state (TaskHandle_t handler)
{
    TaskStatus_t task_status;
    vTaskGetInfo(handler, &task_status, pdTRUE, eInvalid);
    printf("\nTask STATE: ");
    switch (task_status.eCurrentState)
    {
        case eRunning:
        printf("RUNNING\n");
        break;
        case eReady:
        printf("READY\n");
        break;
        case eBlocked:
        printf("BLOCKED\n");
        break;
        case eSuspended:
        printf("SUSPENDED\n");
        break;
        case eDeleted:
        printf("DELETED\n");
        break;
        default:
        printf("UNKNOWN\n");
        break;
    }
}

void app_main()
{
    TaskHandle_t task_handler; // Variable de tipo manejador de tarea
    ESP_LOGI(TAG, "app_main: despliegue de la tarea.");
    // Función para crear tareas
    xTaskCreate(task_function, "Task", 2048, NULL, 1, &task_handler);
    // Tarea activa
    print_task_state(task_handler);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    // Tarea en suspensión
    vTaskSuspend(task_handler);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    print_task_state(task_handler);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    // Reanudación
    vTaskResume(task_handler);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    print_task_state(task_handler);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    // Suspensión
    vTaskSuspend(task_handler);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    print_task_state(task_handler);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    // Eliminación
    vTaskDelete(task_handler);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    print_task_state(task_handler);
}