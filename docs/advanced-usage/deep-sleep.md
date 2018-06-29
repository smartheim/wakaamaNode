After a long deep sleep a new IP may be assigned by the DHCP/stateless-address-autoconfiguration part of your network layer.
This requires a new DTLS security context and a new lwM2M handshake,
therefore a proper session closing is recommended before entering deep sleep.

To ensure that all messages are sent and the (DTLS) session is shutdown correctly,
use the function `lwm2m_network_close(context)`. Reinitialize
the network after the deep sleep has finished with `lwm2m_network_init(context,port)`.

```cpp
#include "lwm2m/network.h"

void loop() {
  if (requestDeepsleep) {
    requestDeepsleep = false;
    lwm2m_network_close(CTX(context));
    
    ESP.deepSleep(); // Example call to enter deep sleep
    sleep(10); // Some time for the OS and network layer to recover
    
    lwm2m_network_init(CTX(context), 0);
  }
}
```
