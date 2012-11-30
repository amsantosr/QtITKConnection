#ifndef CONNECTEDTHRESHOLDSEGMENTATIONDIALOG_H
#define CONNECTEDTHRESHOLDSEGMENTATIONDIALOG_H

#include <QDialog>
#include <QPoint>
#include "imagelayer.h"
#include <itkCurvatureFlowImageFilter.h>
#include <itkConnectedThresholdImageFilter.h>
#include <itkCastImageFilter.h>

//class CustomScrollArea;
class CustomGraphicsScene;

namespace Ui {
    class ConnectedThresholdSegmentationDialog;
}

class ConnectedThresholdSegmentationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectedThresholdSegmentationDialog(QWidget *parent = 0);
    void setPickPointGraphicsScene(CustomGraphicsScene *graphicsScene);
    ~ConnectedThresholdSegmentationDialog();

private:
    Ui::ConnectedThresholdSegmentationDialog *ui;
    typedef itk::CurvatureFlowImageFilter<ImageLayer::FloatImageType, ImageLayer::FloatImageType> CurvatureFlowFilterType;
    typedef itk::ConnectedThresholdImageFilter<ImageLayer::FloatImageType, ImageLayer::FloatImageType> ConnectedThresholdFilterType;
    typedef itk::CastImageFilter<ImageLayer::FloatImageType, ImageLayer::GrayImageType> CastToIntFilterType;
    CurvatureFlowFilterType::Pointer curvatureFilter;
    ConnectedThresholdFilterType::Pointer connectedFilter;
    CastToIntFilterType::Pointer castToIntFilter;

private slots:
    void on_pushButtonApply_clicked();
    void updateSeedPoint(QPoint point);
};

#endif // CONNECTEDTHRESHOLDSEGMENTATIONDIALOG_H
