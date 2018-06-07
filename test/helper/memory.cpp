#include "memory.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>

#include <iomanip>
#include <sstream>

#ifdef WITH_LIB_BACKTRACE
#include <execinfo.h> // gnu backtrace
#endif

#ifdef WITH_LIB_UNWIND
#include <libunwind.h>
#include <cxxabi.h>
#endif

MemoryObserver memoryObserver;

template< typename T >
std::string hexify(T i)
{
    std::stringbuf buf;
    std::ostream os(&buf);


    os << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2)
       << std::hex << i;

    return buf.str().c_str();
}

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WITH_LIB_UNWIND

std::string print_trace (void)
{
    unw_cursor_t cursor;
    unw_context_t context;

    // Initialize cursor to current frame for local unwinding.
    unw_getcontext(&context);
    unw_init_local(&cursor, &context);

    std::string a;
    // Unwind frames one by one, going up the frame stack.
    while (unw_step(&cursor) > 0) {
        unw_word_t offset, pc;
        unw_get_reg(&cursor, UNW_REG_IP, &pc);
        if (pc == 0) {
          break;
        }
        a += hexify(pc) + " ";

        char sym[256];
        if (unw_get_proc_name(&cursor, sym, sizeof(sym), &offset) == 0) {
            char* nameptr = sym;
            int status;
            char* demangled = abi::__cxa_demangle(sym, nullptr, nullptr, &status);
            if (status == 0) nameptr = demangled;
            std::string l(nameptr);
            if (l.find("TestBody")!=std::string::npos) continue;
            a += l + " (" + hexify(offset)+") \n";
        } else {
            a += "no symbol for this frame\n";
        }
    }

    return a;
}

#elif defined(WITH_LIB_BACKTRACE)
std::string print_trace (void)
{
    void *array[10];
    size_t size;
    char **strings;
    size_t i;

    size = backtrace (array, 10);
    strings = backtrace_symbols (array, size);

    std::string a;
    for (i = 1; i < size; i++){
        std::string l(strings[i]);
        if (l.find("libgtest")!=std::string::npos) continue;
        a+= l;
        a+="\n";
    }

    free (strings);

    return a;
}
#else
std::string print_trace (void) { return std::string(); }
#endif

void* lwm2m_malloc(size_t s)
{
    void* mem = malloc(s);
    memoryObserver.add((long)mem, print_trace());
    return mem;
}

void lwm2m_free(void * p)
{
    memoryObserver.remove((long)p);
    free(p);
}

char* lwm2m_strdup(const char * str)
{
    char* mem = strdup(str);
    memoryObserver.add((long)mem, print_trace());
    return mem;
}

#ifdef __cplusplus
}
#endif
