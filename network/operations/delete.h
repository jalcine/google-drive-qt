#ifndef DELETE_H
#define DELETE_H

#include "network/networkmanager.h"
#include "operation.h"
#include "gui/items.h"

class Delete : public NetworkManager, public Operation
{
    Q_OBJECT
public:
    Delete(QObject *parent = 0);
    void item(const Items::Data &source);

protected slots:
    void slotReplyFinished(QNetworkReply*);
};

#endif // DELETE_H
