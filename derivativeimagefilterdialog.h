#ifndef DERIVATIVEIMAGEFILTERDIALOG_H
#define DERIVATIVEIMAGEFILTERDIALOG_H

#include <QDialog>
#include "imagelayer.h"
#include <itkDerivativeImageFilter.h>
#include <itkCastImageFilter.h>

namespace Ui {
    class DerivativeImageFilterDialog;
}

class DerivativeImageFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DerivativeImageFilterDialog(QWidget *parent = 0);
    ~DerivativeImageFilterDialog();

private:
    Ui::DerivativeImageFilterDialog *ui;
    typedef itk::DerivativeImageFilter<ImageLayer::FloatImageType, ImageLayer::FloatImageType> DerivativeImageFilterType;
    typedef itk::CastImageFilter<ImageLayer::FloatImageType, ImageLayer::GrayImageType> CastToIntFilterType;
    DerivativeImageFilterType::Pointer derivativeFilter;
    CastToIntFilterType::Pointer castToIntFilter;

private slots:
    void on_pushButtonApply_clicked();
};

#endif // DERIVATIVEIMAGEFILTERDIALOG_H
