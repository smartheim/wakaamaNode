#include "lwm2m/events.h"

void EventDispatcher::dispatch(int result, lwm2m_context_t* context) {
    connected();
}
