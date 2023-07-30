

#include "network.h"
#include <cstdio>
#include "pico/stdlib.h"
#include "pico/sleep.h"
#include "hardware/rosc.h"
#include "hardware/structs/scb.h"
#include "hardware/clocks.h"
#include "hardware/watchdog.h"


int send_notification(){
    if (!network_connect()){
        return 1;
    }

    tls_config = altcp_tls_create_config_client(NULL, 0);

    TLS_CLIENT_T *state = tls_client_init();
    if (!state) {
        return 2;
    }
    if (!tls_client_open(TLS_CLIENT_SERVER, state)) {
        return 2;
    }
    while(!state->complete) {
        sleep_ms(1000);
    }
    free(state);
    altcp_tls_free_config(tls_config);
    return 0;
}


void recover_from_sleep(uint scb_orig, uint clock0_orig, uint clock1_orig){

    //Re-enable ring Oscillator control
    rosc_write(&rosc_hw->ctrl, ROSC_CTRL_ENABLE_BITS);

    //reset procs back to default
    scb_hw->scr = scb_orig;
    clocks_hw->sleep_en0 = clock0_orig;
    clocks_hw->sleep_en1 = clock1_orig;

    //reset clocks
    clocks_init();
    stdio_init_all();

    return;
}


void software_reset()
{
    watchdog_enable(1, 1);
    while(1);
}

void blink(uint LED_PIN) {
    gpio_put(LED_PIN, 0);
    sleep_ms(250);
    gpio_put(LED_PIN, 1);
    sleep_ms(250);
    gpio_put(LED_PIN, 0);
}


int main() {
    const uint LED_PIN = 16;
    const uint WIFI_PIN = 23;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_set_dir(WIFI_PIN, GPIO_OUT);

    // start up sequence
    gpio_put(LED_PIN, 1);

    //save values for later
    uint scb_orig = scb_hw->scr;
    uint clock0_orig = clocks_hw->sleep_en0;
    uint clock1_orig = clocks_hw->sleep_en1;

    sleep_ms(800);
    gpio_put(LED_PIN, 0);
    sleep_ms(100);
    gpio_put(LED_PIN, 1);
    sleep_ms(150);
    gpio_put(LED_PIN, 0);
    sleep_ms(100);

    gpio_put(WIFI_PIN, 0);

    sleep_run_from_xosc();
    sleep_goto_dormant_until_edge_high(10);

    gpio_put(LED_PIN, 1);
    recover_from_sleep(scb_orig, clock0_orig, clock1_orig);
    gpio_put(LED_PIN, 0);

    gpio_put(WIFI_PIN, 1);

    blink(LED_PIN);
    blink(LED_PIN);
    gpio_put(LED_PIN, 1);
    send_notification();
    gpio_put(LED_PIN, 0);

    software_reset();

    return 0;
}
