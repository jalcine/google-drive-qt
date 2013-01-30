#ifndef QUERIES_H
#define QUERIES_H

#include <QObject>
#include <QUrl>
#include <QNetworkRequest>

class Queries : public QObject
{
     Q_OBJECT
public:
    Queries();

public:
    void userAboutInfo(QString &userInfoQuery, QString &aboutInfoQuery);
    QByteArray getCopyFileData(const QString &sourceName, const QString &destFolderUrl);
    QUrl constructCopyFileUrl(const QString &url);
    void setRawHeader(const QString &accessToken, QNetworkRequest &request);
    QByteArray getRenameFileData(const QString &newName);
    QUrl constructRenameFileUrl(const QString &sourceName);
    QByteArray getCreateFolderData(const QString &name, const QString &folderUrl);
    QUrl constructCreateFolderUrl(void);
    QUrl constructDeleteFileUrl(const QString &sourceName);
    QString construcChildrenUrl(const QString &Id);

private:
   QString urlStartPart;
};

#endif // QUERIES_H
