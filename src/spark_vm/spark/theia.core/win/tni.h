//
// Created by Kirill Zhukov on 05.12.2022.
//

#ifndef VM_WITH_HEAP_TNI_H
#define VM_WITH_HEAP_TNI_H

#define NATIVECALL __stdcall
#ifdef _MSC_VER
typedef __int64 tlong;
typedef long tint;
#endif

#endif //VM_WITH_HEAP_TNI_H
