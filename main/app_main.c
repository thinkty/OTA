
#include "esp_event.h"
#include "esp_netif.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"

#include "app_ota.h"
#include "app_task_dht.h"
#include "app_task_cds.h"
#include "app_wifi.h"

void app_main()
{
    ESP_ERROR_CHECK(nvs_flash_init()); /* Initialize default NVS partition */
    ESP_ERROR_CHECK(esp_netif_init()); /* Initialize TCP/IP stack */
    ESP_ERROR_CHECK(esp_event_loop_create_default()); /* Create default event loop */

    /* Connect to WiFi */
    ESP_ERROR_CHECK(init_wifi());

    // Initialize OTA-update TODO:
    // ESP_ERROR_CHECK(init_ota());

    // Initialize and run the temperature/humidity sensor task
    ESP_ERROR_CHECK(init_dht());
    xTaskCreate(task_dht, "task_dht", DEFAULT_THREAD_STACKSIZE, NULL, DEFAULT_THREAD_PRIO, NULL);

    // Initialize and run the light sensor task
    ESP_ERROR_CHECK(init_cds());
    xTaskCreate(task_cds, "task_cds", DEFAULT_THREAD_STACKSIZE, NULL, DEFAULT_THREAD_PRIO, NULL);
}
