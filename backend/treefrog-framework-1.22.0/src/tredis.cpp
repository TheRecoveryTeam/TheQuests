/* Copyright (c) 2015-2017, AOYAMA Kazuharu
 * All rights reserved.
 *
 * This software may be used and distributed according to the terms of
 * the New BSD License, which is incorporated herein by reference.
 */

#include <TRedis>
#include <TActionContext>
#include "tredisdriver.h"

/*!
  \class TRedis
  \brief The TRedis class provides a means of operating a Redis
  system.
*/

/*!
  Constructs a TRedis object.
*/
TRedis::TRedis()
    : database(Tf::currentDatabaseContext()->getKvsDatabase(TKvsDatabase::Redis))
{ }

/*!
  Copy constructor.
*/
TRedis::TRedis(const TRedis &other)
    : database(other.database)
{ }

/*!
  Returns the MongoDB driver associated with the TRedis object.
*/
TRedisDriver *TRedis::driver()
{
#ifdef TF_NO_DEBUG
    return (TRedisDriver *)database.driver();
#else
    if (!database.driver()) {
        return nullptr;
    }

    TRedisDriver *driver = dynamic_cast<TRedisDriver *>(database.driver());
    if (!driver) {
        throw RuntimeException("cast error", __FILE__, __LINE__);
    }
    return driver;
#endif
}

/*!
  Returns the MongoDB driver associated with the TRedis object.
*/
const TRedisDriver *TRedis::driver() const
{
#ifdef TF_NO_DEBUG
    return (const TRedisDriver *)database.driver();
#else
    if (!database.driver()) {
        return nullptr;
    }

    const TRedisDriver *driver = dynamic_cast<const TRedisDriver *>(database.driver());
    if (!driver) {
        throw RuntimeException("cast error", __FILE__, __LINE__);
    }
    return driver;
#endif
}

/*!
  Returns true if the Redis connection is open; otherwise
  returns false.
 */
bool TRedis::isOpen() const
{
    return (driver()) ? driver()->isOpen() : false;
}

/*!
  Returns true if the \a key exists; otherwise returns false.
 */
bool TRedis::exists(const QByteArray &key)
{
    if (!driver()) {
        return false;
    }

    QVariantList resp;
    QList<QByteArray> command = { "EXISTS", key };
    bool res = driver()->request(command, resp);
    return (res && resp.value(0).toInt() == 1);
}

/*!
  Returns the value associated with the \a key; otherwise
  returns an empty bit array.
 */
QByteArray TRedis::get(const QByteArray &key)
{
    if (!driver()) {
        return QByteArray();
    }

    QVariantList resp;
    QList<QByteArray> command = { "GET", key };
    bool res = driver()->request(command, resp);
    return (res) ? resp.value(0).toByteArray() : QByteArray();
}

/*!
  Sets the \a key to hold the \a value. If the key already holds a
  value, it is overwritten, regardless of its type.
 */
bool TRedis::set(const QByteArray &key, const QByteArray &value)
{
    if (!driver()) {
        return false;
    }

    QVariantList resp;
    QList<QByteArray> command = { "SET", key, value };
    return driver()->request(command, resp);
}

/*!
  Sets the \a key to hold the \a value and set the key to timeout
  after a given number of \a seconds.
 */
bool TRedis::setEx(const QByteArray &key, const QByteArray &value, int seconds)
{
    if (!driver()) {
        return false;
    }

    QVariantList resp;
    QList<QByteArray> command = { "SETEX", key, QByteArray::number(seconds), value };
    return driver()->request(command, resp);
}

/*!
  Atomically sets the \a key to the \a value and returns the old value
  stored at the \a key.
 */
QByteArray TRedis::getSet(const QByteArray &key, const QByteArray &value)
{
    if (!driver()) {
        return QByteArray();
    }

    QVariantList resp;
    QList<QByteArray> command = { "GETSET", key, value };
    bool res = driver()->request(command, resp);
    return (res) ? resp.value(0).toByteArray() : QByteArray();
}

/*!
  Removes the specified \a key. A key is ignored if it does
  not exist.
 */
bool TRedis::del(const QByteArray &key)
{
    QList<QByteArray> keys = { key };
    int count = del(keys);
    return (count == 1);
}

/*!
  Removes the specified \a keys. A key is ignored if it does
  not exist.
 */
int TRedis::del(const QList<QByteArray> &keys)
{
    if (!driver()) {
        return 0;
    }

    QVariantList resp;
    QList<QByteArray> command = { "DEL" };
    command << keys;
    bool res = driver()->request(command, resp);
    return (res) ? resp.value(0).toInt() : 0;
}

/*!
  Inserts all the \a values at the tail of the list stored at the \a key.
  Returns the length of the list after the push operation.
 */
int TRedis::rpush(const QByteArray &key, const QList<QByteArray> &values)
{
    if (!driver()) {
        return false;
    }

    QVariantList resp;
    QList<QByteArray> command = { "RPUSH", key };
    command << values;
    bool res = driver()->request(command, resp);
    return (res) ? resp.value(0).toInt() : 0;
}

/*!
  Inserts all the \a values at the tail of the list stored at the \a key.
  Returns the length of the list after the push operation.
 */
int TRedis::lpush(const QByteArray &key, const QList<QByteArray> &values)
{
    if (!driver()) {
        return false;
    }

    QVariantList resp;
    QList<QByteArray> command = { "LPUSH", key };
    command << values;
    bool res = driver()->request(command, resp);
    return (res) ? resp.value(0).toInt() : 0;
}

/*!
  Returns the specified elements of the list stored at the \a key.
 */
QList<QByteArray> TRedis::lrange(const QByteArray &key, int start, int end = -1)
{
    if (!driver()) {
        return QList<QByteArray>();
    }

    QList<QByteArray> ret;
    QVariantList resp;
    QList<QByteArray> command = { "LRANGE", key, QByteArray::number(start), QByteArray::number(end) };
    bool res = driver()->request(command, resp);
    if (res) {
        for (auto &var : (const QVariantList&)resp) {
            ret << var.toByteArray();
        }
    }
    return ret;
}

/*!
  Returns the element at the \a index in the list stored at the \a key.
 */
QByteArray TRedis::lindex(const QByteArray &key, int index)
{
    if (!driver()) {
        return QByteArray();
    }

    QVariantList resp;
    QList<QByteArray> command = { "LINDEX", key, QByteArray::number(index) };
    bool res = driver()->request(command, resp);
    return (res) ? resp.value(0).toByteArray() : QByteArray();
}

/*!
  Returns the length of the list stored at the \a key.
*/
int TRedis::llen(const QByteArray &key)
{
    if (!driver()) {
        return -1;
    }

    QVariantList resp;
    QList<QByteArray> command = { "LLEN", key };
    bool res = driver()->request(command, resp);
    return (res) ? resp.value(0).toInt() : -1;
}


QList<QByteArray> TRedis::toByteArrayList(const QStringList &values)
{
    QList<QByteArray> ret;
    for (auto &val : values) {
        ret << val.toUtf8();
    }
    return ret;
}


QStringList TRedis::toStringList(const QList<QByteArray> &values)
{
    QStringList ret;
    for (auto &val : values) {
        ret << QString::fromUtf8(val);
    }
    return ret;
}


/*!
  \fn QString TRedis::gets(const QByteArray &key)
  Returns the string associated with the \a key; otherwise returns a
  null string.
 */

/*!
  \fn bool TRedis::sets(const QByteArray &key, const QString &value)
  Sets the \a key to hold the string \a value. If the key already holds
  a value, it is overwritten, regardless of its type.
 */

/*!
  \fn bool TRedis::setsEx(const QByteArray &key, const QString &value, int seconds)
  Sets the \a key to hold the string \a value and set the key to timeout
  after a given number of \a seconds.
 */

/*!
  \fn QString TRedis::getsSets(const QByteArray &key, const QString &value)
  Atomically sets the \a key to the string \a value and returns the old string
  value stored at the \a key.
 */

/*!
  \fn int TRedis::rpushs(const QByteArray &key, const QStringList &values);
  Inserts all the string \a values at the tail of the list stored at the
  \a key. Returns the length of the list after the push operation.
*/

/*!
  \fn int TRedis::lpushs(const QByteArray &key, const QStringList &values);
  Inserts all the string \a values at the tail of the list stored at the
  \a key. Returns the length of the list after the push operation.
*/

/*!
  \fn QStringList TRedis::lranges(const QByteArray &key, int start, int end);
  Returns the specified elements of the list stored at the \a key.
*/

/*!
  \fn QString TRedis::lindexs(const QByteArray &key, int index);
  Returns the string at the \a index in the list stored at the \a key.
*/
