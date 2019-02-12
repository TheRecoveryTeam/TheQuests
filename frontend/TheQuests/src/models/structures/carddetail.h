#ifndef CARDDETAIL_H
#define CARDDETAIL_H

#include <QString>

namespace structures {

struct CardDetail {
    QString id = "";
    QString questId = "";
    QString title = "";
    QString description = "";
    QString imagePath = "";
    QString type = "";
};

}

#endif // CARDDETAIL_H
