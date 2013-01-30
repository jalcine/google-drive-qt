#include "downloadmanager.h"
#include "gui/forms/mainwindow.h"
#include "settings/settingsmanager.h"
#include "share/debug.h"
#include "ui_mainwindow.h"

DownloadFileManager::DownloadFileManager(QObject *parent) :
    NetworkManager(parent)
{
}

void DownloadFileManager::startDownload(QUrl url, QString& fileName, const QString& type)
{
    init();

    fileType = type;

    CommonTools::setHeader(SettingsManager().accessToken(), request);

    setProgressBarSettings(fileName, tr("Downloading file: "));

    request.setUrl(url);

    file.open(QIODevice::WriteOnly);

    reply = networkManager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(slotDownloadFinished()));
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotDownloadReadyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(slotDownloadProgress(qint64,qint64)));

    connectErrorHandlers();
}

void DownloadFileManager::slotDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    progressBarDialog.setMaximum(bytesTotal);
    progressBarDialog.setValue(bytesReceived);
}

void DownloadFileManager::slotDownloadFinished()
{
    progressBarDialog.hide();

    state = EReady;

    file.flush();
    file.close();
}

void DownloadFileManager::slotDownloadReadyRead()
{
    file.write(reply->readAll());
}
