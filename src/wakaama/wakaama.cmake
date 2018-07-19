# Provides WAKAAMA_SOURCES_DIR and WAKAAMA_SOURCES and WAKAAMA_DEFINITIONS variables.
# Add LWM2M_WITH_LOGS to compile definitions to enable logging.

set(WAKAAMA_SOURCES_DIR ${CMAKE_CURRENT_LIST_DIR})

set(EXT_SOURCES 
    ${WAKAAMA_SOURCES_DIR}/er-coap-13/er-coap-13.c
	${WAKAAMA_SOURCES_DIR}/er-coap-13/er-coap-13.h)

set(CORE_HEADERS
    ${WAKAAMA_SOURCES_DIR}/liblwm2m.h
    
    ${WAKAAMA_SOURCES_DIR}/uri.h
    ${WAKAAMA_SOURCES_DIR}/utils.h
    ${WAKAAMA_SOURCES_DIR}/objects.h
    ${WAKAAMA_SOURCES_DIR}/tlv.h
    ${WAKAAMA_SOURCES_DIR}/data.h
    ${WAKAAMA_SOURCES_DIR}/list.h
    ${WAKAAMA_SOURCES_DIR}/packet.h
    ${WAKAAMA_SOURCES_DIR}/transaction.h
    ${WAKAAMA_SOURCES_DIR}/registration.h
    ${WAKAAMA_SOURCES_DIR}/bootstrap.h
    ${WAKAAMA_SOURCES_DIR}/observe.h
    ${WAKAAMA_SOURCES_DIR}/json.h
    ${WAKAAMA_SOURCES_DIR}/discover.h
    ${WAKAAMA_SOURCES_DIR}/block1.h
    ${WAKAAMA_SOURCES_DIR}/context.h
    ${WAKAAMA_SOURCES_DIR}/debug.h
    ${WAKAAMA_SOURCES_DIR}/communication.h
    ${WAKAAMA_SOURCES_DIR}/server_clientlist.h
    ${WAKAAMA_SOURCES_DIR}/lwm2m_server.h
    ${WAKAAMA_SOURCES_DIR}/lwm2m_client.h
    )

set(WAKAAMA_SOURCES
    ${WAKAAMA_SOURCES_DIR}/liblwm2m.c
    ${WAKAAMA_SOURCES_DIR}/uri.c
    ${WAKAAMA_SOURCES_DIR}/utils.c
    ${WAKAAMA_SOURCES_DIR}/objects.c
    ${WAKAAMA_SOURCES_DIR}/tlv.c
    ${WAKAAMA_SOURCES_DIR}/data.c
    ${WAKAAMA_SOURCES_DIR}/list.c
    ${WAKAAMA_SOURCES_DIR}/packet.c
    ${WAKAAMA_SOURCES_DIR}/transaction.c
    ${WAKAAMA_SOURCES_DIR}/registration.c
    ${WAKAAMA_SOURCES_DIR}/bootstrap.c
    ${WAKAAMA_SOURCES_DIR}/management.c
    ${WAKAAMA_SOURCES_DIR}/observe.c
    ${WAKAAMA_SOURCES_DIR}/json.c
    ${WAKAAMA_SOURCES_DIR}/discover.c
    ${WAKAAMA_SOURCES_DIR}/block1.c
    ${WAKAAMA_SOURCES_DIR}/internals.h
	${CORE_HEADERS}
    ${EXT_SOURCES})

