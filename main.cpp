

#include "network.h"


int main() {
    stdio_init_all();
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
