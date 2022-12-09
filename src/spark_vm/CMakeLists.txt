cmake_minimum_required(VERSION 3.21)
project(vm_with_heap)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost)

include_directories(
        spark/share
        spark/theia.core
        spark/share/utilities
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
        )

target_link_libraries(${PROJECT_NAME} Boost::boost)
