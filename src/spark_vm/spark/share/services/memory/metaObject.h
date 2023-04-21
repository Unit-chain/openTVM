//
// Created by Kirill Zhukov on 30.01.2023.
//

#ifndef VM_WITH_HEAP_METAOBJECT_H
#define VM_WITH_HEAP_METAOBJECT_H
#include "global/globalDefenitions.h"

class metaObject {
    void *_bottomMetaspace;
    void *_topMetaspace;

public:
    void *getBottomMetaspace() const;

    void setBottomMetaspace(void *bottomMetaspace);

    void *getTopMetaspace() const;

    void setTopMetaspace(void *topMetaspace);

    u_int16_t getMinorVersion() const;

    void setMinorVersion(u_int16_t minorVersion);

    u_int16_t getMajorVersion() const;

    void setMajorVersion(u_int16_t majorVersion);
};


#endif //VM_WITH_HEAP_METAOBJECT_H
