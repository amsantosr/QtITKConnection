#ifndef CUSTOMSCROLLAREA_H
#define CUSTOMSCROLLAREA_H

#include <QScrollArea>
#include <QPoint>

class QMouseEvent;
class QLabel;

class CustomScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit CustomScrollArea(QWidget *parent = 0);
    QLabel *imageLabel();

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    bool pickEnabled;
    QLabel *m_imageLabel;

signals:
    void pointPicked(QPoint point);

public slots:
    void enablePick(bool enable);
};

inline QLabel *CustomScrollArea::imageLabel()
{
    return m_imageLabel;
}

#endif // CUSTOMSCROLLAREA_H
