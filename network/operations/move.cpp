#include "move.h"

Move::Move(QObject *parent) :
    QObject(parent)
{
}

void Move::item(const Items::Data &source, const QString &destFolderUrl)
{
    copy.file(source, destFolderUrl);
    connect(&copy, SIGNAL(fileCopied(Items::Data&)), this, SLOT(slotFileCopied(Items::Data&)));
}

void Move::slotFileCopied(Items::Data &source)
{
    del.item(source);
}
