#include "items.h"
#include <QtAlgorithms>

Items::Items()
{
}

void Items::setFileSize(const QString &size, int index)
{
    items[index].fileSize = size;
}

const QList<Items::Data> &Items::getItems() const
{
    return items;
}

void Items::sort(QList<Items::Data> &sortItems, Data::ESortOrder itemSortOrder, Qt::SortOrder sortOrder)
{
    setItemsSortOrder(sortItems, itemSortOrder);

    QList<Items::Data> folderItems, fileItems;

    for(int i = 0; i < sortItems.count(); ++i)
    {
        if(sortItems[i].type == FOLDER_TYPE_STR) folderItems.push_back(sortItems[i]);
        if(sortItems[i].type == FILE_TYPE_STR) fileItems.push_back(sortItems[i]);
    }

    if(sortOrder == Qt::AscendingOrder)
    {
        qSort(folderItems.begin(), folderItems.end());
        qSort(fileItems.begin(), fileItems.end());
    }

    if(sortOrder == Qt::DescendingOrder)
    {
        qSort(folderItems.begin(), folderItems.end(), qGreater<Items::Data>());
        qSort(fileItems.begin(), fileItems.end(), qGreater<Items::Data>());
    }

    for(int i = 0; i < folderItems.count(); ++i)
    {
        sortItems[i] = folderItems[i];
    }

    for(int i = folderItems.count(), j = 0; i < sortItems.count(); ++i, ++j)
    {
        sortItems[i] = fileItems[j];
    }
}

void Items::setItemsSortOrder(QList<Items::Data> &sortItems, Data::ESortOrder itemSortOrder)
{
    for(int i = 0; i < sortItems.count(); ++i)
    {
        sortItems[i].setSortOrder(itemSortOrder);
    }
}

void Items::pushBack(Items::Data &data)
{
    items.push_back(data);
}

void Items::setAccountOwner(const QString &name)
{
    accountOwner = name;
}

QString Items::getAccountOwner(void) const
{
    return accountOwner;
}

void Items::setDataOwner(const QString &name, int index)
{
    items[index].owner = name;
}

