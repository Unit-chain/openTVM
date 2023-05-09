//
// Created by Kirill Zhukov on 05.12.2022.
//

// share theia native interface

#ifndef VM_WITH_HEAP_S_TI_H
#define VM_WITH_HEAP_S_TI_H

#include "boost/multiprecision/cpp_int.hpp"

#ifdef _MSC_VER
    #include "win/tni.h"
#else
    #include "unix/tni.h"
#endif

typedef signed char tbyte_t;
typedef unsigned char tchar_t;
typedef short tshort_t;
typedef float tfloat_t;
typedef double tdouble_t;
typedef tint_t tsize_t;
typedef bool tboolean_t;
typedef uint16_t tuint16_t;
typedef uint32_t tuint32_t;

#ifdef __UINT64_TYPE__
typedef uint64_t tuint64_t;
#else
typedef unsigned long long tuint64_t;
#endif
typedef boost::multiprecision::uint128_t tuint128_t;
typedef boost::multiprecision::uint256_t tuint256_t;

class t_object{};
class t_class : public t_object{};
class t_string : public t_object {};
class t_array : public t_object {};
class t_booleanArray : public t_array {};
class t_byteArray : public t_array {};
class t_charArray : public t_array {};
class t_shortArray : public t_array {};
class t_intArray : public t_array {};
class t_longArray : public t_array {};
class t_floatArray : public t_array {};
class t_doubleArray : public t_array {};
class t_objectArray : public t_array {};

typedef t_object *tobject_t;
typedef t_class *tclass;
typedef t_string *tstring;
typedef t_array *tarray;
typedef t_booleanArray *tbooleanArray;
typedef t_byteArray *tbyteArray;
typedef t_charArray *tcharArray;
typedef t_shortArray *tshortArray;
typedef t_intArray *tintArray;
typedef t_longArray *tlongArray;
typedef t_floatArray *tfloatArray;
typedef t_doubleArray *tdoubleArray;
typedef t_objectArray *tobjectArray;

[[maybe_unused]] typedef union tvalue {
    tboolean_t bo;
    tbyte_t    by;
    tchar_t    ch;
    tshort_t   sh;
    tint_t     in;
    tlong_t    tl;
    tfloat_t   fl;
    tdouble_t  du;
    tobject_t  ob;
    tuint32_t  t32;
    tuint64_t  t64;
    tuint128_t t128;
    tuint256_t t256;
} tvalue;

#endif //VM_WITH_HEAP_S_TI_H
