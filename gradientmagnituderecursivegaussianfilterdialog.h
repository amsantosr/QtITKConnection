#ifndef GRADIENTMAGNITUDERECURSIVEGAUSSIANFILTERDIALOG_H
#define GRADIENTMAGNITUDERECURSIVEGAUSSIANFILTERDIALOG_H

#include <QDialog>
#include "imagelayer.h"
#include <itkGradientMagnitudeRecursiveGaussianImageFilter.h>
#include <itkCastImageFilter.h>

namespace Ui {
    class GradientMagnitudeRecursiveGaussianFilterDialog;
}

class GradientMagnitudeRecursiveGaussianFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GradientMagnitudeRecursiveGaussianFilterDialog(QWidget *parent = 0);
    ~GradientMagnitudeRecursiveGaussianFilterDialog();

private:
    Ui::GradientMagnitudeRecursiveGaussianFilterDialog *ui;
    typedef itk::GradientMagnitudeRecursiveGaussianImageFilter<ImageLayer::FloatImageType, ImageLayer::FloatImageType>
            GradientMagnitudeRecursiveGaussianFilterType;
    typedef itk::CastImageFilter<ImageLayer::FloatImageType, ImageLayer::GrayImageType> CastToIntFilterType;
    CastToIntFilterType::Pointer castToIntFilter;
    GradientMagnitudeRecursiveGaussianFilterType::Pointer gradientRecursiveFilter;

private slots:
    void on_pushButtonApply_clicked();
};

#endif // GRADIENTMAGNITUDERECURSIVEGAUSSIANFILTERDIALOG_H
