#include "createfolderdialog.h"
#include "ui_createfolderdialog.h"

CreateFolderDialog::CreateFolderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateFolderDialog)
{
    ui->setupUi(this);
    ui->nameEdit->setFocus();

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(slotAccept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(slotReject()));
    connect(this, SIGNAL(finished(int)), this, SLOT(slotFinished(int)));
}

CreateFolderDialog::~CreateFolderDialog()
{
    delete ui;
}

void CreateFolderDialog::slotAccept()
{
    emit signalAccept(ui->nameEdit->text());
}

void CreateFolderDialog::slotReject()
{
    emit signalReject();
}

void CreateFolderDialog::slotFinished(int result)
{
    emit signalFinished(result);
}

void CreateFolderDialog::setNameLabel(const QString &text)
{
    return ui->nameLabel->setText(text);
}
