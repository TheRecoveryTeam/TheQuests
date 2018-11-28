#ifndef QUESTCONTROLLER_H
#define QUESTCONTROLLER_H

#include "../AbstractController/abstractcontoller.h"

class QuestDetailModel;
class QQmlEngine;
class QJSEngine;
class HttpRequester;
class QuestListsContainerModel;

class QuestController: public AbstractContoller
{
    Q_OBJECT
public:
    ~QuestController() = default;
    static QuestController* instance();

    Q_INVOKABLE void getQuestDetail(const QString& questId) const;
    Q_INVOKABLE void getResources(const QString& questId) const;
    Q_INVOKABLE void getQuestList(const QString& page,
                                  const QString& limit,
                                  const QString& authorId,
                                  const QString& asc,
                                  const QString& stage
                                  );


    Q_INVOKABLE void create(const QString& title,
                            const QString& description,
                            const QString& image);


    void remove(const QString& id);
    void edit(const QString& title,
              const QString& description,
              const QString& image);
    void editImage(const QString& id,
                   const QString& image);


private:
    static QuestController* createInstance();
    explicit QuestController(QObject* parent = nullptr);

    QuestDetailModel* questDetailModel;
    QuestListsContainerModel* questListsContainerModel;
};

#endif // QUESTCONTROLLER_H
