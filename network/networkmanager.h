#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QSslError>
#include "gui/forms/progressbardialog.h"
#include <QFileInfo>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    enum EStates
    {
        EReady,
        EBusy
    };

    explicit NetworkManager(QObject *parent = 0);
    virtual ~NetworkManager();
    
signals:
    void signalAccessTokenRequired();

protected slots:
    virtual void slotPostFinished(QNetworkReply* reply);
    virtual void slotPutFinished(void);
    virtual void slotError(QNetworkReply::NetworkError error);
    virtual void slotSslErrors(const QList<QSslError> &errors);
    virtual void slotReplyFinished(QNetworkReply*);
    virtual void slotReplyReadyRead();
    virtual void slotProgressCanceled();

public:
    void init(void);
    QNetworkAccessManager *getNetworkManager(void) const;
    QNetworkRequest getRequest(void) const;
    void getRequest(const QString &url);
    void postRequest(QUrl url);
    void putRequest(QUrl url);
    void putRequest(const QString &url,const QByteArray &postData);
    EStates getState(void) const;
    void setState(EStates currentState);
    const NetworkManager* self(void) const;
    void connectErrorHandlers(void);
    void deleteRequest(QUrl url);

protected:
    virtual void postFinishedActions(QNetworkReply*);
    virtual void setProgressBarSettings(const QString &fileName, const QString &progressBarDialogInfoText);

protected:
    QObject* parent;
    QScopedPointer <QNetworkAccessManager> networkManager;
    QNetworkReply *reply;
    QNetworkRequest request;
    QByteArray postData;
    EStates state;
    QFile file;
    QString fileType;
    ProgressBarDialog progressBarDialog;
    bool operationCanceled;
    QString replyStr;
};

#endif // NETWORKMANAGER_H



