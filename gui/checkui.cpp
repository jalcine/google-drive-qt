#include "checkui.h"
#include "settings/settingsmanager.h"
#include <QMessageBox>
#include "gui/forms/settingsdialog.h"
#include "share/defs.h"
#include "gui/forms/mainwindow.h"
#include "ui_mainwindow.h"
#include "core/driveengine.h"

CheckUI::CheckUI(QObject *parent) :
    QObject(parent)
{
}

bool CheckUI::checkReg(void)
{
    return false;
}

bool CheckUI::slotCheckWorkDir(bool showDlg)
{   
    SettingsManager settingsManager;

    if(settingsManager.isWorkDirSet() && !showDlg)
    {
        return true;
    }

    bool dirTextNotEmpty = false;

    if(showDlg)
    {
        SettingsDialog dlg(SDriveEngine::inst()->getParent());

        dlg.setDirectoryPath(settingsManager.workDir());

        switch(dlg.exec())
        {
        case QDialog::Accepted:
        {
            if(!dlg.directoryPath().isEmpty() )
            {
                settingsManager.setWorkDir(dlg.directoryPath());
                dirTextNotEmpty = true;
            }

        }
            break;
        }
    }

    return dirTextNotEmpty;
}
