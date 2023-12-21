#ifndef DANYMIC_LIB_CALLER_H
#define DANYMIC_LIB_CALLER_H
#include "prism_qt_modular_global.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef __linux
#include <dlfcn.h>
#endif

#include <iostream>
#include <filesystem>

class PRISM_QT_MODULAR_EXPORT dynamic_lib_caller
{
public:
    dynamic_lib_caller();

    static void* loadLib(std::string path);
    static void* getFunctionAddr(void *lib, const char*  funName);
    static void  unloadLib(void *lib);
};

#endif // DANYMIC_LIB_CALLER_H
