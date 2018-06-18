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
#pragma once

#include <map>
#include <iostream>

class MemoryObserver {
public:
    using MemAreas = std::map<long, std::string>;
    MemAreas memAreas;

    void reset() {
        memAreas.clear();
    }
    void add(long mem, const std::string& stacktrace) {
        memAreas.insert(std::make_pair(mem, stacktrace));
    }
    void remove(long mem) {
        memAreas.erase(mem);
    }
};

extern MemoryObserver memoryObserver;
