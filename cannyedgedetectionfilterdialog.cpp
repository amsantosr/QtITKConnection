#include "cannyedgedetectionfilterdialog.h"
#include "ui_cannyedgedetectionfilterdialog.h"
#include "imagelayer.h"
#include <itkCannyEdgeDetectionImageFilter.h>
#include <itkRescaleIntensityImageFilter.h>

CannyEdgeDetectionFilterDialog::CannyEdgeDetectionFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CannyEdgeDetectionFilterDialog)
{
    ui->setupUi(this);
    cannyFilter = CannyFilterType::New();
    rescaleFilter = RescaleFilterType::New();
    rescaleFilter->SetOutputMinimum(0);
    rescaleFilter->SetOutputMaximum(255);

    ui->spinBoxUpperThreshold->setValue(30);
    ui->doubleSpinBoxVariance->setValue(2.0);
}

CannyEdgeDetectionFilterDialog::~CannyEdgeDetectionFilterDialog()
{
    delete ui;
}

void CannyEdgeDetectionFilterDialog::on_pushButtonApply_clicked()
{
    ImageLayer *imageLayer = ImageLayer::instance();
    int lowerThreshold = ui->spinBoxLowerThreshold->value();
    int upperThreshold = ui->spinBoxUpperThreshold->value();
    double variance = ui->doubleSpinBoxVariance->value();

    imageLayer->resizeImageVector(2);
    cannyFilter->SetInput(imageLayer->floatGrayImagePointer(0));
    cannyFilter->SetVariance(variance);
    cannyFilter->SetLowerThreshold(lowerThreshold);
    cannyFilter->SetUpperThreshold(upperThreshold);
    rescaleFilter->SetInput(cannyFilter->GetOutput());
    rescaleFilter->Update();

    imageLayer->setGrayImage(1, rescaleFilter->GetOutput());
}
