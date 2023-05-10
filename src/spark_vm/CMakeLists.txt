cmake_minimum_required(VERSION 3.24)
project(spark_vm)

set(CMAKE_CXX_STANDARD 20)
set(DCMAKE_VARIABLE_NAME /opt/homebrew/Cellar/zstd/1.5.5/lib)

find_package(Boost REQUIRED)
find_package(zstd CONFIG REQUIRED)

include_directories(
        spark/share
        spark/theia.core
        spark/share/utilities
        spark/share/services
        spark/memory/
)

#file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.hpp" "*.c" "*.h")
#
#add_executable(spark_vm ${SOURCE_FILES})

add_executable(${PROJECT_NAME}
        main.cpp
        spark/share/utilities/hash/xxhash.h
        spark/theia.core/unix/tni.h
        spark/theia.core/win/tni.h
        spark/theia.core/share/s_ti.h
        spark/share/utilities/hash/MurmurHash3.cpp
        spark/share/utilities/hash/MurmurHash3.h
        spark/share/utilities/hash/xxhash.c
        spark/share/utilities/hash/xxhash.h
        spark/share/utilities/bloomfilter.h
        spark/share/utilities/bloomhash.h
        spark/share/utilities/hash/xxh3.h
        spark/share/utilities/hash/sha3.h
        spark/share/utilities/hash/sha3.cpp
        spark/share/utilities/hash/SHA256.h
        spark/share/utilities/hash/SHA256.cpp
        spark/share/utilities/hash/City.cpp
        spark/share/services/logger/loggerTime.h
        spark/share/services/logger/logger.h
        spark/share/global/globalDefenitions.h
        spark/share/utilities/accessFlags.h
        spark/cpu/x86/x86.h spark/cpu/arm/arm.h
        spark/share/utilities/accessFlags.cpp
        spark/share/types/integralTypes.h
        spark/memory/os.h
        test/LogDuration.h
        spark/share/obj/object_ref.cpp
        spark/share/obj/object_ref.h
        spark/share/obj/klass.cpp
        spark/share/obj/klass.h
        spark/share/obj/method.cpp
        spark/share/obj/method.h
        spark/share/utilities/compression/zstd_decompression.cpp
        spark/share/utilities/compression/zstd_decompression.h
        spark/share/utilities/read/BytecodeFileReader.cpp
        spark/share/utilities/read/BytecodeFileReader.h
        spark/share/utilities/hash/unordered/th_hash.c
        spark/share/utilities/hash/unordered/th_hash.h
        spark/share/utilities/hash/unordered/CustomHash.h
        spark/share/utilities/hash/unordered/CustomHash.cpp
        )


find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME}
        Boost::boost
        OpenSSL::SSL
        zstd::libzstd_static
        )