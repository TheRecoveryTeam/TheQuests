#ifndef QUESTSHORTMODEL_H
#define QUESTSHORTMODEL_H
#include <QMetaType>
#include <QObject>

class QuestShortModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(const QString& id READ getId NOTIFY idChanged)
    Q_PROPERTY(const QString& title READ getTitle NOTIFY titleChanged)
    Q_PROPERTY(const QString& description READ getDescription NOTIFY descriptionChanged)
    Q_PROPERTY(const QString& authorNickName READ getAuthorNickName NOTIFY authorNickNameChanged)
    Q_PROPERTY(const QString& playerCount READ getPlayerCount NOTIFY playerCountChanged)
    Q_PROPERTY(const QString& imagePath READ getImagePath NOTIFY imagePathChanged)
public:
    explicit QuestShortModel(QObject *parent = nullptr);
    ~QuestShortModel() = default;
    QuestShortModel(
            const QString& id,
            const QString& title,
            const QString& description,
            const QString& authorNickName,
            const QString& playerCount,
            const QString& imagePath,
            QObject* parent = nullptr);

    const QString& getId() const;
    void setId(const QString &value);

    const QString& getTitle() const;
    void setTitle(const QString &value);

    const QString& getDescription() const;
    void setDescription(const QString &value);

    const QString& getAuthorNickName() const;
    void setAuthorNickName(const QString &value);

    const QString& getPlayerCount() const;
    void setPlayerCount(const QString &value);

    const QString& getImagePath() const;
    void setImagePath(const QString &value);

signals:
    void idChanged(const QString&);
    void titleChanged(const QString&);
    void descriptionChanged(const QString&);
    void authorNickNameChanged(const QString&);
    void playerCountChanged(const QString&);
    void imagePathChanged(const QString&);

protected:
    QString id;
    QString title;
    QString description;
    QString authorNickName;
    QString playerCount;
    QString imagePath;
};

#endif // QUESTSHORTMODEL_H
