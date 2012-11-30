#ifndef GRADIENTANISOTROPICFILTERDIALOG_H
#define GRADIENTANISOTROPICFILTERDIALOG_H

#include <QDialog>
#include "imagelayer.h"
#include <itkGradientAnisotropicDiffusionImageFilter.h>
#include <itkRescaleIntensityImageFilter.h>

namespace Ui {
    class GradientAnisotropicFilterDialog;
}

class GradientAnisotropicFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GradientAnisotropicFilterDialog(QWidget *parent = 0);
    ~GradientAnisotropicFilterDialog();

private:
    Ui::GradientAnisotropicFilterDialog *ui;
    typedef itk::RescaleIntensityImageFilter<ImageLayer::FloatImageType, ImageLayer::GrayImageType> RescaleIntensityFilterType;
    typedef itk::GradientAnisotropicDiffusionImageFilter<ImageLayer::FloatImageType, ImageLayer::FloatImageType> GradientAnisotropicFilterType;
    RescaleIntensityFilterType::Pointer rescaleFilter;
    GradientAnisotropicFilterType::Pointer gradientAnisotropicFilter;

private slots:
    void on_pushButtonApply_clicked();
};

#endif // GRADIENTANISOTROPICFILTERDIALOG_H
