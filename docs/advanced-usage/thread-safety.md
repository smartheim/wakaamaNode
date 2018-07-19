The library itself is not thread safe to save runtime cost.
You need to push new data into the library in the same thread that handles received data.
Lwm2m object instances and resources may only be manipulated within the same thread as well. 

### How to read object instance data from another thread?

Create a Mutex and lock the access to `lwm2m_network_process`.
Whenever you want to access object instance resources, lock the mutex as well, for example:

```cpp
#include <mutex>
std::mutex m;

// Changed sources of network/network_posix.c
inline int lwm2m_process(lwm2m_context_t *contextP) {
    std::lock_guard<std::mutex> lock(m);
    ...
}

void myOtherThreadLoop() {
    ...
    // Access object instance data
    {
        std::lock_guard<std::mutex> lock(m);
        if (my_object_instance.my_res == 3)
            do_something();
    }
    ...
}


```

### How to write object instance data from another thread?

The safest way is to use a thread safe queue that you push your object instance resource changes into
and which is processed in your lwM2M thread.

### How to react on object instance changes in another thread?

Create a Mutex and lock the access to `lwm2m_network_process`.
Whenever you receive data via the `writeVerify` callback for example, lock the mutex as well.
