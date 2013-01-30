#include "networkmanager.h"
#include "share/commontools.h"
#include "share/debug.h"

NetworkManager::NetworkManager(QObject *parent) :
    QObject(parent),
    state(EReady),
    operationCanceled(false)
{
    this->parent = parent;
}

void NetworkManager::init(void)
{
    networkManager.reset(new QNetworkAccessManager(this));
}

QNetworkAccessManager* NetworkManager::getNetworkManager(void) const
{
    return  networkManager.data();
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::slotReplyReadyRead()
{
    replyStr.append(reply->readAll());
}

void NetworkManager::slotError(QNetworkReply::NetworkError error)
{
    DEBUG << "error code:" << error;

    state = EReady;

    if(error == QNetworkReply::AuthenticationRequiredError)
    {
        DEBUG << "AuthenticationRequiredError URL" << request.url();
        reply->abort();
        emit signalAccessTokenRequired();
    }

    if(error == QNetworkReply::UnknownNetworkError)
    {
        static bool msgOnScreen = false;
        QString msgStr("If this error occur, please make sure that you have openssl installed (also you can copy libeay32.dll and ssleay32.dll files from Qt SDK MSVC*/bin folder into folder where your program .exe file is located (tested on non-static compilation only))");

        if(!msgOnScreen)
        {
            msgOnScreen = true;
            CommonTools::errorMsg("QNetworkReply::UnknownNetworkError", msgStr);
            msgOnScreen = false;
        }
    }
}

void NetworkManager::slotSslErrors(const QList<QSslError> &errors)
{
    foreach(const QSslError &e, errors) DEBUG << "error:" << e.error();
}

NetworkManager::EStates NetworkManager::getState(void) const
{
    return state;
}

void NetworkManager::setState(NetworkManager::EStates currentState)
{
    state = currentState;
}

void NetworkManager::connectErrorHandlers(void)
{
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(const QList<QSslError>&)),this, SLOT(slotSslErrors(const QList<QSslError>&)));
}

void NetworkManager::setProgressBarSettings(const QString &fileName, const QString &progressBarDialogInfoText)
{
    state = EBusy;
    operationCanceled = false;

    file.setFileName(fileName);

    QFileInfo fi(file.fileName());

    progressBarDialog.setParent(static_cast<QWidget*>(parent), Qt::Dialog);
    progressBarDialog.setText(progressBarDialogInfoText + fi.fileName());
    progressBarDialog.show();

    connect(&progressBarDialog, SIGNAL(signalProgressCanceled()), this, SLOT(slotProgressCanceled()));  
}

void NetworkManager::slotProgressCanceled()
{
    operationCanceled = true;
    reply->abort();
}

void NetworkManager::slotPostFinished(QNetworkReply* reply)
{
    if (reply->error())
    {
        progressBarDialog.hide();
        DEBUG << "Reply with the error";

        return;
    }

    postFinishedActions(reply);
}

void NetworkManager::getRequest(const QString &url)
{
    init();

    request.setUrl(QUrl(url));

    reply = networkManager->get(request);

    connect(networkManager.data(), SIGNAL(finished(QNetworkReply*)),this, SLOT(slotReplyFinished(QNetworkReply*)));
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReplyReadyRead()));

    connectErrorHandlers();
}

void NetworkManager::postRequest(QUrl url)
{
    init();

    request.setUrl(url);
    reply = networkManager->post(request, postData);

    connect(networkManager.data(), SIGNAL(finished(QNetworkReply*)), this, SLOT(slotPostFinished(QNetworkReply*)));
    connectErrorHandlers();
}

void NetworkManager::putRequest(const QString &url, const QByteArray &data)
{
    request.setUrl(QUrl(url));

    reply = networkManager->put(request, data);

    connect(reply, SIGNAL(finished()), this, SLOT(slotUploadFinished()));
    connect(reply, SIGNAL(uploadProgress(qint64, qint64)), this, SLOT(slotUploadProgress(qint64, qint64)));

    connectErrorHandlers();
}

void NetworkManager::putRequest(QUrl url)
{
    init();

    request.setUrl(url);
    reply = networkManager->put(request, postData);

    connect(reply, SIGNAL(finished()), this, SLOT(slotPutFinished()));
    connectErrorHandlers();
}

void NetworkManager::deleteRequest(QUrl url)
{
    init();

    request.setUrl(url);
    reply = networkManager->deleteResource(request);

    connect(networkManager.data(), SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyFinished(QNetworkReply*)));
    connectErrorHandlers();
}


const NetworkManager* NetworkManager::self(void) const
{
    return this;
}

QNetworkRequest NetworkManager::getRequest(void) const
{
    return request;
}

void NetworkManager::postFinishedActions(QNetworkReply*) {}
void NetworkManager::slotReplyFinished(QNetworkReply*){}
void NetworkManager::slotPutFinished(void){}
