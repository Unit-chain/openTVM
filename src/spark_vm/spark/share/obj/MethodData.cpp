//
// Created by Kirill Zhukov on 01.02.2023.
//

#include "MethodData.h"

MethodData::MethodData(cstring *code, Method *method) : _code(reinterpret_cast<cstring>(code)), _backMethod(method) {}
