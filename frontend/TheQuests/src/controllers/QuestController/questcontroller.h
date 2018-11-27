#ifndef QUESTCONTROLLER_H
#define QUESTCONTROLLER_H

#include "../AbstractController/abstractcontoller.h"

class QuestDetailModel;
class QQmlEngine;
class QJSEngine;
class HttpRequester;

class QuestController: public AbstractContoller
{
    Q_OBJECT
public:
    ~QuestController() = default;
    static QuestController* instance();

    Q_INVOKABLE void get(const QString& questId) const;

    void create(const QString& title,
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
    static QuestController* createInstance();
    explicit QuestController(QObject* parent = nullptr);

    QuestDetailModel* questDetailModel;
};

#endif // QUESTCONTROLLER_H
