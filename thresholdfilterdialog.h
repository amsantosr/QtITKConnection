#ifndef THRESHOLDFILTERDIALOG_H
#define THRESHOLDFILTERDIALOG_H

#include <QDialog>
#include <itkThresholdImageFilter.h>
#include "imagelayer.h"

namespace Ui {
    class ThresholdFilterDialog;
}

class ThresholdFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThresholdFilterDialog(QWidget *parent = 0);
    ~ThresholdFilterDialog();

private:
    Ui::ThresholdFilterDialog *ui;
    typedef itk::ThresholdImageFilter<ImageLayer::GrayImageType> ThresholdFilterType;
    ThresholdFilterType::Pointer thresholdFilter;

private slots:
    void on_pushButtonApply_clicked();
    void updateActiveControls();
};

#endif // THRESHOLDFILTERDIALOG_H
