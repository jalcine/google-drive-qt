#include "settings/settingsmanager.h"
#include "contentui.h"
#include "share/debug.h"
#include <QDir>

ContentUI::ContentUI(QObject *parent) :
    QObject(parent)
{
}

void ContentUI::slotLeftViewClicked(const QModelIndex&)
{
    SettingsManager().setCurrentPanel(LEFT_PANEL_VALUE);
}

void ContentUI::slotRightViewClicked(const QModelIndex&)
{
    SettingsManager().setCurrentPanel(RIGHT_PANEL_VALUE);
}

void ContentUI::slotLeftPanelItemDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    SettingsManager().setCurrentPanel(LEFT_PANEL_VALUE);
    showFilesOnPanel(item->data(0, Qt::DisplayRole).toString(), ELeft);
}

void ContentUI::slotRightPanelItemDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    SettingsManager().setCurrentPanel(RIGHT_PANEL_VALUE);
    showFilesOnPanel(item->data(0, Qt::DisplayRole).toString(), ERight);
}

void ContentUI::showFilesOnPanel(const QString &name, EPanels panel)
{
    if(name == PARENT_FOLDER_SIGN)
    {
        performShowFiles(SDriveEngine::inst()->getContentMngr()->back(), name, EBackward, panel);
    }
    else
    {
        if(isFolder())
        {
            QString query(GET_FILES_IN_FOLDER);

            query += CommonTools::getIDFromURL(SDriveEngine::inst()->getContentMngr()->getCurrentFileInfo().self);
            query += (CONTENTS + MAX_RESULTS);

            performShowFiles(query, name, EForward, panel);
        }
    }
}

bool ContentUI::isFolder(void)
{
  return (SDriveEngine::inst()->getContentMngr()->getCurrentFileInfo().type == FOLDER_TYPE_STR);
}

void ContentUI::setCurrentPanelState(EPanels panel, const QString &url)
{
    SettingsManager settingsManager;

    int panelNum = static_cast <int> (panel);

    settingsManager.setCurrentFolderURL(panelNum, url);

    QString fullPath(getPanelLabel(panel)->text());
    int beginPos = fullPath.indexOf(QDir::toNativeSeparators("/")) + 1;
    int length = fullPath.length() - beginPos;

    settingsManager.setCurrentFolderPath(panelNum, fullPath.mid(beginPos, length));
    settingsManager.setPathesURLs(panelNum, SDriveEngine::inst()->getContentMngr()->getPathesURLs());
}

void ContentUI::performShowFiles(const QString &query, const QString &name, EPath path, EPanels panel)
{
    setPanelDisplayingPath(name, path, panel);
    SDriveEngine::inst()->getContentMngr()->get(query);
    setCurrentPanelState(panel, query);

    children.fetch();
}

void ContentUI::slotUpdateFileList()
{
    SDriveEngine::inst()->getContentMngr()->get(SDriveEngine::inst()->getContentMngr()->getParentFolderUrl());
}

void ContentUI::setPanelDisplayingPath(const QString &name, EPath path, EPanels panel)
{
    QLabel* label = getPanelLabel(panel);
    QString pathDividerSign(QDir::toNativeSeparators("/"));
    int labelTextlength = label->text().length();
    int discStrLength = getDiscLength(panel);

    switch(path)
    {
    case EForward:
    {
        QString divider((labelTextlength == discStrLength) ? "" : pathDividerSign);
        label->setText(label->text() += (divider + name));
    }
        break;
    case EBackward:
    {
        int pos = label->text().lastIndexOf(pathDividerSign);
        int removeCount = labelTextlength - (pos + 1) + 1;

        if(pos == (discStrLength - 1)) ++pos;

        label->setText(label->text().remove(pos,  removeCount));
    }
        break;
    }
}

int ContentUI::getDiscLength(EPanels panel) const
{
    SettingsManager settingsManager;
    QString disc(settingsManager.accountDisc(settingsManager.currentAccount(static_cast <int> (panel))));

    disc += QString(":");
    disc += QDir::toNativeSeparators("/");

    return disc.length();
}

QLabel* ContentUI::getPanelLabel(EPanels panel) const
{
    return  SDriveEngine::inst()->getFilePanel(panel)->getPathLabel();
}


