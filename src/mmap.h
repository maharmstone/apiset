#pragma once

#include "apiset.h"

class mmap {
public:
    explicit mmap(fd_t h);
    ~mmap();
    std::span<const uint8_t> map();

    size_t filesize;

private:
#ifdef _WIN32
    HANDLE h = INVALID_HANDLE_VALUE;
    HANDLE mh = INVALID_HANDLE_VALUE;
#endif
    void* ptr = nullptr;
};
