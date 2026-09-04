#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_log.h"

static const char* TAG = "P2_1_2";

// Callback function for the timer that occurs every second
void timer_callback_1(void* arg) {
    // 1. Convertimos (cast) el puntero genérico a un puntero a entero
    int* ticks = (int*) arg;
    
    // 2. Incrementamos el valor al que apunta
    (*ticks)++;

    // 3. Obtenemos el tiempo e imprimimos todo junto
    int64_t current_time = esp_timer_get_time();
    ESP_DRAM_LOGI(TAG, "Timer1 Tick (%lld us.) - Ticks: %d\n", current_time, *ticks);
}

// Callback function for the timer that occurs every 5 seconds
void timer_callback_2(void* arg) {
    // 1. Convertimos (cast) el puntero genérico a un puntero a entero
    int* ticks = (int*) arg;
    
    // 2. Incrementamos el valor al que apunta
    (*ticks)++;

    // 3. Obtenemos el tiempo e imprimimos todo junto
    int64_t current_time = esp_timer_get_time();
    ESP_DRAM_LOGI(TAG, "Timer2 Tick (%lld us.) - Ticks: %d\n", current_time, *ticks);
}

void app_main(void) {
    // Declaración de los contadores para cada temporizador
    int timer1_ticks = 0;
    int timer2_ticks = 0;

    // Timer 1: estructuras manejador y configurador
    esp_timer_handle_t timer1;
    esp_timer_create_args_t timer_args1 =
    {
        .callback = &timer_callback_1, // callback de interrupción
        .arg = &timer1_ticks,          // Pasamos la dirección de memoria de nuestro contador
        .name = "timer_1"
    };

    // creación del timer 1
    esp_timer_create(&timer_args1, &timer1);

    // Uso del timer 1: interrupción periódica cada segundo
    esp_timer_start_periodic(timer1, 1000000); // 1 second in microseconds

    // Timer 2 configurado de forma análoga
    esp_timer_handle_t timer2;
    esp_timer_create_args_t timer_args2 =
    {
        .callback = &timer_callback_2,
        .arg = &timer2_ticks,          // Pasamos la dirección de memoria de nuestro contador
        .name = "timer_2"
    };

    esp_timer_create(&timer_args2, &timer2);
    esp_timer_start_periodic(timer2, 5000000); // 5 segundos

    // Un bucle, para que la ejecución no se detenga. 
    // Como app_main no termina gracias a este bucle, las variables locales 
    // timer1_ticks y timer2_ticks se mantienen "vivas" en la memoria de la tarea.
    while (1);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    
}
