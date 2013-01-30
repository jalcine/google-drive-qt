#include "copy.h"
#include "settings/settingsmanager.h"

Copy::Copy(QObject *parent) :
    NetworkManager(parent)
{
}

void Copy::file(const Items::Data &source, const QString &destFolderUrl)
{
    sourceData = source;
    postData = queries.getCopyFileData(source.name, destFolderUrl);

    queries.setRawHeader(SettingsManager().accessToken(), request);
    postRequest(queries.constructCopyFileUrl(source.self));
}

void Copy::slotPostFinished(QNetworkReply *reply)
{
    NetworkManager::slotPostFinished(reply);
    updatePanelContent(true);

    emit fileCopied(sourceData);
}
