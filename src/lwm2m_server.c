#include "lwm2m/server.h"
#include "internal.h"
#include "wakaama/internals.h"
#include "lwm2m/debug.h"
#include "lwm2m/network.h"
#include "network/network_common.h"

#if defined(LWM2M_WITH_DTLS) && defined(LWM2M_SERVER_MODE)
void lwm2m_server_dtls_psk(lwm2m_context_t * context, const char* publicId, const char* psk, unsigned short pskLen) {
    network_t* network = (network_t*) context->userData;
    if (network->secretKey) {
        lwm2m_free(network->secretKey);
        network->secretKey=NULL;
        network->secretKeyLen=0;
    }

    if (network->publicIdentity) {
        lwm2m_free(network->publicIdentity);
        network->publicIdentity=NULL;
        network->publicIdLen=0;
    }

    if (publicId == NULL || psk == NULL) {
        network->dtls = false;
        network->publicIdentity = NULL;
    } else {
        network->dtls = true;
        network->publicIdLen = (unsigned short)strlen(publicId);
        network->publicIdentity = lwm2m_malloc(network->publicIdLen+1);
        strcpy(network->publicIdentity, publicId);
    }

    if (psk) {
       network->secretKey = lwm2m_malloc(pskLen);
       memcpy(network->secretKey, psk, pskLen);
       network->secretKeyLen = pskLen;
    }
}
#else
void lwm2m_server_dtls_psk(lwm2m_context_t * context, const char* publicId, const char* psk, unsigned short pskLen) {}
#endif
