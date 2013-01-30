#ifndef SHAREDIALOG_H
#define SHAREDIALOG_H

#include <QDialog>

namespace Ui {
class ShareDialog;
}

class ShareDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ShareDialog(QWidget *parent = 0);
    ~ShareDialog();
    
private:
    Ui::ShareDialog *ui;
};

#endif // SHAREDIALOG_H
