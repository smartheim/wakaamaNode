# libWakaamaEmb
[![Build Status](https://travis-ci.org/Openhab-Nodes/libWakaamaEmb.svg?branch=master)](https://travis-ci.org/Openhab-Nodes/libWakaamaEmb)

Wakaama provided as an Arduino and PlattformIO library.
Wakaama (formerly liblwm2m) is an implementation of the Open Mobile Alliance's LightWeight M2M protocol (LWM2M).

### Porting
src/platform_esp8266.c implements the following methods:

* lwm2m_malloc(size_t s)
* void lwm2m_free(void * p)
* char * lwm2m_strdup(const char * str)
* int lwm2m_strncmp(const char * s1, const char * s2,  size_t n)
* time_t lwm2m_gettime(void)
* void lwm2m_printf(const char * format, ...)

src/network_lwip_sockets.c implements the following methods:
* uint8_t lwm2m_buffer_send(void * sessionH,
                          uint8_t * buffer,
                          size_t length,
                          void * userdata)
* bool lwm2m_session_is_equal(void * session1,
                            void * session2,
                            void * userData)
* void * lwm2m_connect_server(uint16_t secObjInstID,
                            void * userData)
* // Returns socket identifier
  void * lwm2m_create_socket()
* // Free socket
  void lwm2m_free_socket(void * socket)
* // Return true if a new data packet is received
  bool lwm2m_has_data(void * socket)
* // Copies received data to buffer and return size of data
  int lwm2m_receive_data(void * socket, uint8_t * buffer, int buffer_size)
* // Return true if binding to the given address succeeded.
  // uri is for example: coap://a-coap-server.org or coaps://192.168.0.107
  bool udp_bind_to_coap_server(void * socket, char * uri)



### Demo/Example
* An example for the ESP8266 is located in examples/.

### License
This platform code and API wrappers are provided under the MIT license.
Wakaama is provided under the Eclipse Public License - v 1.0.
