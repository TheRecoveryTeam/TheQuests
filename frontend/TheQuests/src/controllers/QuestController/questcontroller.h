#ifndef QUESTCONTROLLER_H
#define QUESTCONTROLLER_H

#include "../AbstractController/abstractcontoller.h"
#include "src/models/QuestDetailModel/questdetailmodel.h"
#include "src/models/QuestShortModel/questshortmodel.h"

class QuestController: public AbstractContoller
{
public:
    QuestController(QObject* parent = nullptr);
    ~QuestController();
    void create (const QString& title,
                 const QString& description,
                 const QString& image);
    void remove(const QString& id);
    void edit(const QString& title,
              const QString& description,
              const QString& image);
    void editImage(const QString& id,
                   const QString& image);

    void getQuestDetail(const QString& id);
    void getResources(const QString& id);
    // TODO: продумать передаваемые значения
    void getQuestList();

private:
    QuestDetailModel* questDetailModel;
};

#endif // QUESTCONTROLLER_H
