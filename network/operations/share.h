#ifndef SHARE_H
#define SHARE_H

#include "network/networkmanager.h"
#include "gui/items.h"

class Share : public NetworkManager
{
    Q_OBJECT
public:
    Share(QObject *parent = 0);

public:
    void file(const Items::Data &source);
};

#endif // SHARE_H
