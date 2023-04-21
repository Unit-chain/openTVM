//
// Created by Kirill Zhukov on 30.01.2023.
//

#include "metaObject.h"

void *metaObject::getBottomMetaspace() const {
    return _bottomMetaspace;
}

void metaObject::setBottomMetaspace(void *bottomMetaspace) {
    _bottomMetaspace = bottomMetaspace;
}

void *metaObject::getTopMetaspace() const {
    return _topMetaspace;
}

void metaObject::setTopMetaspace(void *topMetaspace) {
    _topMetaspace = topMetaspace;
}