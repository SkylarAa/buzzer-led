#include "cmsis_os.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "tim.h"

// 音符频率（Hz）
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_F5  440
#define NOTE_G5  494
#define NOTE_F6  523


// 旋律：音符 + 时长（ms）
const uint16_t melody_notes[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_F5, NOTE_G5, NOTE_F6};
const uint16_t melody_durations[] = {500, 500, 500, 500, 500, 500, 500, 500};
const uint8_t melody_length = 8;

void buzzer_set_frequency(uint16_t freq) {
    if (freq == 0) {
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0);
        return;
    }
    uint32_t period = 2000000 / freq; // 2 MHz / freq
    if (period > 65535) {
        period = 65535; // 限制最大值
    }
    __HAL_TIM_SET_AUTORELOAD(&htim4, period - 1);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, period / 2); // 50% 占空比
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
}

void buzzer_task(void const * argument) {
    while (1) {
        for (int i = 0; i < melody_length; i++) {
            buzzer_set_frequency(melody_notes[i]);
            osDelay(melody_durations[i]);
        }
        buzzer_set_frequency(0); // 停止
        vTaskDelay(200);
    }
}