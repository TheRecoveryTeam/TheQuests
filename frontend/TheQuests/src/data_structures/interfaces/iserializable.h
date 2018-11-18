#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

class QJsonObject;

class ISerializable {
public:
    virtual ~ISerializable() = default;
    virtual QJsonObject toJSON() const = 0;
};

#endif // ISERIALIZABLE_H
