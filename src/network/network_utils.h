#pragma once

#include <stdint.h>

struct _connection_t_;

typedef enum {
    NET_CLIENT_PROCESS,
    NET_SERVER_PROCESS
} network_process_type_t;

typedef struct _network_t_ {
    int* socket_handle;
    int open_listen_sockets;
    struct _connection_t_* connection_list;
    network_process_type_t type;
    void* net_if_out;
} network_t;

uint8_t decode_uri(char* uri, char** host, char** port);
