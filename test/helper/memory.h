#pragma once

#include <map>
#include <iostream>

class MemoryObserver {
public:
    std::map<long, std::string> memAreas;

    void reset() {
        memAreas.clear();
    }
    void add(long mem, const std::string& stacktrace) {
        memAreas.insert(std::make_pair(mem, stacktrace));
    }
    void remove(long mem) {
        memAreas.erase(mem);
    }

    std::string printIfNotEmpty() {
        std::string all;
        for (auto& e: memAreas) {
            all += "Entry @ " +std::to_string(e.first) + "\n" + e.second + "\n\n";
        }
        return all;
    }
};

extern MemoryObserver memoryObserver;
