#ifndef IQUERYABLE_H
#define IQUERYABLE_H

class QString;

class IQueryable {
public:
    virtual ~IQueryable() = default;
    virtual QString toQueryString() const = 0;
};

#endif // IQUERYABLE_H
