#ifndef LED_H
#define LED_H

void breathing_led(uint32_t color, uint16_t duration_ms);
void led_task(void const * argument);

#endif
