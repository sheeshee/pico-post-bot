# pico-post-bot

A simple PicoW-powered device that notifies me when I have post

# Build Instructions

```
$ mkdir build
$ cd build
$ export PICO_SDK_PATH=../../pico-sdk
$ export PICO_SSID="Your Wifi Network Name"
$ export PICO_SSID_PASSWORD="Some Password"
$ export PICO_IFTTT_KEY="Some IFTTT key"
$ cmake ..
$ make
```

# Open Serial Port

```
$ minicom -b 115200 -o -D /dev/ttyACM0
```

# For Reference

## Blink an LED

```
#include "pico/stdlib.h"

int main() {
    const uint LED_PIN = 15;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
    }
}
```

## Read a button

```
#include "pico/stdlib.h"

int main() {
    // int state = 1;
    bool trigger = false;
    const uint LED_PIN = 16;
    const uint BUTTON_PIN = 17;
    gpio_init(BUTTON_PIN);
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    while (true) {
        trigger = gpio_get(BUTTON_PIN);
        gpio_put(LED_PIN, trigger);
        sleep_ms(10);

    }
}
```
