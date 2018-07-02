/*******************************************************************************
 * Copyright (c) 2017-2018  David Graeff <david.graeff@web.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 */
#pragma once

#include <mutex>
#include <thread>
#include <string>
#include "../wakaama/liblwm2m.h"

#include "../network/network_common.h"
#ifdef POSIX_NETWORK
#include <sys/epoll.h>
#endif

class Lwm2mServer {
public:
    Lwm2mServer(std::mutex* mutex);
    ~Lwm2mServer();
    void init(bool useDtls);
    void release();
    void loop();
    std::string getConnectClientName() const;
    inline void incClientUpdate() {++client_updated;}
public:
    lwm2m_context_t * server_context = nullptr;
    std::string connected_client_name;
    static const char PSK[];
    static unsigned short PSK_LEN;
    static const char PUBLICID[];
private:
    std::thread* thread = nullptr;
    std::mutex* mutex;
    int server_bound_sockets;
    int client_updated = 0;
    volatile bool server_running;
    #ifdef POSIX_NETWORK
    struct epoll_event ev;
    // Pipe to cancel the server thread
    int pfds[2]={0,0};
    #endif
};
