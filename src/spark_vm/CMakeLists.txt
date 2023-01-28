cmake_minimum_required(VERSION 3.24)
project(vm_with_heap)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost)
#find_package(JEMALLOC)
include_directories(
        spark/share
        spark/theia.core
        spark/share/utilities
        spark/service
)

#file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.hpp" "*.c" "*.h")
#
#add_executable(spark_vm ${SOURCE_FILES})

add_executable(vm_with_heap
        main.cpp
        spark/Heap/pairingheap.h
        spark/share/oops/Klass.h
        spark/share/utilities/hash/xxhash.h
        spark/theia.core/unix/tni.h
        spark/theia.core/win/tni.h
        spark/theia.core/share/s_tni.h
        spark/share/utilities/hash/MurmurHash3.cpp
        spark/share/utilities/hash/MurmurHash3.h
        spark/share/utilities/hash/xxhash.c
        spark/share/utilities/hash/xxhash.h
        spark/share/utilities/bitmask.h
        spark/share/utilities/bloomfilter.h
        spark/share/utilities/bloomhash.h
        spark/share/utilities/hash/xxh3.h
        spark/share/utilities/hash/sha3.h
        spark/share/utilities/hash/sha3.cpp
        spark/share/utilities/hash/SHA256.h
        spark/share/utilities/hash/SHA256.cpp
        spark/share/utilities/hash/City.cpp
        spark/memory/alloc.h
        spark/service/logger/loggerTime.h spark/service/logger/logger.h spark/service/globalDefenitions.h spark/memory/pheap.h spark/share/utilities/accessFlags.h spark/share/runtime/os.h spark/cpu/x86/x86.h spark/cpu/arm/arm.h)

find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} Boost::boost)
target_link_libraries(${PROJECT_NAME} OpenSSL::SSL)
