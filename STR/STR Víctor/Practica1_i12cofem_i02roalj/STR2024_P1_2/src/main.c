#include "stdio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_chip_info.h"
#include "esp_clk_tree.h"

void app_main() {
    // Verifica cuál de las opciones ha sido seleccionada (si MI_OPCION_ABC está habilitado)
    #ifdef CONFIG_MI_OPCION_ABC
    #if defined(CONFIG_OPCION_A)
    printf("Has seleccionado la Opción A\n");
    #elif defined(CONFIG_OPCION_B)
    printf("Has seleccionado la Opción B\n");
    #elif defined(CONFIG_OPCION_C)
    printf("Has seleccionado la Opción C\n");
    #endif
    #else
    printf("La selección de opciones ABC está deshabilitada.\n");
    #endif

    // Imprime si la opción en el submenu está activada
    #ifdef CONFIG_MI_SUBMENU_OPCION
    printf("La opción en submenu está activada.\n");
    #endif

    // Muestra el valor numérico configurado
    printf("El valor numérico configurado es: %d\n", CONFIG_MI_SUBMENU_OPCION_NUMERICA);
}

