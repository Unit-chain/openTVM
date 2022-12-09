//
// Created by Kirill Zhukov on 05.12.2022.
//

// share theia native interface

#ifndef VM_WITH_HEAP_S_TNI_H
#define VM_WITH_HEAP_S_TNI_H

#ifdef _WIN32
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

class t_object{};
class t_class : public t_object{};
class t_throwable : public t_object{};
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
typedef t_throwable *tthrowable;
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
    tbyte by;
    tchar ch;
    tshort sh;
    tint in;
    tlong tl;
    tfloat fl;
    tdouble du; // not "do" because "do" reserved by C++
    tobject ob;
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

#endif //VM_WITH_HEAP_S_TNI_H
