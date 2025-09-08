//
// Created by 12933 on 25-9-7.
//
#include "cmsis_os.h"
#include"main.h"
#include"FreeRTOS.h"
#include "task.h"
#include "tim.h"


const uint32_t colors[] = {
    0xFF0000, // 红
    0x00FF00, // 绿
    0x0000FF, // 蓝
    0xFFFF00, // 黄
    0xFF00FF, // 紫
    0x00FFFF  // 青
};
const uint8_t num_colors = 6;


void breathing_led(uint32_t color, uint16_t duration_ms) {
    for (uint16_t i = 0; i < 1000; i++) {
        uint16_t brightness = (i < 500) ? i : 1000 - i;
        uint16_t r = ((color >> 16) & 0xFF) * brightness / 500;
        uint16_t g = ((color >> 8) & 0xFF) * brightness / 500;
        uint16_t b = (color & 0xFF) * brightness / 500;
        __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, r); // 红
        __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, g); // 绿
        __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, b); // 蓝
        osDelay(duration_ms / 1000);
    }
}
void led_task(void const * argument)
{
    while (1)
    {
        for (int i = 0; i < num_colors; i++) {
            breathing_led(colors[i],2000);
        }
    }
}