#ifndef CANNYEDGEDETECTIONFILTERDIALOG_H
#define CANNYEDGEDETECTIONFILTERDIALOG_H

#include <QDialog>
#include <itkCannyEdgeDetectionImageFilter.h>
#include <itkRescaleIntensityImageFilter.h>
#include "imagelayer.h"

namespace Ui {
    class CannyEdgeDetectionFilterDialog;
}

class CannyEdgeDetectionFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CannyEdgeDetectionFilterDialog(QWidget *parent = 0);
    ~CannyEdgeDetectionFilterDialog();

private:
    Ui::CannyEdgeDetectionFilterDialog *ui;
    typedef itk::CannyEdgeDetectionImageFilter<ImageLayer::FloatImageType, ImageLayer::FloatImageType> CannyFilterType;
    typedef itk::RescaleIntensityImageFilter<ImageLayer::FloatImageType, ImageLayer::GrayImageType> RescaleFilterType;

    CannyFilterType::Pointer cannyFilter;
    RescaleFilterType::Pointer rescaleFilter;

private slots:
    void on_pushButtonApply_clicked();
};

#endif // CANNYEDGEDETECTIONFILTERDIALOG_H
