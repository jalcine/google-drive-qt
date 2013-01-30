#ifndef UPLOAD_H
#define UPLOAD_H

#include <QNetworkAccessManager>

class Upload : public QNetworkAccessManager
{
public:
    Upload(QObject *parent = 0);
};

#endif // UPLOAD_H
