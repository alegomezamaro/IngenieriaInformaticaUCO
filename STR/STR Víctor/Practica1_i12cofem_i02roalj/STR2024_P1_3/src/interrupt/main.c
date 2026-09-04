#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"

const char* TAG = "P1_3";
#define LED_GPIO_PIN 2  // Definición del pin del LED

// Manejador de interrupción (ISR)
static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    // Leer el estado actual del botón
    int gpio_state = gpio_get_level(CONFIG_GPIO_PIN);

    if (gpio_state == 0) {
        // Botón está presionado
        gpio_set_level(LED_GPIO_PIN, 0); // Apaga el LED
        ESP_DRAM_LOGI(TAG, "Botón pulsado, LED apagado");
    } else {
        // Botón está liberado
        gpio_set_level(LED_GPIO_PIN, 1); // Enciende el LED
        ESP_DRAM_LOGI(TAG, "Botón liberado, LED encendido");
    }
}

void app_main(void)
{
    // Configuración inicial del GPIO para el botón
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_ANYEDGE,  // Interrupción en ambos flancos
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = (1ULL << CONFIG_GPIO_PIN),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_ENABLE
    };
    ESP_ERROR_CHECK(gpio_config(&io_conf));

    // Configuración del GPIO para el LED
    gpio_set_direction(LED_GPIO_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_GPIO_PIN, 1);  // Inicialmente el LED está encendido

    // Instala el servicio de ISR y añade el manejador
    ESP_ERROR_CHECK(gpio_install_isr_service(ESP_INTR_FLAG_SHARED));
    ESP_ERROR_CHECK(gpio_isr_handler_add(CONFIG_GPIO_PIN, gpio_isr_handler, NULL));

    while (1)
    {
        vTaskDelay(portTICK_PERIOD_MS * 1000);  // Bucle de espera con delay más largo
    }
}

