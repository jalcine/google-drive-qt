#include "contentmanager.h"
#include "share/commontools.h"
#include "settings/settingsmanager.h"
#include "core/driveengine.h"
#include "share/debug.h"
#include <QLocale>
#include <QDateTime>
#include <QPair>
#include <QApplication>

ContentManager::ContentManager(QObject *parent):
    NetworkManager(parent),
    panel(NULL)
{
    parser.reset(new XMLParser);
}

ContentManager::~ContentManager()
{
    if(panel && !panel->topLevelItemCount() > 0) panel->clear();
    pathesURLs.clear();
}

void ContentManager::get(const QString &url)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    CommonTools::setHeader(SettingsManager().accessToken(), request);
    getRequest(url);
}

void ContentManager::slotReplyFinished(QNetworkReply* reply)
{
    //CommonTools::logToFile(QString("ParserReply ") + ".txt", replyStr.toAscii());

//    DEBUG << "<===============================================================================================================";
//    DEBUG << "replyStr" << replyStr;
//    DEBUG << "===============================================================================================================>";

    /*if(*/parseReply(replyStr);/*) DEBUG << "parse OK"*/
    //    else DEBUG << "parse not OK";

    replyStr.clear();

    if(!parser->getXMLHandler()->resDownloadingNow() && reply->error() != QNetworkReply::AuthenticationRequiredError)
    {
        show();
    }

    QApplication::restoreOverrideCursor();
}

bool ContentManager::parseReply(const QString &str)
{
    QXmlSimpleReader reader;
    QXmlInputSource source;

    parser.reset(new XMLParser);

    connect(parser->getXMLHandler(), SIGNAL(signalAllResDownloaded()),this, SLOT(slotResDownloaded()));

    source.setData(str.toAscii());

    reader.setContentHandler(parser.data());
    reader.setErrorHandler(parser.data());

    return reader.parse(&source);
}

void ContentManager::slotResDownloaded(void)
{
    show();
}

XMLParser* ContentManager::getParser(void) const
{
    return parser.data();
}

void ContentManager::clear(void)
{
    treeWidgetItems.clear();

    if(treeWidgetItems.empty()) return;

    for(int i = 0; i < treeWidgetItems.count(); ++i)
    {
        delete treeWidgetItems[i];
    }
}

void ContentManager::show(void)
{
    if(!panel) return;

    clear();
    panel->clear();

    updateItemsState();

    if(getRequest().url() != GET_FULL_ROOT_CONTENT)
    {
        isRoot = false;

        treeWidgetItems.push_back(new QTreeWidgetItem(panel));
        treeWidgetItems.last()->setText(0, PARENT_FOLDER_SIGN);
    }
    else
    {
        isRoot = true;
    }

    for(int i = 0; i < normalizedItems.count(); ++i)
    {
        addItem(normalizedItems[i]);
    }

    if(SettingsManager().initialLoading()) emit signalFirstPanelIsLoaded();

    QString url(getRequest().url().toString());

    if(!pathesURLs.contains(url)) pathesURLs.push_back(url);

    connect(panel->header(),SIGNAL(sectionClicked(int)), this, SLOT(slotSectionClicked(int)));
}

void ContentManager::setItems(Items::Data::ESortOrder itemSortOrder, Qt::SortOrder sortOrder)
{
    normalizedItems = parser->getXMLHandler()->getItemInfo()->getItems();

    if(!normalizedItems.isEmpty())
    {
        rootData = normalizedItems.takeFirst();
    }

    parser->getXMLHandler()->getItemInfo()->sort(normalizedItems, itemSortOrder, sortOrder);
}

void ContentManager::addItem(const Items::Data &itemData)
{
    treeWidgetItems.push_back(new QTreeWidgetItem(panel));

    treeWidgetItems.last()->setText(0, itemData.name);
    treeWidgetItems.last()->setIcon(0, QPixmap(itemData.iconPath));
    treeWidgetItems.last()->setText(1, itemData.owner);
    treeWidgetItems.last()->setText(2, getDate(itemData.dateTime));
    treeWidgetItems.last()->setText(3, getSize(itemData.fileSize));
}

QString ContentManager::getDate(const QString &date)
{
    QDateTime fileDateTime = QDateTime::fromString(date, Qt::ISODate);
    return fileDateTime.toLocalTime().toString("ddd, MMM d yyyy, h:mm");
}

QString ContentManager::getSize(const QString &size)
{
    QString formattedSize;

    if(size.toLongLong() > 0)
    {
        formattedSize = QLocale().toString(size.toLongLong());
    }

    return formattedSize;
}

void ContentManager::setPanel(QTreeWidget *p, int pn)
{
    panel = p;
    panelNum = pn;
}

QTreeWidget* ContentManager::getPanel(void) const
{
    return panel;
}

QString ContentManager::getParentFolderUrl(void) const
{
    return pathesURLs.last();
}

Items::Data ContentManager::getUpperLevelFolderInfo(void) const
{
    return  rootData;
}

QString ContentManager::back(void)
{
    QString prevLink;

    if(!pathesURLs.isEmpty())
    {
        pathesURLs.pop_back();
        prevLink = pathesURLs.last();
        pathesURLs.pop_back();
    }

    return prevLink;
}

QStringList ContentManager::getPathesURLs(void) const
{
    return pathesURLs;
}

void ContentManager::setPathesURLs(const QStringList &pathesURLsStrList)
{
    pathesURLs = pathesURLsStrList;
}

void ContentManager::sort(int column, Qt::SortOrder order)
{
}

Items::Data ContentManager::getCurrentFileInfo(void)
{
    int index;

    if(isRoot) index = panel->currentIndex().row();
    else index = panel->currentIndex().row() - 1;

    if(index < 0) index = 0;

    return  normalizedItems[index];
}

void ContentManager::slotSectionClicked(int logicalIndex)
{
    Q_UNUSED(logicalIndex);
    SettingsManager().savePanelHeaderState(panelNum, panel->header()->saveState());
    show();
}

void ContentManager::updateItemsState(void)
{
    Items::Data::ESortOrder itemSortOrder;
    Qt::SortOrder sortOrder;

    QByteArray values(SettingsManager().restorePanelHeaderState(panelNum));

    if(values.isEmpty())
    {
        itemSortOrder = Items::Data::ETypeName;
        sortOrder = Qt::AscendingOrder;

        panel->header()->setSortIndicator(0, sortOrder);
    }
    else
    {
        panel->header()->restoreState(values);

        itemSortOrder = static_cast<Items::Data::ESortOrder> (panel->header()->sortIndicatorSection());
        sortOrder =  static_cast<Qt::SortOrder> (panel->header()->sortIndicatorOrder());
    }

    setItems(itemSortOrder, sortOrder);
}



