#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <lvgl.h>

#define SLEEP_TIME_MS 10

int main(void) {
    const struct device *display_dev;

    display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    if (!device_is_ready(display_dev)) {
        printk("Display device not ready\n");
        return 0;
    }
    printk("Display ready../n/r");

    lv_obj_t *hello_world_label = lv_label_create(lv_scr_act());
    lv_label_set_text(hello_world_label, "Hello Display!");
    lv_obj_align(hello_world_label, LV_ALIGN_CENTER, 0, 0);

    lv_task_handler();
    display_blanking_off(display_dev);

    while (1) {
        lv_timer_handler();
        k_msleep(SLEEP_TIME_MS);
    }
    return 0;
}