#include "singleton.h"

template <class T>
T* Singleton<T>::instance(CreateInstanceFunction create)
{
  Singleton::create.store(create);
  qCallOnce(init, flag);
  return (T*)tptr.load();
}

template <class T>
void Singleton<T>::init()
{
  static Singleton singleton;
  if (singleton.inited) {
    CreateInstanceFunction createFunction = (CreateInstanceFunction)Singleton::create.load();
    tptr.store(createFunction());
  }
}

template <class T>
Singleton<T>::Singleton() {
  inited = true;
};

template <class T>
Singleton<T>::~Singleton() {
  T* createdTptr = (T*)tptr.fetchAndStoreOrdered(nullptr);
  if (createdTptr) {
    delete createdTptr;
  }
  create.store(nullptr);
}
