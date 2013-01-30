#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "share/singleton.h"
#include "network/queries.h"
#include "network/auth.h"

namespace Ui
{
class MainWindow;
}

class DriveEngine;

typedef TSingleton<Ui::MainWindow> SUi;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void init(void);

private:
    void setConnections(void);

private slots:
    void slotAccessTokenRequired(void);
    void slotAccountInfoReadyToUse(void);
    void slotAuthDialog(void);
    void slotAuthResponse(const QString &accessToken);
    void slotTokens(const QString &accessToken, const QString &refreshToken);

private:
    Auth *auth;
};

#endif // MAINWINDOW_H
