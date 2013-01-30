#ifndef CREATE_H
#define CREATE_H

#include "network/networkmanager.h"
#include "operation.h"
#include "gui/items.h"

class Create : public NetworkManager, public Operation
{
    Q_OBJECT
public:
    Create(QObject *parent = 0);

protected slots:
    void slotPostFinished(QNetworkReply* reply);

public:
    void folder(const QString &name, const QString &parentFolderUrl);
};

#endif // CREATE_H
