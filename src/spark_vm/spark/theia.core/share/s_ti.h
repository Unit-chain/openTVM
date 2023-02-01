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

typedef signed char tbyte;
typedef unsigned char tchar;
typedef short tshort;
typedef float tfloat;
typedef double tdouble;
typedef tint tsize;
typedef bool tboolean;
typedef uint32_t tuint32;

#ifdef __UINT64_TYPE__
typedef uint64_t tuint64;
#endif
#ifdef __SIZEOF_INT128__
typedef __uint128_t tuint128;
#elif
typedef boost::multiprecision::uint128_t tuint128;
#endif
typedef boost::multiprecision::uint256_t tuint256;

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

typedef t_object *tobject;
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
    tboolean bo;
    tbyte    by;
    tchar    ch;
    tshort   sh;
    tint     in;
    tlong    tl;
    tfloat   fl;
    tdouble  du;
    tobject  ob;
    tuint32  t32;
    tuint64  t64;
    tuint128 t128;
    tuint256 t256;
} tvalue;

class t_fieldID{};
typedef t_fieldID *tfieldID;
class t_methodID{};
typedef t_methodID *tmethodID;

typedef enum t_objectType {
    TNIInvalidRefType    = 0,
    TNILocalRefType      = 1,
    TNIGlobalRefType     = 2,
    TNIWeakGlobalRefType = 3
} tobjectRefType;

typedef struct {
    char *name;
    char *signature;
    void *fnPtr;
} TNINativeMethod;

/// @note
/// returning values from Theia Native Interface
#define TNI_OK      0
#define TNI_ERR     (-1)
#define TNI_VERSION (-2)
#define TNI_NEMEM   (-3)

#endif //VM_WITH_HEAP_S_TI_H
