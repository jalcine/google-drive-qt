#ifndef FILEPANEL_H
#define FILEPANEL_H

#include <QWidget>
#include <QTreeWidget>
#include <QLabel>
#include "gui/controls/toolbar.h"
#include "gui/controls/combobox.h"

namespace Ui {
class FilePanel;
}

class FilePanel : public QWidget
{
    Q_OBJECT

public:
    explicit FilePanel(int pn, QWidget *parent = 0);
    ~FilePanel();

signals:
    void signalAccountChanged(int panelNum, const QString& accountName);

private slots:
    void slotActivated(const QString& text);

public:
    QTreeWidget* getFileView(void) const;
    QLabel* getPathLabel(void) const;
    ToolBar* getAccountsToolBar(void) const;
    ComboBox* getAccountsComboBox(void) const;
    void fillComboBox(QMap<QString, QString> accountsMap, const QString &currentAccount);
    int getpanelNum(void) const;

private:
    void init(void);

private:
    Ui::FilePanel *ui;
    ToolBar *accountsToolBar;
    ComboBox *accountsComboBox;
    int panelNum;
};

#endif // FILEPANEL_H
