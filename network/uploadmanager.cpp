#include "uploadmanager.h"
#include "settings/settingsmanager.h"

UploadFileManager::UploadFileManager(QObject *parent) :
    NetworkManager(parent),
    allowPut(true)
{
}

void UploadFileManager::slotUploadFinished()
{
    progressBarDialog.hide();

    state = EReady;

    if (!operationCanceled)
    {
        emit signalUpdateFileList();
    }
}

void UploadFileManager::setUploadSettings(void)
{
    QFileInfo fileInfo(file);
    QString ext = fileInfo.suffix();
    QString title = fileInfo.fileName();
    QString contentType = getContentTypeByExtension(ext);


    QString protocol = QString("<?xml version='1.0' encoding='UTF-8'?>"
                                   "<entry xmlns=\"http://www.w3.org/2005/Atom\">  xmlns:docs=\"http://schemas.google.com/docs/2007\">"
                                   "<title>%1</title>"
                                   "</entry>").arg(title);

    postData = protocol.toLatin1();

    CommonTools::setHeader(SettingsManager().accessToken(), request);

    request.setRawHeader("Content-Length", QString::number(postData.size()).toLatin1());
    request.setRawHeader("Content-Type", "application/atom+xml");
    request.setRawHeader("X-Upload-Content-Length", (QString("%1").arg(fileInfo.size())).toLatin1());
    request.setRawHeader("X-Upload-Content-Type", contentType.toLatin1());
}

void UploadFileManager::postFinishedActions(QNetworkReply* reply)
{
    QString location = reply->rawHeader("Location");

    if (!location.isEmpty())
    {
        if(allowPut)
        {
            allowPut = false;

            QFileInfo fi(file.fileName());
            QString ext = fi.suffix().toLower();
            QString contentType = getContentTypeByExtension(ext);

            file.open(QIODevice::ReadOnly);

            QByteArray arr = file.readAll();

            file.close();

            qlonglong fileSize = arr.count();

            request.setRawHeader("Content-Type", contentType.toLatin1());
            request.setRawHeader("Content-Length", (QString("%1").arg(fileSize)).toLatin1());
            request.setRawHeader("Content-Range", (QString("bytes 0-%1/%2").arg(fileSize-1).arg(fileSize)).toLatin1());

            putRequest(location, arr);
        }
    }
}

void UploadFileManager::slotUploadProgress( qint64 bytesSent, qint64 bytesTotal )
{
    progressBarDialog.setMaximum(bytesTotal);
    progressBarDialog.setValue(bytesSent);
}

void UploadFileManager::startUpload(QUrl url, const QString &fileName)
{
    setProgressBarSettings(fileName, fileName);
    postRequest(url);
}

void UploadFileManager::setProgressBarSettings(const QString &fileName, const QString &progressBarDialogInfoText)
{
    Q_UNUSED(progressBarDialogInfoText);

    NetworkManager::setProgressBarSettings(fileName, tr("Uploading file: "));
    setUploadSettings();
}

QString UploadFileManager::getContentTypeByExtension(const QString &ext)
{
    QString contentType;

    if(ext == "doc" || ext == "docx") contentType = "application/msword";
    if(ext == "xls") contentType = "application/vnd.ms-excel";
    if(ext == "ppt" || ext == "pptx") contentType = "application/vnd.ms-powerpoint";
    if(ext == "pdf") contentType = "application/pdf";
    if(ext == "exe") contentType = "application/x-msdos-program";
    if(ext == "rar") contentType = "application/rar";
    if(ext == "png") contentType = "image/png";
    if(ext == "png") contentType = "application/rtf";
    if(ext == "tar") contentType = "application/x-tar";
    if(ext == "zip") contentType = "application/zip";
    if(ext == "") contentType = "";
    if(ext == "jpeg" || ext == "jpg" || ext == "jpe") contentType = "image/jpeg";
    if(ext == "gif") contentType = "image/gif";
    if(ext == "wav") contentType = "application/x-wav";
    if(ext == "tiff" || ext == "tif") contentType = "image/tiff";
    if(ext == "txt" || ext == "cpp" || ext == "h" || ext == "c") contentType = "text/plain";
    if(ext == "mpeg" || ext == "mpg" || ext == "mpe" ) contentType = "video/mpeg";
    if(ext == "qt" || ext == "mov") contentType = "video/quicktime";
    if(ext == "qvi") contentType = "video/x-msvideo";
    if(ext == "video/x-sgi-movie") contentType = "movie";
    if(ext == "exe") contentType = "application/x-msdos-program";

    return contentType;
}
