#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "core/driveengine.h"
#include "share/debug.h"
#include "settings/settingsmanager.h"
#include "gui/forms/authdialog.h"
#include "network/operations/operationsmanager.h"
#include <QTextCodec>
#include <QKeyEvent>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    auth(NULL)
{
    SUi::inst()->setupUi(this);
}

MainWindow::~MainWindow()
{
    SDriveEngine::freeInst();
    SUi::freeInst();
    SOperationsManager::freeInst();
}

void MainWindow::init(void)
{
    SDriveEngine::inst(this)->init();
    SDriveEngine::inst()->getCheckUI()->slotCheckWorkDir(false);

    setConnections();

    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    if(!CheckUI().checkReg())
    {
        CommonTools::msg(tr("The application is under development. Currently disabled to use.\nNo commercial use allowed."));
        return;
    }
}

void MainWindow::setConnections(void)
{
    connect(SUi::inst()->actionLogin, SIGNAL(triggered()), this, SLOT(slotAuthDialog()));
    connect(SUi::inst()->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(SUi::inst()->actionDownload, SIGNAL(triggered()), SDriveEngine::inst()->getfilesTransferUI(), SLOT(slotDownload()));
    connect(SUi::inst()->actionUpload, SIGNAL(triggered()), SDriveEngine::inst()->getfilesTransferUI(), SLOT(slotUpload()));
    connect(SUi::inst()->actionSettings, SIGNAL(triggered()), SDriveEngine::inst()->getCheckUI(), SLOT(slotCheckWorkDir()));   
    connect(SUi::inst()->actionDelete, SIGNAL(triggered()), SOperationsManager::inst(), SLOT(slotDeleteItem()));
    connect(SUi::inst()->actionNewFolder, SIGNAL(triggered()), SOperationsManager::inst(), SLOT(slotNewFolder()));
    connect(SUi::inst()->copyButton, SIGNAL(clicked()), SOperationsManager::inst(), SLOT(slotCopyFile()));
    connect(SUi::inst()->moveButton, SIGNAL(clicked()), SOperationsManager::inst(), SLOT(slotMoveFile()));
    connect(SUi::inst()->newFolderButton, SIGNAL(clicked()), SOperationsManager::inst(), SLOT(slotNewFolder()));
    connect(SUi::inst()->deleteButton, SIGNAL(clicked()), SOperationsManager::inst(), SLOT(slotDeleteItem()));
    connect(SUi::inst()->renameButton, SIGNAL(clicked()), SOperationsManager::inst(), SLOT(slotRenameItem()));
    connect(SUi::inst()->shareButton, SIGNAL(clicked()), SOperationsManager::inst(), SLOT(slotShareFile()));
    connect(SDriveEngine::inst()->getFilePanel(ELeft)->getFileView(), SIGNAL(clicked(const QModelIndex&)), SDriveEngine::inst()->getfilesUI(), SLOT(slotLeftViewClicked(const QModelIndex&)));
    connect(SDriveEngine::inst()->getFilePanel(ERight)->getFileView(), SIGNAL(clicked(const QModelIndex&)), SDriveEngine::inst()->getfilesUI(), SLOT(slotRightViewClicked(const QModelIndex&)));
    connect(SDriveEngine::inst()->getFilePanel(ELeft)->getFileView(), SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), SDriveEngine::inst()->getfilesUI(), SLOT(slotLeftPanelItemDoubleClicked(QTreeWidgetItem*, int)));
    connect(SDriveEngine::inst()->getFilePanel(ERight)->getFileView(), SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), SDriveEngine::inst()->getfilesUI(), SLOT(slotRightPanelItemDoubleClicked(QTreeWidgetItem*, int)));
    connect(SDriveEngine::inst()->getContentMngr()->self(), SIGNAL(signalAccessTokenRequired()), this, SLOT(slotAccessTokenRequired()));
    connect(SDriveEngine::inst()->getContentMngr(true)->self(), SIGNAL(signalAccessTokenRequired()), this, SLOT(slotAccessTokenRequired()));
    connect(SDriveEngine::inst()->getContentMngr(), SIGNAL(signalFirstPanelIsLoaded()), SDriveEngine::inst(), SLOT(slotFirstPanelIsLoaded()));
    connect(SOperationsManager::inst(), SIGNAL(signalAccountInfoReadyToUse()), this, SLOT(slotAccountInfoReadyToUse()));
}

void MainWindow::slotAuthDialog(void)
{
    AuthDialog authDialog(SUi::inst()->centralWidget);    
    connect(&authDialog, SIGNAL(signalTokens(const QString&, const QString&)), this, SLOT(slotTokens(const QString&, const QString&)));
    authDialog.exec();
}

void MainWindow::slotTokens(const QString &accessToken, const QString &refreshToken)
{
    SOperationsManager::inst()->setAccountInfo(accessToken, refreshToken);
}

void MainWindow::slotAccountInfoReadyToUse(void)
{
    SDriveEngine::inst()->updatePanel(LEFT_PANEL_VALUE, true);
}

void MainWindow::slotAccessTokenRequired(void)
{
    SettingsManager settingsManager;

    if(auth) delete auth;
    auth = new Auth;

    auth->getAccessToken(settingsManager.clientId(), settingsManager.clientSecret(), settingsManager.refreshToken());
    connect(auth, SIGNAL(signalAuthResponse(const QString&)), this, SLOT(slotAuthResponse(const QString&)));
}

void MainWindow::slotAuthResponse(const QString &accessToken)
{
    SOperationsManager::inst()->setAccountInfo(accessToken);

    auth->deleteLater();
    auth = NULL;
}


