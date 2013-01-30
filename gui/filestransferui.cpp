#include "filestransferui.h"
#include "share/debug.h"
#include "settings/settingsmanager.h"
#include <QFileDialog>
#include <QDir>

FilesTransferUI::FilesTransferUI(QObject *parent) :
    QObject(parent)
{
}

void FilesTransferUI::download(void)
{
    if(SDriveEngine::inst()->downloadMngr)
    {
        if(SDriveEngine::inst()->downloadMngr->getState() == NetworkManager::EBusy) return;
    }

    Items::Data item = SDriveEngine::inst()->getContentMngr()->getCurrentFileInfo();

    QString downloadLink(item.downloadLink);

    if(SDriveEngine::inst()->checkUI->slotCheckWorkDir(false))
    {
        QString fileName(SettingsManager().workDir() + QDir::toNativeSeparators("/") + item.name);

        SDriveEngine::inst()->downloadMngr.reset(new DownloadFileManager(SDriveEngine::inst()->parent));
        SDriveEngine::inst()->downloadMngr->startDownload(QUrl(downloadLink), fileName, item.fileType);
    }
    else
    {
        CommonTools::msg(tr("Please note: you must set working directory for downloading files"));
    }
}

void FilesTransferUI::upload(void)
{
    if(SDriveEngine::inst()->uploadFileMngr)
    {
        if(SDriveEngine::inst()->uploadFileMngr->getState() == NetworkManager::EBusy) return;
    }

    QString  fileName = QFileDialog::getOpenFileName(SDriveEngine::inst()->parent, tr("Uploading file"), QDir::homePath(), tr("All files(*)"));

    if(!fileName.isEmpty())
    {
        QString uploadLink(SDriveEngine::inst()->getContentMngr()->getUpperLevelFolderInfo().uploadLink + QString("/?convert=false"));

        SDriveEngine::inst()->uploadFileMngr.reset(new UploadFileManager(SDriveEngine::inst()->parent));
        connect(SDriveEngine::inst()->uploadFileMngr.data(), SIGNAL(signalUpdateFileList()), SDriveEngine::inst()->filesUI.data(), SLOT(slotUpdateFileList()));
        SDriveEngine::inst()->uploadFileMngr->startUpload(uploadLink, fileName);
    }
}

void FilesTransferUI::slotDownload(void)
{
    download();
}

void FilesTransferUI::slotUpload(void)
{
    upload();
}
