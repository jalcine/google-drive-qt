#include "sharedialog.h"
#include "ui_sharedialog.h"
#include <QUrl>
#include <QFile>

ShareDialog::ShareDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShareDialog)
{
    ui->setupUi(this);
}

ShareDialog::~ShareDialog()
{
    delete ui;
}
