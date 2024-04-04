#ifndef PRISM_QT_MODULAR_SHM_HELPER_H
#define PRISM_QT_MODULAR_SHM_HELPER_H

#include "prism_qt_modular_global.h"
#include <iostream>
#ifdef _WIN32 // Windows

#include <windows.h>

namespace prism::qt::modular {

class PRISM_QT_MODULAR_EXPORT shm_helper
{
public:

    shm_helper(const char* name, size_t size);

    ~shm_helper();

    void* map() ;

    void unmap(void* addr);

private:
    HANDLE handle;
};
}// namespace prism::qt::modular

#else // Linux and macOS

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

namespace prism::qt::modular {

class PRISM_QT_MODULAR_EXPORT shm_helper {
public:

    shm_helper(const char* name, size_t size);

    ~shm_helper();

    void* map();

    void unmap(void* addr);

private:
    int fd;
    size_t size;
};
}// namespace prism::qt::modular

#endif

#endif // PRISM_QT_MODULAR_SHM_HELPER_H






