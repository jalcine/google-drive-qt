#include "toolbar.h"
#include <QLayout>
#include <QStyleOption>
#include <QPainter>

ToolBar::ToolBar(QWidget *parent, const QString &styleSheet, int height) :
    QToolBar(parent)
{ 
    //setStyleSheet(styleSheet);
    setStyleSheet("QToolBar {background-color: qlineargradient(spread:pad, x1:1, y1:0.432, x2:1, y2:0, stop:0 rgba(72, 72, 72, 255), stop:1 rgba(154, 154, 154, 255));}");
    setFixedHeight(height);

    const int offset = 0;

    layout()->setContentsMargins(offset, offset, offset, offset);
}

void ToolBar::paintEvent(QPaintEvent *event)
{    
    Q_UNUSED(event);

    QStyleOption opt;
    QPainter p(this);

    opt.init(this);

    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
