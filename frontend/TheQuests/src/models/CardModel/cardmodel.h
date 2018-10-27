#ifndef CARDMODEL_H
#define CARDMODEL_H

#include <QObject>

class CardModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(const QString& id READ getId NOTIFY idChanged)
    Q_PROPERTY(const QString& questId READ getQuestId NOTIFY questIdChanged)
    Q_PROPERTY(const QString& title READ getTitle NOTIFY titleChanged)
    Q_PROPERTY(const QString& imagePath READ getImagePath NOTIFY imagePathChanged)
    Q_PROPERTY(const QString& description READ getDescription NOTIFY descriptionChanged)
    Q_PROPERTY(const QString& type READ getType NOTIFY typeChanged)

public:

    explicit CardModel(QObject* parent = nullptr);

    CardModel(
            const QString& id,
            const QString& questId,
            const QString& title,
            const QString& imagePath,
            const QString& description,
            const QString& type,
            QObject* parent = nullptr);
    virtual ~CardModel() = default;

    const QString& getId() const;
    void setId(const QString &value);

    const QString& getQuestId() const;
    void setQuestId(const QString &value);

    const QString& getTitle() const;
    void setTitle(const QString &value);

    const QString& getImagePath() const;
    void setImagePath(const QString &value);

    const QString& getDescription() const;
    void setDescription(const QString &value);

    const QString& getType() const;
    void setType(const QString &value);

signals:

    void idChanged(const QString&);
    void questIdChanged(const QString&);
    void titleChanged(const QString&);
    void imagePathChanged(const QString&);
    void descriptionChanged(const QString&);
    void typeChanged(const QString&);

private:

    QString id;
    QString questId;
    QString title;
    QString imagePath;
    QString description;
    QString type;
};

#endif // CARDMODEL_H
