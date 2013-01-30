#include "queries.h"
#include "share/commontools.h"
#include "settings/settingsmanager.h"
#include <QString>

Queries::Queries() :
    urlStartPart("https://www.googleapis.com/drive/v2/")
{
}

void Queries::setRawHeader(const QString &accessToken, QNetworkRequest &request)
{
    request.setRawHeader("User-Agent", SettingsManager().applicationName().toAscii());
    request.setRawHeader("Authorization", QString("Bearer %1").arg(accessToken).toAscii());
    request.setRawHeader("Content-Type", "application/json");
}

void Queries::userAboutInfo(QString &userInfoQuery, QString &aboutInfoQuery)
{
    userInfoQuery = QString("https://www.googleapis.com/oauth2/v1/userinfo");
    aboutInfoQuery = urlStartPart + QString("about");
}

QByteArray Queries::getCopyFileData(const QString &sourceName, const QString &destFolderUrl)
{
    return QString("{\"kind\": \"drive#file\", \"title\": \"%1\",\"parents\": [{\"id\":\"%2\"}]}").arg(sourceName).arg(CommonTools::getIDFromURL(destFolderUrl)).toAscii();
}

QUrl Queries::constructCopyFileUrl(const QString &url)
{
    return QUrl(QString(urlStartPart + QString("files/") + CommonTools::getIDFromURL(url) + QString("/copy")));
}

QByteArray Queries::getRenameFileData(const QString &newName)
{
    return QString("{\"title\": \"%1\"}").arg(newName).toAscii();
}

QUrl Queries::constructRenameFileUrl(const QString &sourceName)
{
    return QUrl(urlStartPart + QString("files/") + CommonTools::getIDFromURL(sourceName));
}

QByteArray Queries::getCreateFolderData( const QString &name, const QString &folderUrl)
{
    return QString("{\"title\": \"%1\",\"parents\": [{\"id\": \"%2\"}],\"mimeType\": \"application/vnd.google-apps.folder\"}").arg(name).arg(CommonTools::getIDFromURL(folderUrl)).toAscii();
}

QUrl Queries::constructCreateFolderUrl(void)
{
    return QUrl(urlStartPart + QString("files"));
}

QUrl Queries::constructDeleteFileUrl(const QString &sourceName)
{
  return QUrl(urlStartPart + QString("files/") + CommonTools::getIDFromURL(sourceName));
}

QString Queries::construcChildrenUrl(const QString &Id)
{
    return QString(urlStartPart + QString("files?q=\"") + Id + QString("\" in parents"));
}

