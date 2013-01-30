#ifndef MOVE_H
#define MOVE_H

#include <QObject>
#include "network/operations/copy.h"
#include "network/operations/delete.h"

class Move : public QObject
{
    Q_OBJECT
public:
    Move(QObject* parent = 0);

public:
    void item(const Items::Data &source, const QString &destFolderUrl);

private slots:
    void slotFileCopied(Items::Data &source);

private:
    Copy copy;
    Delete del;
};

#endif // MOVE_H
