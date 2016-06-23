//-----------------------------------------------------------------------
// For the moment, we just test if the library compiles fine for an 
// arduino environment.
// TODO:
// * Use esp8266/lwip network 
//-----------------------------------------------------------------------
#include "wakaama_simple_client.h"
#include "wakaama_network.h"
#include "wakaama_object_utils.h"

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>

const char* client_name = "testClient";
lwm2m_context_t * client_context;

void setup() {
    client_context = lwm2m_client_init(client_name);
    //lwm2m_network_init(client_context, "12345");
}

void loop() {
    struct timeval tv = {2,0};
    uint8_t result = lwm2m_step(client_context, &tv.tv_sec);
    // result = network_step_blocking(client_context,client_bound_sockets);
}
