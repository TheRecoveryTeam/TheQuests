#include "cardlink.h"

CardLink::CardLink(QObject *parent) : QObject(parent)
{ }

CardLink::CardLink(const QString& answer,
                   const std::map<config::ResourceTypes, int>& influenceMap,
                   QObject* parent):
    QObject (parent),
    answer(answer),
    influenceMap(influenceMap)
{ }

const QString& CardLink::getAnswer() const
{
    return answer;
}

void CardLink::setAnswer(const QString& value)
{
    answer = value;
}

int CardLink::getInfluence(const config::ResourceTypes& rt) const
{
    if (influenceMap.find(rt) == influenceMap.end()) {
        // Значит, на этот ресурс не влияет
        return 0;
    }
    return influenceMap.at(rt);
}

void CardLink::setInfluenceMap(const std::map<config::ResourceTypes, int>& value)
{
    influenceMap = value;
}

void CardLink::rewriteInfluence(const config::ResourceTypes& rt, int magnitude)
{
    influenceMap[rt] = magnitude;
}
