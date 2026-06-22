#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_log.h"

static const char* TAG = "P2_1_1";

void app_main(void)
{
    int matrix1 [CONFIG_MATRIX_SIZE] [CONFIG_MATRIX_SIZE];
    int matrix2 [CONFIG_MATRIX_SIZE] [CONFIG_MATRIX_SIZE];
    int result [CONFIG_MATRIX_SIZE] [CONFIG_MATRIX_SIZE];

    for(int i = 0; i < CONFIG_MATRIX_SIZE; i++) 
    {
        for(int j = 0; j < CONFIG_MATRIX_SIZE; j++) 
        {
            matrix1[i][j] = rand() % 10; 
            matrix2[i][j] = rand() % 10;
        }
    }

    uint64_t start_time = esp_timer_get_time();

    for(int i = 0; i < CONFIG_MATRIX_SIZE; i++) 
    {
        for(int j = 0; j < CONFIG_MATRIX_SIZE; j++) 
        {
            result[i][j] = 0;
            for(int k = 0; k < CONFIG_MATRIX_SIZE; k++) 
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    uint64_t end_time = esp_timer_get_time();
    double elapsed_time = (double)(end_time - start_time);
    ESP_LOGI(TAG, "Matrix multiplication completed in %.2f us", elapsed_time);
}