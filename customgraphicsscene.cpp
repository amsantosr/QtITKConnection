#include "customgraphicsscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>

CustomGraphicsScene::CustomGraphicsScene(QObject *parent) :
    QGraphicsScene(parent), pickEnabled(false)
{
}

void CustomGraphicsScene::enablePick(bool enable)
{
    if (pickEnabled != enable) {
        pickEnabled = enable;
        if (pickEnabled) {
            this->views().first()->viewport()->setCursor(Qt::CrossCursor);
        } else {
            this->views().first()->viewport()->unsetCursor();
        }
    }
}

void CustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (pickEnabled) {
        emit pointPicked(QPoint(event->scenePos().x(), event->scenePos().y()));
    } else {
        QGraphicsScene::mousePressEvent(event);
    }
}
