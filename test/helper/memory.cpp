/*******************************************************************************
 * Copyright (c) 2017-2018  David Graeff <david.graeff@web.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 */
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

bool contains(const std::string& src, const char* expr) {
    return src.find(expr)!=std::string::npos;
}

template <class ... Types>
bool contains(const std::string& src, const char* expr, Types* ... more) {
    return contains(src, expr) || contains(src, more...);
}

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
        //a += hexify(pc) + " ";

        char sym[256];
        if (unw_get_proc_name(&cursor, sym, sizeof(sym), &offset) == 0) {
            char* nameptr = sym;
            int status;
            char* demangled = abi::__cxa_demangle(sym, nullptr, nullptr, &status);
            if (status == 0) nameptr = demangled;
            std::string l(nameptr);
            if (l.empty()||l=="lwm2m_malloc"||l=="main"||l=="clone"||l=="_start"||l=="start_thread"||
                    contains(l,"testing::", "TestBody", "std::thread", "std::error_code", "_start_main", "_invoke")) continue;
            a += "\t" + l + " (" + hexify(offset)+") \n";
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
#include "backward.hpp"
std::string print_trace (void) {
    std::string s;
    using namespace backward;
    StackTrace st; st.load_here(32);
    TraceResolver tr; tr.load_stacktrace(st);
    for (size_t i = 3; i < st.size(); ++i) {
        ResolvedTrace trace = tr.resolve(st[i]);
        std::string l(trace.object_function);
        if (l.empty()||l=="main"||l=="clone"||l=="_start"||l=="lwm2m_malloc"||l=="start_thread"||
                contains(l,"testing::", "TestBody", "std::thread", "std::error_code", "_start_main", "_invoke")) continue;
        s += "\t#" + std::to_string(i)
            + " " +trace.source.filename+"#L" + std::to_string(trace.source.line)
            + " " + trace.object_function
            + " [" + hexify(trace.addr) + "]\n";
    }
    return s;
}
#endif


#ifdef __cplusplus
extern "C" {
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
