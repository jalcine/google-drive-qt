#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <QObject>
#include <QXmlAttributes>
#include "gui/items.h"
#include "share/defs.h"
#include "network/resmanager.h"

class XMLHandler : public QObject
{
    Q_OBJECT
public:

    enum ETags
    {
        ETitle,
        ESize,
        EUpdated,
        EAuthor,
        EEntry,
        ETagsCount
    };

    XMLHandler();
    ~XMLHandler();

public:
    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &attribs);
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);
    bool characters(const QString &str);
    bool fatalError(const QXmlParseException &exception);

    Items* getItemInfo(void) const;
    bool resDownloadingNow(void) const;

public slots:
    void slotResDownloaded();

signals:
    void signalAllResDownloaded(void);

private:
    bool handleReply(const QString &qName, const QXmlAttributes &attribs);
    void handleAuthorTag(const QString &str, bool entryTag);
    void handleTitleTag(const QString &str);
    void handleSizeTag(const QString &str);
    void handleUpdatedTag(const QString &str);
    void setDefaults(void);
    void setTag(const QString& qName, bool state);
    QString getItemType(const QString &selfURL);
    void saveResData(const QXmlAttributes &attribs);

private:
    QScopedPointer<Items> itemInfo;
    Items::Data itemData;
    QList<ResManager*> resManagers;
    int resDownloadedCount;
    bool isResDownloding;
    bool tags[ETagsCount];
};

#endif // XMLHANDLER_H
