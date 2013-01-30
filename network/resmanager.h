#ifndef RESMANAGER_H
#define RESMANAGER_H

#include "share/defs.h"
#include "network/downloadmanager.h"

class ResManager: public DownloadFileManager
{
     Q_OBJECT
public:
    explicit ResManager(QObject *parent = 0);

public:
    void cash(const QString &url);

public slots:
    virtual void slotDownloadFinished();

signals:
    void signalResDownloaded();
};

#endif // RESMANAGER_H
