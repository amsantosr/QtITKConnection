#ifndef CONFIDENCECONNECTEDSEGMENTATIONDIALOG_H
#define CONFIDENCECONNECTEDSEGMENTATIONDIALOG_H

#include <QDialog>
#include <QPoint>
#include <itkIntensityWindowingImageFilter.h>
#include <itkCurvatureFlowImageFilter.h>
#include <itkConfidenceConnectedImageFilter.h>
#include <itkRescaleIntensityImageFilter.h>
#include <itkCastImageFilter.h>
#include "imagelayer.h"

//class CustomScrollArea;
class CustomGraphicsScene;

namespace Ui {
    class ConfidenceConnectedSegmentationDialog;
}

class ConfidenceConnectedSegmentationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfidenceConnectedSegmentationDialog(QWidget *parent = 0);
    ~ConfidenceConnectedSegmentationDialog();
    void setPickPointGraphicsScene(CustomGraphicsScene *graphicsScene);

private:
    Ui::ConfidenceConnectedSegmentationDialog *ui;
    typedef itk::IntensityWindowingImageFilter<ImageLayer::FloatImageType, ImageLayer::GrayImageType> WindowingFloatFilterType;
    typedef itk::CurvatureFlowImageFilter<ImageLayer::FloatImageType, ImageLayer::FloatImageType> CurvatureFlowFilterType;
    typedef itk::ConfidenceConnectedImageFilter<ImageLayer::FloatImageType, ImageLayer::FloatImageType> ConfidenceConnectedFilterType;
    //typedef itk::RescaleIntensityImageFilter<ImageLayer::FloatImageType, ImageLayer::ImageType> RescaleIntensityFilterType;
    typedef itk::CastImageFilter<ImageLayer::FloatImageType, ImageLayer::GrayImageType> CastToIntFilterType;
    WindowingFloatFilterType::Pointer windowingFilter;
    CurvatureFlowFilterType::Pointer curvatureFilter;
    ConfidenceConnectedFilterType::Pointer confidenceFilter;
    //RescaleIntensityFilterType::Pointer rescaleFilter;
    CastToIntFilterType::Pointer castToIntFilter;

private slots:
    void on_pushButtonApply_clicked();
    void updateSeedPoint(QPoint point);
};

#endif // CONFIDENCECONNECTEDSEGMENTATIONDIALOG_H
