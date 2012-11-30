#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QRgb>

namespace Ui {
    class MainWindow;
}

QT_BEGIN_NAMESPACE
class QScrollArea;
class QLabel;
class QTabWidget;
QT_END_NAMESPACE

//class CustomScrollArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    //CustomScrollArea *appendNewTab();
    void appendNewTab();
    void initializeImageColorTable();

private:
    Ui::MainWindow *ui;
    QTabWidget *m_tabWidget;
    QVector<QRgb> m_colorTable;

private slots:
    void setNumberOfTabs(int numTabs);
    void updateGrayImageTab(int index);
    void on_actionNeighborhoodConnectedSegmentation_triggered();
    void on_actionOtsuThresholdSegmentation_triggered();
    void on_actionConfidenceConnectedSegmentation_triggered();
    void on_actionConnectedThresholdSegmentation_triggered();
    void on_actionGradientAnisotropicDifussionFilter_triggered();
    void on_actionDerivativeFilter_triggered();
    void on_actionSigmoidFilter_triggered();
    void on_actionNormalizeFilter_triggered();
    void on_actionRescaleIntensityFilter_triggered();
    void on_actionCannyEdgeDetectionFilter_triggered();
    void on_actionGeneralThresholdFilter_triggered();
    void on_actionBinaryThresholdFilter_triggered();
    void on_actionOpenImage_triggered();
    void on_actionIsolatedConnected_triggered();
    void on_actionWatershedSegmentation_triggered();
    void on_actionFastMarchingSegmentation_triggered();
};

#endif // MAINWINDOW_H
