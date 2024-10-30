#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_system.h"

void app_main(void)
{
    printf("Hello from ESP32!\n");

    // แสดงข้อมูลชิป
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("CPU Cores: %d, WiFi: %s, Bluetooth: %s\n", 
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "Yes" : "No",
           (chip_info.features & CHIP_FEATURE_BT) ? "Yes" : "No");

    // แสดงข้อมูลหน่วยความจำว่าง
    printf("Free Heap Size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());

    // นับถอยหลังและรีสตาร์ท
    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    esp_restart();
}
