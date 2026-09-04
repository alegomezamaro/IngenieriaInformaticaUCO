#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

const char* TAG = "P1_3_Polling_LED";
#define GPIO_LED 2

void app_main(void) {
    // Configuración del botón (Entrada con Pull-up)
    gpio_config_t io_conf_btn = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = (1ULL << CONFIG_GPIO_PIN),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_ENABLE
    };
    gpio_config(&io_conf_btn);

    // Configuración del LED (Salida)
    gpio_config_t io_conf_led = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << GPIO_LED),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE
    };
    gpio_config(&io_conf_led);

    uint8_t gpio_value;
    uint8_t last_value = 1; 
    while (1)
    {
        gpio_value = gpio_get_level(CONFIG_GPIO_PIN);
        gpio_set_level(GPIO_LED, gpio_value); 

        if (gpio_value == 0 && last_value == 1)
        {
            ESP_LOGI(TAG, "Botón pulsado!");

        }
        last_value = gpio_value;
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }


}
