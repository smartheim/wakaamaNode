After a deep sleep a new IP may be assigned, which requires a new DTLS security context and a new lwM2M handshake, therefore a proper session closing is recommended. To ensure that all messages are sent and the session is shutdown correctly,  do a `lwm2m_network_close(lwm2mH);` and `lwm2m_client_close();`. This will disconnect everything cleanly, so that you can call `ESP.deepSleep()`. 

```c++
void reconnect() {
  // ...
}

void loop() {
  if (requestDeepsleep) {
    requestDeepsleep = false;
    lwm2m_network_close(lwm2mH);
    lwm2m_client_close();
    
    ESP.deepSleep();
    
    sleep(10);
    reconnect();
  }
}
```
