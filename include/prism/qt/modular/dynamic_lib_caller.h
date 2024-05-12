#ifndef PRISM_QT_MODULAR_DANYMIC_LIB_CALLER_H
#define PRISM_QT_MODULAR_DANYMIC_LIB_CALLER_H
#include "prism_qt_modular_global.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#if defined(__GNUC__) || defined(__clang__)
#include <dlfcn.h>
#endif

#include <iostream>

#ifdef __linux
#include <experimental/filesystem>
#define filesystem experimental::filesystem
#else
#include <filesystem>
#endif

namespace prism::qt::modular {

class PRISM_QT_MODULAR_EXPORT dynamic_lib_caller
{
public:
    dynamic_lib_caller();

    static void* loadLib(std::string path);
    static void* getFunctionAddr(void *lib, const char*  funName);
    static void  unloadLib(void *lib);
};
}// namespace prism::qt::modular

#endif // PRISM_QT_MODULAR_DANYMIC_LIB_CALLER_H
