#include "include/prism/qt/modular/dynamic_lib_caller.h"
#include <sstream>

dynamic_lib_caller::dynamic_lib_caller()
{

}

#ifdef _WIN32
void *dynamic_lib_caller::loadLib(std::string path)
{
    HMODULE lib = LoadLibrary(path.c_str()) ;
    return static_cast<void*>(lib);
}

void *dynamic_lib_caller::getFunctionAddr(void *lib, const char*  funName)
{
    HMODULE library = static_cast<HMODULE>(lib);
     // 获取函数地址
    FARPROC functionAddr = GetProcAddress(library, funName);
    if (!functionAddr) {
        return nullptr;
    }
    return  static_cast<void*>(functionAddr);

}

void dynamic_lib_caller::unloadLib(void *lib)
{
    if(lib)
    {
        HMODULE library = static_cast<HMODULE>(lib);
        FreeLibrary(library);
    }
}

#endif

#ifdef __linux
void *dynamic_lib_caller::loadLib(std::string path)
{
    void* library = dlopen(path.c_str(), RTLD_NOW);
    if(!library)
    {
        const char* msg = dlerror();
        std::cout << msg << std::endl;
    }
    return library;
}

void *dynamic_lib_caller::getFunctionAddr(void *lib, const char*  funName)
{
    void* functionAddr = dlsym(lib, funName);
     // 获取函数地址
    if (!functionAddr)
    {
        return nullptr;
    }
    return  functionAddr;

}

void dynamic_lib_caller::unloadLib(void *lib)
{
    if(lib)
    {
        dlclose(lib);
    }
}

#endif
