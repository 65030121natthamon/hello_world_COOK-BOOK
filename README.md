## แนวทางการทำงาน ESP32 project cook book
1. ระบุตัวอย่างที่ใช้ ว่าเอามาจากตัวอย่างไหน
   - มาจาก example hello_world
    ![image](https://github.com/user-attachments/assets/5c7aa610-179b-4f41-bd2f-48ac7fcab965)
   - ในตัวอย่างนี้เป็นการพิมพ์ Hello world ออกมาและ restartทุกๆ10วินาที จะมีการนับ ถอยหลัง 10-0
   - โค้ดมีการปรับแก้ไขให้นับจำนวน แสดงข้อมูลเกี่ยวกับชิป ESP32 
2. ระบุว่า จะแก้ไขตรงไหนบ้าง เพื่ออะไร
   - แก้ไขโค้ดในส่วนโค้ดไฟล์hello_world_main.c
```
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

```
3. แสดงขั้นตอนการทำ project
   - สร้างโปรเจคจาก example   hello_world
   - ทดสอบการทำงานของโปรเจค
   - ทำการแก้ไขเนื้อหาโค้ดให้เป็นไปตามที่ต้องการ
   - และทำการ build หลังจากเรียบร้อยแล้วทำการ flash และ monitor
4. แสดงผลการทำ project
   - จะมีการแสดงผลดังรูป
     ![image](https://github.com/user-attachments/assets/6b5711fc-392e-4e10-832e-e10c24243937)
* วนลูปนับถอยหลังจาก 10 ถึง 0 วินาที ใช้เวลา 1 วินาที เหมือนเดิม (vTaskDelay(1000 / portTICK_PERIOD_MS))
และจะทำการ restart ข้อมูลใหม่
* แสดงข้อความแสดงข้อความ "Hello from ESP32!"
* แสดงจำนวน CPU cores
* ตรวจสอบว่าชิปมี WiFi หรือ Bluetooth โดยตรวจสอบผ่าน chip_info.features
(ใช้esp_chip_info ดึงข้อมูลชิปและเก็บลงในตัวแปร chip_info)
5. สรุปผลการทำ project
   - โปรเจคแสดงชิปและขนาดหน่วยความจำที่เหลืออยู่
   - ใช้ในการตรวจสอบสถานะการทำงานของ ESP32 แสดงชิปและขนาดหน่วยความจำที่เหลืออยู่ 
