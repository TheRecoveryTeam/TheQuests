#include "cardshortmodel.h"

CardShortModel::CardShortModel(QObject *parent) : QObject(parent)
{

}

CardShortModel::CardShortModel(const QString& id,
                               const QString& title,
                               const QString& imagePath,
                               const QString& description,
                               QObject* parent):
    QObject (parent),
    id(id),
    title(title),
    imagePath(imagePath),
    description(description)
{ }

QString CardShortModel::getId() const
{
    return id;
}

void CardShortModel::setId(const QString& value)
{
    id = value;
}

QString CardShortModel::getTitle() const
{
    return title;
}

void CardShortModel::setTitle(const QString& value)
{
    title = value;
}

QString CardShortModel::getImagePath() const
{
    return imagePath;
}

void CardShortModel::setImagePath(const QString& value)
{
    imagePath = value;
}

QString CardShortModel::getDescription() const
{
    return description;
}

void CardShortModel::setDescription(const QString& value)
{
    description = value;
}
