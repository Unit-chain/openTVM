//
// Created by Kirill Zhukov on 01.02.2023.
//

#include "MethodData.h"

MethodData::MethodData(cstring *code, void *backMethod) : _code(reinterpret_cast<cstring>(code)), _backMethod(backMethod) {}
