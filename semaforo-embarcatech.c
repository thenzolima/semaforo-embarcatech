#include <stdio.h>
#include "pico/stdlib.h"

#define LED_GREEN_PIN 11
#define LED_YELLOW_PIN 12
#define LED_RED_PIN 13

static uint8_t current_led_pin = LED_RED_PIN;

void set_leds(bool red, bool yellow, bool green);
bool timer_callback(struct repeating_timer *timer);
void display_timer();

int main()
{
    stdio_init_all();

    gpio_init(LED_RED_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    gpio_init(LED_YELLOW_PIN);
    gpio_set_dir(LED_YELLOW_PIN, GPIO_OUT);

    set_leds(true, false, false);

    struct repeating_timer timer;

    add_repeating_timer_ms(3000, timer_callback, NULL, &timer);

    while (true) {
        display_timer();
        sleep_ms(1000);
    }
}

void set_leds(bool red, bool yellow, bool green)
{
    gpio_put(LED_RED_PIN, red);
    gpio_put(LED_YELLOW_PIN, yellow);
    gpio_put(LED_GREEN_PIN, green);
}

bool timer_callback(struct repeating_timer *timer)
{
    set_leds(current_led_pin == LED_RED_PIN, current_led_pin == LED_YELLOW_PIN, current_led_pin == LED_GREEN_PIN);

    if (current_led_pin == LED_RED_PIN) {
        current_led_pin = LED_YELLOW_PIN;
    } else if (current_led_pin == LED_YELLOW_PIN) {
        current_led_pin = LED_GREEN_PIN;
    } else {
        current_led_pin = LED_RED_PIN;
    }

    return true;
}

void display_timer()
{
    static int timer = 3;
    if (timer == 0) timer = 3;
    printf("Tempo restante: %d\n", timer--);
}
