#ifndef ITEMINFO_H
#define ITEMINFO_H

#include <QVariant>
#include <QTreeWidgetItem>
#include <QDateTime>
#include "share/defs.h"
#include "share/debug.h"

class Items
{
public:
    Items();

    struct Data
    {
        enum ESortOrder
        {
            ETypeName = 0,
            EOwner = 1,
            EDateTime = 2,
            ESize = 3
        };

        Data() : sortOrder(ETypeName) {}

        QString type;
        QString fileType;
        QString owner;
        QString fileSize;
        QString dateTime;
        QString name;
        QString self;
        QString parent;
        QString iconPath;
        QString downloadLink;
        QString uploadLink;

        bool operator < (const Data &other) const { return sort(other); }
        void setSortOrder(ESortOrder so) { sortOrder = so; }

    private:
        bool sort(const Data &other) const
        {
            switch(sortOrder)
            {
            case ETypeName: return sortByName(other);
            case EOwner: return sortByOwner(other);
            case EDateTime: return sortByDateTime(other);
            case ESize: return sortBySize(other);
            }

            return sortByName(other);
        }

        bool sortByName(const Data &other) const { return name.toLower() < other.name.toLower(); }
        bool sortByOwner(const Data &other) const { return owner.toLower() < other.owner.toLower(); }
        bool sortByDateTime(const Data &other) const { return QDateTime::fromString(dateTime, Qt::ISODate) < QDateTime::fromString(other.dateTime, Qt::ISODate); }
        bool sortBySize(const Data &other) const { return fileSize.toLongLong() < other.fileSize.toLongLong(); }

    private:
        ESortOrder sortOrder;
    };

public:
    void setFileSize(const QString &size, int index);
    void pushBack(Data &data);
    const QList<Data> &getItems() const;
    void setAccountOwner(const QString &name);
    QString getAccountOwner(void) const;
    void setDataOwner(const QString &name, int index);
    void sort(QList<Items::Data> &sortItems, Data::ESortOrder itemSortOrder, Qt::SortOrder sortOrder);

private:
    void setItemsSortOrder(QList<Data> &sortItems, Data::ESortOrder itemSortOrder);

private:
    QList<Data> items;
    QString accountOwner;
};

#endif // TREEITEMINFO_H
