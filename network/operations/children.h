#ifndef CHILDREN_H
#define CHILDREN_H

#include "network/networkmanager.h"
#include "operation.h"
#include "gui/items.h"

class Children : public NetworkManager,  public Operation
{
    Q_OBJECT
public:    
    Children(QObject *parent = 0);

protected slots:
     void slotReplyFinished(QNetworkReply *reply);

public:
     void fetch(const Items::Data &source = Items::Data());

};

#endif // CHILDREN_H
