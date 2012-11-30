#ifndef RESCALEINTENSITYFILTERDIALOG_H
#define RESCALEINTENSITYFILTERDIALOG_H

#include <QDialog>
#include "imagelayer.h"
#include <itkRescaleIntensityImageFilter.h>

namespace Ui {
    class RescaleIntensityFilterDialog;
}

class RescaleIntensityFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RescaleIntensityFilterDialog(QWidget *parent = 0);
    ~RescaleIntensityFilterDialog();

private:
    Ui::RescaleIntensityFilterDialog *ui;
    typedef itk::RescaleIntensityImageFilter<ImageLayer::GrayImageType, ImageLayer::GrayImageType> RescaleFilterType;
    RescaleFilterType::Pointer rescaleFilter;

private slots:
    void on_pushButtonApply_clicked();
};

#endif // RESCALEINTENSITYFILTERDIALOG_H
