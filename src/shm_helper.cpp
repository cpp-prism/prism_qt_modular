#include "include/prism/qt/modular/shm_helper.h"
#include <errno.h>
#include <cstring>

namespace prism::qt::modular {

#ifdef _WIN32 // Windows
shm_helper::shm_helper(const char *name, size_t size):size(size)
{
    handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, static_cast<DWORD>(size), name);
    if (handle == NULL) {
        std::cerr << "Failed to create shared memory" << std::endl;
    }
}

shm_helper::~shm_helper()
{
    CloseHandle(handle);
}

void *shm_helper::map()
{
    return MapViewOfFile(handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
}

void shm_helper::unmap(void *addr)
{
    UnmapViewOfFile(addr);
}

#else
shm_helper::shm_helper(const char *name, size_t size):size(size)
{
    //fd = shm_open(name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    fd = shm_open(name, O_CREAT | O_RDWR, 0777);
    if (fd == -1) {
        std::cerr << "Failed to create shared memory," << strerror(errno) << std::endl;
    }
    ftruncate(fd, size);
}

shm_helper::~shm_helper()
{
    close(fd);
    // Unlink shared memory object
    // shm_unlink(name); // Uncomment this if you want to remove shared memory object after use
}

void *shm_helper::map()
{
    std::cout << "map size:" << size << "   fd:" << fd << std::endl;
    void* r =  mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(r == MAP_FAILED)
    {
        std::cerr << "mmap failed: " << strerror(errno) << std::endl;
        return nullptr;
    }
    else
        return r;
}

void shm_helper::unmap(void *addr)
{
    munmap(addr, size);
}

#endif
}//namespace prism::qt::modular
