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
#include "server.h"
#include "lwm2m/c_connect.h"
#include "lwm2m/server.h"
#include "lwm2m/network.h"
#include "with_lwip/lwip_tap_helper.h"
#include <gtest/gtest.h>

const char Lwm2mServer::PSK[] = "psk";
unsigned short Lwm2mServer::PSK_LEN = 3;
const char Lwm2mServer::PUBLICID[] = "publicid";

static void prv_monitor_callback(uint16_t clientID,
                                 lwm2m_uri_t * uriP,
                                 int status,
                                 lwm2m_media_type_t format,
                                 uint8_t * data,
                                 int dataLength,
                                 void * userData)
{
    (void)uriP; (void)format; (void)data; (void)dataLength;
    Lwm2mServer* t = (Lwm2mServer*) userData;
    lwm2m_context_t * lwm2mH = t->server_context;
    lwm2m_client_t * targetP;

    switch (status)
    {
    case COAP_201_CREATED:
        targetP = (lwm2m_client_t *)lwm2m_list_find((lwm2m_list_t *)lwm2mH->clientList, clientID);
        t->connected_client_name = targetP->name;
        //prv_dump_client(targetP);
        break;

    case COAP_202_DELETED:
        t->connected_client_name.clear ();
        break;

    case COAP_204_CHANGED:
        t->incClientUpdate();
        //prv_dump_client(targetP);
        break;

    default:
        break;
    }
}

Lwm2mServer::Lwm2mServer(std::mutex* mutex) : mutex(mutex) {

}

std::string Lwm2mServer::getConnectClientName() const {
    return connected_client_name;
}

void Lwm2mServer::init(bool useDtls) {
    if (server_context) return;
    assert(thread==nullptr);

    client_updated = 0;
    connected_client_name.clear ();
    
    server_context = lwm2m_init(nullptr);
    server_context->state = STATE_READY;
    ASSERT_TRUE(server_context);

    //// init server thread ////

    // Install a monitoring callback for the server lwm2m context.
    // We check for the COAP_201_CREATED and COAP_202_DELETED events
    lwm2m_set_monitoring_callback(server_context, prv_monitor_callback, this);
    int server_bound_sockets = lwm2m_network_init(server_context,
                                              useDtls ? LWM2M_DEFAULT_SECURE_SERVER_PORT : LWM2M_DEFAULT_SERVER_PORT);
    ASSERT_LE(1, server_bound_sockets);
    ASSERT_TRUE(server_context->userData!=NULL);

    //// If DTLS: Set server public ID and preshared key
    if (useDtls)
        lwm2m_server_dtls_psk(server_context,PUBLICID,PSK,PSK_LEN);
    
    server_running = true;

    #ifdef POSIX_NETWORK
    pipe(pfds);
    ev.events=EPOLLIN | EPOLLPRI | EPOLLONESHOT;
    ev.data.fd=pfds[0];
    errno=0;
    network_t* network = (network_t*)server_context->userData;
    epoll_ctl(network->epfd, EPOLL_CTL_ADD, ev.data.fd, &ev);
    assert (errno==0);
    #endif

    thread = new std::thread([this]() { loop(); });
}

void Lwm2mServer::loop() {
    while (server_running) {
        struct timeval next_event = {0,50*1000};
        {
            std::lock_guard<std::mutex> guard(*mutex);
            lwm2m_process (server_context,&next_event);
        }
        lwm2m_block_wait(server_context,next_event);
    }
    int last10 = 10;
    while (last10--) {
        struct timeval next_event = {0,5000};
        {
            std::lock_guard<std::mutex> guard(*mutex);
            lwm2m_process (server_context,&next_event);
            if (!server_context->serverList ||
                    server_context->serverList->status==STATE_DEREGISTERED)
                break;
        }
        lwm2m_block_wait(server_context,next_event);
    }
}

Lwm2mServer::~Lwm2mServer() {
    release();
}

void Lwm2mServer::release() {
    if (!server_context) return;
    
    server_running=false;
    #ifdef POSIX_NETWORK
    char c = 1;
    write(pfds[1], &c, 1);
    #endif
    thread->join();
    delete thread;
    thread = nullptr;

    #ifdef POSIX_NETWORK
    close(pfds[0]);
    close(pfds[1]);
    #endif

    lwm2m_close (server_context);
    lwm2m_network_close(server_context);
    lwm2m_free(server_context);
    server_context = nullptr;
}
