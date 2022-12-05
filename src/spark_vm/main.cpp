#include <iostream>
#include "cmath"
#include "test/LogDuration.h"

int main() {
    #ifdef _LP64
        std::cout << 111 << std::endl;
    #endif

//    __linux__       Defined on Linux
//    __sun           Defined on Solaris
//    __FreeBSD__     Defined on FreeBSD
//    __NetBSD__      Defined on NetBSD
//    __OpenBSD__     Defined on OpenBSD
//    __APPLE__       Defined on Mac OS X
//    __hpux          Defined on HP-UX
//    __osf__         Defined on Tru64 UNIX (formerly DEC OSF1)
//    __sgi           Defined on Irix
//    _AIX            Defined on AIX
//    _WIN32          Defined on Windows

    #ifdef __linux__
        std::cout << "linux" << std::endl;
    #elif _WIN32
        std::cout << "windows" << std::endl;
    #elif __APPLE__
        std::cout << "macos" << std::endl;
    #endif

    return 0;
}
