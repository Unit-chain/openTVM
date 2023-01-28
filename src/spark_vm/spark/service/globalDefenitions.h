//
// Created by Kirill Zhukov on 29.12.2022.
//

#ifndef VM_WITH_HEAP_GLOBALDEFENITIONS_H
#define VM_WITH_HEAP_GLOBALDEFENITIONS_H

#define DEBUG_MODE true
#define COLORFUL_TERMINAL true

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

#if _WIN32 || _AIX || __hpux || __sgi || __osf || __sun || __linux__
    /// took from: https://opensource.apple.com/source/Libc/Libc-262/string/strlcat.c.auto.html
    /*
     * Appends src to string dst of size siz (unlike strncat, siz is the
     * full size of dst, not space left).  At most siz-1 characters
     * will be copied.  Always NUL terminates (unless siz <= strlen(dst)).
     * Returns strlen(src) + MIN(siz, strlen(initial dst)).
     * If retval >= siz, truncation occurred.
     */
    size_t strlcat(char *dst, const char *src, size_t siz) {
        char *d = dst;
        const char *s = src;
        size_t n = siz;
        size_t dlen;
        /* find the end of dst and adjust bytes left but don't go past end */
        while (n-- != 0 && *d != '\0')
            d++;
        dlen = d - dst;
        n = siz - dlen;
        if (n == 0)
            return(dlen + strlen(s));
        while (*s != '\0') {
            if (n != 1) {
                *d++ = *s;
                n--;
            }
            s++;
        }
        *d = '\0';
        return(dlen + (s - src));	/* count does not include nul */
    }
#endif

#ifdef DEBUG_MODE
#  define ALWAYS_INLINE static inline
#else
#  ifdef _MSC_VER
#    define ALWAYS_INLINE static __forceinline
#  else
#    define ALWAYS_INLINE JEMALLOC_ATTR(always_inline) static inline
#  endif
#endif
#ifdef _MSC_VER
#  define inline _inline
#endif

typedef unsigned char       u_char;
typedef u_char*            address;
typedef uintptr_t     address_word;

#ifdef _WIN32

#include <windows.h>
SYSTEM_INFO si;
GetSystemInfo(&si);
const size_t page_size = si.dwPageSize;

#elif defined(__OpenBSD__) || defined(__FreeBSD__) || defined(__APPLE__) || defined(__linux__) || defined(__NetBSD__)

#include <unistd.h>
const size_t page_size = (size_t)getpagesize();

#endif

const size_t K = 1024;  // kilo
constexpr size_t M = K * K; // mega
constexpr size_t G = M * K; // giga

const size_t typical_page_size = 4 * K; // 4096 bytes

#define byteShifter(byte1, byte2) (byte1 << 8 | byte2)

#endif //VM_WITH_HEAP_GLOBALDEFENITIONS_H
