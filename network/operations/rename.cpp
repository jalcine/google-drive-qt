#include "rename.h"
#include "settings/settingsmanager.h"

Rename::Rename(QObject *parent) :
    NetworkManager(parent)
{
}

void Rename::item(const Items::Data &source, const QString &newName)
{
    postData = queries.getRenameFileData(newName);
    queries.setRawHeader(SettingsManager().accessToken(), request);
    putRequest(QUrl(queries.constructRenameFileUrl(source.self)));
}

void Rename::slotPutFinished(void)
{
    updatePanelContent(false);
}
