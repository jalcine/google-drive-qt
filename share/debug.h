#ifndef DEBUG_H
#define DEBUG_H

#include <QDebug>

#ifdef Q_WS_WIN
   #define DEBUG qDebug() << "[ DEBUG:" << __PRETTY_FUNCTION__ << ", line:" << __LINE__ << "]"
#else
   #define DEBUG qDebug() << "[ DEBUG:" << __FUNCTION__ << ", line:" << __LINE__ << "]"
#endif
#endif // DEBUG_H
