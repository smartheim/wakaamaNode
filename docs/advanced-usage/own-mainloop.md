The library can be integrated into your own select/poll/epoll based mainloop fairly easy,
because you have access to the native socket handlers via `lwm2m_network_native_sock(context,sock_no)`
and the next due time to call `lwm2m_process(context)`.

If you are already using the linux `epoll` API (or `wepoll` on Windows), you should have a look at the implementation of `lwm2m_block_wait` in  
[<img src="../../assets/github.png" style="width:20px"> network/network_posix.c](https://github.com/Openhab-Nodes/wakaamaNode/blob/master/src/network/network_posix.c#L326).

### Add own file descriptors to lwm2m_block_wait

You can access the epoll descriptor this way:

```cpp
#include "lwm2m/../../network/network_common.h"

network_t* network = (network_t*)contextP->userData;
int epoll_desc = network->epfd;
```

Add your file descriptor:

```cpp
struct epoll_event ev={ .events=EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP, {0} };
ev.data.fd=your_file_desc;
epoll_ctl(epoll_desc, EPOLL_CTL_ADD, your_file_desc, &ev);
```

### Example implementation of a select() based lwm2m_block_wait

```cpp
int lwm2m_block_wait(lwm2m_context_t * contextP, int timeout_in_sec) {
    network_t* network = (network_t*)contextP->userData;
    fd_set readfds = {{0}};
    unsigned sockets = network->open_listen_sockets;
    for (unsigned c = 0; c < sockets; ++c) {
        intptr_t sock = lwm2m_network_native_sock(contextP, c);
        if (sock == -1) continue;
        FD_SET(sock, &readfds);
    }

    int* due_time_sec = lwm2m_due_time(contextP);
    struct timeval next_event = {*due_time_sec, 0};
    const int select_result = select(FD_SETSIZE, &readfds, NULL, NULL, &next_event);
    
    // The timeout is actually for the next iteration (if no alarm
    // is requiring an ealier due time).
    *due_time_sec = timeout_in_sec;

    if (select_result < 0 && errno != EINTR) {
        fprintf(stderr, "Error in select(): %d %s\r\n", errno, strerror(errno));
        return -1;
    }

    for (unsigned c = 0; c < sockets; ++c) {
        const intptr_t sock = lwm2m_network_native_sock(contextP, c);
        if (sock != -1 && FD_ISSET(sock, &readfds)) {
            return (int)c;
        }
    }

    return 0;
}
```

