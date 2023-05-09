//
// Created by Kirill Zhukov on 05.12.2022.
//

#ifndef VM_WITH_HEAP_TNI_H
#define VM_WITH_HEAP_TNI_H

#define NATIVECALL
typedef int tint_t;
#ifdef _LP64
typedef long tlong_t;
#else
typedef long long tlong;
#endif

#endif //VM_WITH_HEAP_TNI_H
