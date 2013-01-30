#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>

class ToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit ToolBar(QWidget *parent = 0, const QString &styleSheet = "", int height = 26);
    
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // TOOLBAR_H
