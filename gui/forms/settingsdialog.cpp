#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QFileDialog>
#include <QDir>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(browseDir()));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::browseDir()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Set Directory"), ui->directoryLineEdit->text());

    if(dir.isEmpty())
    {
        return;
    }

    ui->directoryLineEdit->setText(dir);
}

QString SettingsDialog::directoryPath() const
{
    return QDir::toNativeSeparators(ui->directoryLineEdit->text());
}

void SettingsDialog::setDirectoryPath(const QString &dir)
{
    ui->directoryLineEdit->setText(QDir::toNativeSeparators(dir));
}
