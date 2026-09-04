#include <stdio.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_chip_info.h"
#include "esp_clk_tree.h"
const char* TAG = "P1_2";
// Función para obtener el nombre del modelo como cadena
const char* get_chip_model_name(esp_chip_model_t model) {
    switch (model) {
        case CHIP_ESP32: return "ESP32";
        case CHIP_ESP32S2: return "ESP32-S2";
        case CHIP_ESP32S3: return "ESP32-S3";
        case CHIP_ESP32C3: return "ESP32-C3";
        case CHIP_ESP32C2: return "ESP32-C2";
        case CHIP_ESP32C6: return "ESP32-C6";
        case CHIP_ESP32H2: return "ESP32-H2";
        case CHIP_POSIX_LINUX: return "POSIX/Linux Simulator";
        default: return "Unknown";
    }
}
void app_main(void){

    // Estructura para almacenar información del chip
    esp_chip_info_t chip_info;
    // Entero para almacenar la frecuencia de la CPU
    uint32_t freq;
    ESP_LOGI(TAG, "Hello ESP32!");
    ESP_LOGI(TAG, "Lucía, Alba Rueda");
    ESP_LOGI(TAG, "Alejandro, Gómez Amaro");
    // ...
    // ESP_LOGI(TAG, "<NombreN>, <ApellidosN>");
    // Obtener información del chip
    esp_chip_info(&chip_info);
    if (esp_clk_tree_src_get_freq_hz(SOC_MOD_CLK_CPU,
    ESP_CLK_TREE_SRC_FREQ_PRECISION_EXACT, &freq) != ESP_OK){
        ESP_LOGI(TAG, "Error obteniendo la frecuencia de la CPU");
        freq = 0;
    }

        //AGREGADO P1.2 APARTADO 4.2
        printf("P1.2.4.2: Valores cargados desde menuconfig:\n");
        #ifdef CONFIG_MI_VARIABLE_BOOL
            for(int i = 0; i < CONFIG_MI_VARIABLE_INT; i++) {
                printf("- Hola %s, repeticion %d\n", CONFIG_MI_VARIABLE_STRING, i+1);
            }
        #endif
        // Imprimir el valor hexadecimal
        printf("- Valor Hexadecimal configurado: 0x%X\n", CONFIG_MI_VARIABLE_HEX);
        // Imprimir la opción seleccionada en el bloque 'choice'
        #ifdef CONFIG_PLACA_V1
            printf("- Placa seleccionada: Version 1.0\n");
        #elif defined(CONFIG_PLACA_V2)
            printf("- Placa seleccionada: Version 2.0\n");
        #endif

    // Formatear la cadena con el modelo de chip y el número de cores
    ESP_LOGI(TAG, "Modelo: %s, Cores: %d, Frecuencia: %ld", get_chip_model_name(chip_info.model),
    chip_info.cores, freq);
}
