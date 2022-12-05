cmake_minimum_required(VERSION 3.21)
project(vm_with_heap)

set(CMAKE_CXX_STANDARD 20)
find_package(Boost)

include_directories(
        spark/share
        spark/theia.core
)

#file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.hpp" "*.c" "*.h")
#
#add_executable(spark_vm ${SOURCE_FILES})

add_executable(vm_with_heap main.cpp spark/Heap/pairingheap.h spark/share/oops/Klass.h spark/theia.core/unix/tni.h spark/theia.core/win/tni.h spark/theia.core/share/s_tni.h)
target_link_libraries(${PROJECT_NAME} Boost::boost)