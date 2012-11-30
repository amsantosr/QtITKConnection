#include "customscrollarea.h"
#include <QMouseEvent>
#include <QLabel>

CustomScrollArea::CustomScrollArea(QWidget *parent) :
    QScrollArea(parent), pickEnabled(false)
{
    this->m_imageLabel = new QLabel(this);
}

void CustomScrollArea::enablePick(bool enable)
{
    if (pickEnabled != enable) {
        pickEnabled = enable;
        if (pickEnabled) {
            setCursor(Qt::CrossCursor);
        } else {
            unsetCursor();
        }
    }
}

void CustomScrollArea::mousePressEvent(QMouseEvent *event)
{
    if (pickEnabled) {
        emit pointPicked(event->pos());
    } else {
        QAbstractScrollArea::mousePressEvent(event);
    }
}
