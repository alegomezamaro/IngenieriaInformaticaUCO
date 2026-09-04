#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

const char* TAG = "P1_3";
#define LED_GPIO_PIN 2  // Definición del pin del LED

void app_main(void)
{
    // Configuración del GPIO para el botón
    gpio_config_t io_conf_button = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = (1ULL << CONFIG_GPIO_PIN),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_ENABLE
    };
    gpio_config(&io_conf_button);

    // Configuración del GPIO para el LED
    gpio_config_t io_conf_led = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << LED_GPIO_PIN),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE
    };
    gpio_config(&io_conf_led);

    uint8_t gpio_value;
    bool was_pressed = false;

    while (1)
    {
        gpio_value = gpio_get_level(CONFIG_GPIO_PIN);

        if (gpio_value == 0 && !was_pressed)
        {
            ESP_LOGI(TAG, "Botón pulsado!");
            was_pressed = true;  // Marca el botón como presionado
            gpio_set_level(LED_GPIO_PIN, 0);  // Apaga el LED
        }
        else if (gpio_value == 1)
        {
            if (was_pressed) {
                was_pressed = false;  // Reinicia el estado cuando el botón se libera
                gpio_set_level(LED_GPIO_PIN, 1);  // Enciende el LED
            }
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

