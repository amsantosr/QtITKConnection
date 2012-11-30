#ifndef FASTMARCHINGSEGMENTATIONDIALOG_H
#define FASTMARCHINGSEGMENTATIONDIALOG_H

#include <QDialog>
#include <QPoint>
#include "imagelayer.h"
#include <itkCurvatureAnisotropicDiffusionImageFilter.h>
#include <itkGradientMagnitudeRecursiveGaussianImageFilter.h>
#include <itkSigmoidImageFilter.h>
#include <itkFastMarchingImageFilter.h>
#include <itkBinaryThresholdImageFilter.h>
#include <itkRescaleIntensityImageFilter.h>
#include <itkCastImageFilter.h>

namespace Ui {
    class FastMarchingSegmentationDialog;
}

class CustomGraphicsScene;

class FastMarchingSegmentationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FastMarchingSegmentationDialog(QWidget *parent = 0);
    ~FastMarchingSegmentationDialog();
    void setPickPointGraphicsScene(CustomGraphicsScene *graphicsScene);

private:
    typedef itk::BinaryThresholdImageFilter<ImageLayer::FloatImageType, ImageLayer::GrayImageType> ThresholdingFilterType;
    typedef itk::RescaleIntensityImageFilter<ImageLayer::FloatImageType, ImageLayer::GrayImageType> RescaleFilterType;
    typedef itk::CurvatureAnisotropicDiffusionImageFilter<ImageLayer::FloatImageType, ImageLayer::FloatImageType> CurvatureFilterType;
    typedef itk::GradientMagnitudeRecursiveGaussianImageFilter<ImageLayer::FloatImageType, ImageLayer::FloatImageType> GradientFilterType;
    typedef itk::SigmoidImageFilter<ImageLayer::FloatImageType, ImageLayer::FloatImageType> SigmoidFilterType;
    typedef itk::FastMarchingImageFilter<ImageLayer::FloatImageType, ImageLayer::FloatImageType> FastMarchingFilterType;
    typedef itk::CastImageFilter<ImageLayer::FloatImageType, ImageLayer::GrayImageType> CastToIntFilterType;

    Ui::FastMarchingSegmentationDialog *ui;
    CustomGraphicsScene *graphicsScene;
    ThresholdingFilterType::Pointer thresholdFilter;
    RescaleFilterType::Pointer rescaleFilter;
    CurvatureFilterType::Pointer curvatureFilter;
    GradientFilterType::Pointer gradientFilter;
    SigmoidFilterType::Pointer sigmoidFilter;
    FastMarchingFilterType::Pointer fastMarchingFilter;
    CastToIntFilterType::Pointer castToIntPointer;

private slots:
    void addPoint(QPoint point);
    void on_pushButtonApply_clicked();
    void on_pushButtonRemove_clicked();
};

#endif // FASTMARCHINGSEGMENTATIONDIALOG_H
