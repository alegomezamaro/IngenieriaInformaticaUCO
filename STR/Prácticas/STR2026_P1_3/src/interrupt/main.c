#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"

const char* TAG="P1_3";
#define GPIO_LED 2

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    int level = gpio_get_level(CONFIG_GPIO_PIN);
    gpio_set_level(GPIO_LED, level);

    if (level == 0) {
        ESP_DRAM_LOGI(TAG, "¡Botón pulsado!");
    }
}

void app_main(void)
{
    gpio_reset_pin(GPIO_LED);
    gpio_set_direction(GPIO_LED, GPIO_MODE_OUTPUT);

    gpio_config_t io_conf = 
    {
        .intr_type = GPIO_INTR_ANYEDGE, 
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = (1ULL<<CONFIG_GPIO_PIN),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_ENABLE
    };
    
    ESP_ERROR_CHECK(gpio_config(&io_conf));
    ESP_ERROR_CHECK(gpio_install_isr_service(ESP_INTR_FLAG_SHARED));
    ESP_ERROR_CHECK(gpio_isr_handler_add(CONFIG_GPIO_PIN, gpio_isr_handler, NULL));

    gpio_set_level(GPIO_LED, gpio_get_level(CONFIG_GPIO_PIN));

    while (1)
    {
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
