#ifndef CARDSHORTMODEL_H
#define CARDSHORTMODEL_H

#include <QObject>

class CardShortModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(const QString& id READ getId NOTIFY idChanged)
    Q_PROPERTY(const QString& title READ getTitle NOTIFY titleChanged)
    Q_PROPERTY(const QString& imagePath READ getImagePath NOTIFY imagePathChanged)
    Q_PROPERTY(const QString& description READ getDescription NOTIFY descriptionChanged)
public:

    explicit CardShortModel(QObject *parent = nullptr);

    CardShortModel(const QString& id,
                   const QString& title,
                   const QString& imagePath,
                   const QString& description,
                   QObject* parent = nullptr);

    const QString& getId() const;
    void setId(const QString& value);

    const QString& getTitle() const;
    void setTitle(const QString& value);

    const QString& getImagePath() const;
    void setImagePath(const QString& value);

    const QString& getDescription() const;
    void setDescription(const QString& value);

signals:

    void idChanged(const QString&);
    void titleChanged(const QString&);
    void imagePathChanged(const QString&);
    void descriptionChanged(const QString&);

protected:

    QString id;
    QString title;
    QString imagePath;
    QString description;
};

#endif // CARDSHORTMODEL_H
