#ifndef SIGMOIDFILTERDIALOG_H
#define SIGMOIDFILTERDIALOG_H

#include <QDialog>
#include "imagelayer.h"
#include <itkSigmoidImageFilter.h>

namespace Ui {
    class SigmoidFilterDialog;
}

class SigmoidFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SigmoidFilterDialog(QWidget *parent = 0);
    ~SigmoidFilterDialog();

private:
    Ui::SigmoidFilterDialog *ui;
    typedef itk::SigmoidImageFilter<ImageLayer::GrayImageType, ImageLayer::GrayImageType> SigmoidFilterType;
    SigmoidFilterType::Pointer sigmoidFilter;
private slots:
    void on_pushButtonApply_clicked();
};

#endif // SIGMOIDFILTERDIALOG_H
