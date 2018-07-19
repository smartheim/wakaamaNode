#pragma once

/*
 * Error code
 */
typedef enum {
    COAP_NO_ERROR                   =(uint8_t)0x00,
    COAP_IGNORE                     =(uint8_t)0x01,
    COAP_CONNECT_FAIL               =(uint8_t)0x02,

    COAP_201_CREATED                =(uint8_t)0x41,
    COAP_202_DELETED                =(uint8_t)0x42,
    COAP_204_CHANGED                =(uint8_t)0x44,
    COAP_205_CONTENT                =(uint8_t)0x45,
    COAP_231_CONTINUE               =(uint8_t)0x5F,
    COAP_400_BAD_REQUEST            =(uint8_t)0x80,
    COAP_401_UNAUTHORIZED           =(uint8_t)0x81,
    COAP_402_BAD_OPTION             =(uint8_t)0x82,
    COAP_403_FORBIDDEN              =(uint8_t)0x83,
    COAP_404_NOT_FOUND              =(uint8_t)0x84,
    COAP_405_METHOD_NOT_ALLOWED     =(uint8_t)0x85,
    COAP_406_NOT_ACCEPTABLE         =(uint8_t)0x86,
    COAP_408_REQ_ENTITY_INCOMPLETE  =(uint8_t)0x88,
    COAP_412_PRECONDITION_FAILED    =(uint8_t)0x8C,
    COAP_413_ENTITY_TOO_LARGE       =(uint8_t)0x8D,
    COAP_500_INTERNAL_SERVER_ERROR  =(uint8_t)0xA0,
    COAP_501_NOT_IMPLEMENTED        =(uint8_t)0xA1,
    COAP_503_SERVICE_UNAVAILABLE    =(uint8_t)0xA3
} lwm2m_error_codes_t;
