#ifndef FILESUI_H
#define FILESUI_H

#include "core/driveengine.h"
#include "share/enums.h"
#include <QLabel>

//class FilesManager;

class ContentUI: public QObject
{
    Q_OBJECT
public: 
    enum EPath
    {
        EForward,
        EBackward
    };

    explicit ContentUI(QObject *parent = 0);

    friend class FilesTransferUI;
    friend class FoldersUI;
    friend class OperationsUI;
    friend class DriveEngine;

public:
    QLabel* getPanelLabel(EPanels panel) const;

private slots:
    void slotLeftViewClicked(const QModelIndex&);
    void slotRightViewClicked(const QModelIndex&);
    void slotLeftPanelItemDoubleClicked(QTreeWidgetItem *item, int column);
    void slotRightPanelItemDoubleClicked(QTreeWidgetItem *item, int column);
    void slotUpdateFileList();

private:
    int getDiscLength(EPanels panel) const;
    void setPanelDisplayingPath(const QString &name, EPath path, EPanels panel);
    void showFilesOnPanel(const QString &name, EPanels panel);
    void setCurrentPanelState(EPanels panel, const QString &url);
    void performShowFiles(const QString &query, const QString &name, EPath path, EPanels panel);
    bool isFolder(void);
    Children children;
};

#endif // FILESUI_H
