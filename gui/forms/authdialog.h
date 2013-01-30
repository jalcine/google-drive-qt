#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>
#include "network/auth.h"

namespace Ui {
class AuthDialog;
}

class AuthDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AuthDialog(QWidget *parent = 0);
    ~AuthDialog();

signals:
    void signalTokens(const QString &accessToken, const QString &refreshToken);

private slots:
    void slotUrlChanged(const QUrl& url);
    void slotAuthResponse(const QString &accessToken, const QString &refreshToken);

private:
    void init(void);
    
private:
    Ui::AuthDialog *ui;
    QScopedPointer<Auth> auth;
};

#endif // AUTHDIALOG_H
