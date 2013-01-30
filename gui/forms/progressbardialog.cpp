#include "progressbardialog.h"
#include "ui_progressbardialog.h"

ProgressBarDialog::ProgressBarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::progressBarDialog)
{
    ui->setupUi(this);
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(slotCancel()));
}

ProgressBarDialog::~ProgressBarDialog()
{
    delete ui;
}

void ProgressBarDialog::slotCancel()
{
    hide();
    emit signalProgressCanceled();
}

void ProgressBarDialog::setMaximum(qint64 max)
{
 ui->progressBar->setMaximum(max);
}

void ProgressBarDialog::setValue(qint64 val)
{
  ui->progressBar->setValue(val);
}

void ProgressBarDialog::setText(const QString& text)
{
  ui->infoLbel->setText(text);
}
