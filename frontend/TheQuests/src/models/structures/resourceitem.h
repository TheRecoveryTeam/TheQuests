#ifndef RESOURCEITEM_H
#define RESOURCEITEM_H

#include "src/config/resourcetypes.h"

namespace structures {

struct ResourceItem {
    config::ResourceTypes type;
    int value;
};

}

#endif // RESOURCEITEM_H
