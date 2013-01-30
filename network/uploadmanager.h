#ifndef UPLOADMANAGER_H
#define UPLOADMANAGER_H

#include "share/commontools.h"
#include "networkmanager.h"
#include <QFileInfo>

class UploadFileManager : public NetworkManager
{
    Q_OBJECT
public:  
    explicit UploadFileManager(QObject *parent = 0);

signals:
    void signalUpdateFileList();

public slots:
    virtual void slotUploadFinished();
    virtual void slotUploadProgress(qint64 bytesSent, qint64 bytesTotal);

public:
    void setUploadSettings(void);
    void startUpload(QUrl url, const QString &fileName);

protected:
    void setProgressBarSettings(const QString &fileName, const QString &progressBarDialogInfoText);
    void postFinishedActions(QNetworkReply* reply);

private:
    QString getContentTypeByExtension(const QString &ext);

private:
    bool allowPut;
};

#endif // UPLOADMANAGER_H
