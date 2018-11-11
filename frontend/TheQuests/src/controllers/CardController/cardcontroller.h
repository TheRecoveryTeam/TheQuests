#ifndef CARDCONTROLLER_H
#define CARDCONTROLLER_H

#include "../AbstractController/abstractcontoller.h"
#include "src/models/CardModel/cardmodel.h"
#include "src/models/CardShortModel/cardshortmodel.h"

class CardController: public AbstractContoller
{
public:
    CardController(QObject* parent = nullptr);
    ~CardController();

    // TODO : возвращаемые значения
    void add(const QString& cardId,
             const QString& questId,
             const QString& title,
             const QString& description,
             const QString& type);
    void get(const QString& cardId);
    void edit(const QString& cardId,
              const QString& questId,
              const QString& title,
              const QString& description,
              const QString& type);

    void remode(const QString& cardId);
    void doAnswer(const QString& cardId, const QString& answer);
    void getList(const QString& questId);
    void linksUpsert();
private:
    CardModel* cardModel;
};

#endif // CARDCONTROLLER_H
