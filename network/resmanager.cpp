#include "resmanager.h"
#include "share/commontools.h"

ResManager::ResManager(QObject *parent):
            DownloadFileManager(parent)
{
}

void ResManager::cash(const QString &url)
{
  QString fileNameToSave(QFileInfo(url).fileName());

  startDownload(QUrl(url), fileNameToSave, "image/png");
}

void ResManager::slotDownloadFinished()
{
    DownloadFileManager::slotDownloadFinished();
    emit signalResDownloaded();
}
