#ifndef WATERSHEDSEGMENTATIONDIALOG_H
#define WATERSHEDSEGMENTATIONDIALOG_H

#include <QDialog>
#include "imagelayer.h"
#include <itkGradientAnisotropicDiffusionImageFilter.h>
#include <itkGradientMagnitudeImageFilter.h>
#include <itkWatershedImageFilter.h>
#include <itkCastImageFilter.h>
#include <itkUnaryFunctorImageFilter.h>
#include <itkScalarToRGBPixelFunctor.h>

namespace Ui {
    class WatershedSegmentationDialog;
}

class WatershedSegmentationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WatershedSegmentationDialog(QWidget *parent = 0);
    ~WatershedSegmentationDialog();

private slots:
    void on_pushButtonApply_clicked();

private:
    typedef itk::Image<unsigned long, 2> LabeledImageType;
    typedef itk::GradientAnisotropicDiffusionImageFilter<ImageLayer::FloatImageType, ImageLayer::FloatImageType> DiffusionFilterType;
    typedef itk::GradientMagnitudeImageFilter<ImageLayer::FloatImageType, ImageLayer::FloatImageType> GradientFilterType;
    typedef itk::WatershedImageFilter<ImageLayer::FloatImageType> WatershedFilterType;
    typedef itk::Functor::ScalarToRGBPixelFunctor<unsigned long> ColorMapFunctorType;
    typedef itk::UnaryFunctorImageFilter<LabeledImageType, ImageLayer::RGBImageType, ColorMapFunctorType> ColorMapFilterType;
    typedef itk::CastImageFilter<ImageLayer::FloatImageType, ImageLayer::GrayImageType> CastToIntFilterType;

    Ui::WatershedSegmentationDialog *ui;
    DiffusionFilterType::Pointer diffusionFilter;
    GradientFilterType::Pointer gradientFilter;
    WatershedFilterType::Pointer watershedFilter;
    ColorMapFilterType::Pointer colorMapper;
    CastToIntFilterType::Pointer castToIntFilter;
};

#endif // WATERSHEDSEGMENTATIONDIALOG_H
