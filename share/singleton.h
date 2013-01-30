#ifndef SINGLETON_H
#define SINGLETON_H

#include <QObject>

template <typename T>
class TSingleton
{
public:
    static T* inst(void);
    static T* inst(QWidget *parent);
    static void freeInst(void);

private:
    TSingleton(){}
    ~TSingleton(){}
    Q_DISABLE_COPY(TSingleton)

private:
    static T* instObject;
};

template <typename T>
T* TSingleton<T>::instObject = NULL;

template <typename T>
T* TSingleton<T>::inst(void)
{
    if(!instObject) instObject = new T;
    return instObject;
}

template <typename T>
T* TSingleton<T>::inst(QWidget *parent)
{
    if(!instObject) instObject = new T(parent);
    return instObject;
}

template <typename T>
void TSingleton<T>::freeInst(void)
{
    if(instObject) delete instObject;
    instObject = NULL;
}

#endif // SINGLETON_H
