#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "esp_log.h"
#include "SEGGER_SYSVIEW.h"

static const char* TAG = "P3_1_1";

// Estructura para configurar una tarea
typedef struct task_config_t
{
    char task_name [10];
    uint16_t matrix_size;
    uint16_t iterations;
    uint16_t period; // msecs.
}task_config_t;

// Función auxiliar para introducir un procesamiento de duración variable
void matrix_multiply(uint16_t matrix_size, uint16_t iterations)
{
    float matrix_A[matrix_size][matrix_size];
    float matrix_B[matrix_size][matrix_size];
    float result[matrix_size][matrix_size];

    uint16_t i, j, k, iter;

    // Rellena la matriz con valores aleatorios
    // ESP_LOGI(TAG, "matrix_multiply: %d x %d elementos, %d veces", matrix_size, matrix_size, iterations);
    for (i = 0; i < matrix_size; ++i)
    {
        for (j = 0; j < matrix_size; ++j)
        {
            matrix_A[i][j] = (float)rand();
            matrix_B[i][j] = (float)rand();
        }
    }

    // multiplicación de matrices
    for (iter = 0; iter < iterations; ++iter)
    {
        for (i = 0; i < matrix_size; ++i)
        {
            for (j = 0; j < matrix_size; ++j)
            {
                result[i][j] = 0.0;
                for (k = 0; k < matrix_size; ++k)
                {
                    result[i][j] += matrix_A[i][k] * matrix_B[k][j];
                }
            }
        }
    }
}

// Callback del timer de la tarea
void timer_callback(TimerHandle_t xTimer)
{
    SemaphoreHandle_t *pxSemaphore = (SemaphoreHandle_t *)pvTimerGetTimerID(xTimer);
    // libera semáforo para iteración
    xSemaphoreGiveFromISR(*pxSemaphore, pdFALSE);
}

// Tarea
void task(void *pvParameters)
{
    task_config_t* config = (task_config_t *) pvParameters;
    SemaphoreHandle_t sync_sem = xSemaphoreCreateBinary();
    char tmrname[50];
    sprintf(tmrname, "PeriodicTimer[%s]", config->task_name);
    TimerHandle_t timer = xTimerCreate("PeriodicTimer", pdMS_TO_TICKS(config->period), pdTRUE, (void *)&sync_sem, timer_callback);
    xTimerStart(timer,0);
    while (1)
    {
        ESP_LOGI(TAG, "%s: Multiplicando matriz aleatoria...", config->task_name);
        matrix_multiply(config->matrix_size, config->iterations);
        ESP_LOGI(TAG, "%s: Multiplicación finalizada.", config->task_name);
        // bloquea a la espera del timer
        xSemaphoreTake(sync_sem, portMAX_DELAY);
    }
}

void app_main()
{
    // Configura e inicia el proceso de captura de eventos de Segger SystemView
    SEGGER_SYSVIEW_Conf();
    SEGGER_SYSVIEW_Start();

    // Estructuras de datos para configurar las tareas
    task_config_t config_t1 = {"t1", 50, 10, 100}; // tarea frecuente pero rápida
    task_config_t config_t2 = {"t2", 50, 10, 500}; // tarea poco frecuente pero lenta
    // Creación de las tareas
    xTaskCreatePinnedToCore(task, "TaskA", 50*1024, (void*) &config_t1, 2, NULL, 0); // tarea 1, core 0, prioridad 1
    xTaskCreatePinnedToCore(task, "TaskB", 50*1024, (void*) &config_t2, 1, NULL, 0); // tarea 2, core 0, prioridad 1
    
    // Loop
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}