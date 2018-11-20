#ifndef RESOURCEITEM_H
#define RESOURCEITEM_H

#include <QString>
#include "src/config/resourcetypes.h"

namespace structures {

struct ResourceItem {
    QString type = "";
    int value = 0;
};

}

#endif // RESOURCEITEM_H
