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
#include "lwm2m/connect.h"
#include "lwm2m/c_connect.h"
#include "wakaama/internals.h"
#include "lwm2m/debug.h"
#include "lwm2m/network.h"
#include "network/network_common.h"

LwM2MConnect::LwM2MConnect(const char * endpointName) : lwm2m_client_context_t{} {
    lwm2m_client_init(this, endpointName);
}

LwM2MConnect::~LwM2MConnect() { lwm2m_client_close (this); }

void LwM2MConnect::process() { lwm2m_process (&this->context); }

int LwM2MConnect::block_wait(unsigned timeout_in_sec) { return lwm2m_block_wait (&this->context, timeout_in_sec); }


bool LwM2MConnect::add_server(uint16_t shortServerID,
                             const char* uri, uint32_t lifetime, bool storing) { return lwm2m_add_server (&this->context, shortServerID, uri, lifetime, storing); }


#ifdef LWM2M_WITH_DTLS
bool LwM2MConnect::use_dtls_psk(uint16_t shortServerID, const char* publicId,
                               const char* psk, unsigned short pskLen) { return lwm2m_use_dtls_psk(&this->context,shortServerID,publicId,psk,pskLen); }
#endif

//bool security_use_certificate(uint16_t shortServerID,
//      const char* certificates, unsigned short certificatesLen) { return lwm2m_security_use_certificate(this,shortServerID,certificates,certificatesLen); }

bool LwM2MConnect::unregister_server(uint16_t security_instance_id) { return lwm2m_unregister_server(&this->context, security_instance_id); }

void LwM2MConnect::remove_unregistered_servers() { lwm2m_remove_unregistered_servers(&this->context); }

const char* LwM2MConnect::get_server_uri(uint16_t shortServerID) { return lwm2m_get_server_uri(&this->context, shortServerID); }

bool LwM2MConnect::is_connected() { return lwm2m_is_connected(&this->context); }

int LwM2MConnect::socket_count() { return ((network_t*)context.userData)->open_listen_sockets;}
