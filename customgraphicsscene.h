#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QPoint>

class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomGraphicsScene(QObject *parent = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    bool pickEnabled;

signals:
    void pointPicked(QPoint point);

public slots:
    void enablePick(bool enable);
};

#endif // CUSTOMGRAPHICSSCENE_H
