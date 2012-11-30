#include "thresholdfilterdialog.h"
#include "ui_thresholdfilterdialog.h"
#include "imagelayer.h"
//#include <itkThresholdImageFilter.h>

ThresholdFilterDialog::ThresholdFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThresholdFilterDialog)
{
    ui->setupUi(this);

    connect(ui->radioButtonThresholdBelow, SIGNAL(toggled(bool)), this, SLOT(updateActiveControls()));
    connect(ui->radioButtonThresholdAbove, SIGNAL(toggled(bool)), this, SLOT(updateActiveControls()));
    connect(ui->radioButtonThresholdOutside, SIGNAL(toggled(bool)), this, SLOT(updateActiveControls()));

    ui->radioButtonThresholdBelow->setChecked(true);

    thresholdFilter = ThresholdFilterType::New();
}

ThresholdFilterDialog::~ThresholdFilterDialog()
{
    delete ui;
}

void ThresholdFilterDialog::updateActiveControls()
{
    bool outside = ui->radioButtonThresholdOutside->isChecked();

    ui->spinBoxThreshold->setEnabled(!outside);
    ui->spinBoxLowerThreshold->setEnabled(outside);
    ui->spinBoxUpperThreshold->setEnabled(outside);
    ui->horizontalSliderThreshold->setEnabled(!outside);
    ui->horizontalSliderLowerThreshold->setEnabled(outside);
    ui->horizontalSliderUpperThreshold->setEnabled(outside);
}

void ThresholdFilterDialog::on_pushButtonApply_clicked()
{
    ImageLayer *imageLayer = ImageLayer::instance();
    int outsideValue = ui->spinBoxOutsideValue->value();
    int threshold = ui->spinBoxThreshold->value();
    int lowerThreshold = ui->spinBoxLowerThreshold->value();
    int upperThreshold = ui->spinBoxUpperThreshold->value();
    thresholdFilter->SetInput(imageLayer->grayImagePointer(0));

    if (ui->radioButtonThresholdBelow->isChecked()) {
        thresholdFilter->SetOutsideValue(outsideValue);
        thresholdFilter->ThresholdBelow(threshold);
    } else if (ui->radioButtonThresholdAbove->isChecked()){
        thresholdFilter->SetOutsideValue(outsideValue);
        thresholdFilter->ThresholdAbove(threshold);
    } else {
        thresholdFilter->SetOutsideValue(outsideValue);
        thresholdFilter->ThresholdOutside(lowerThreshold, upperThreshold);
    }
    thresholdFilter->Update();
    imageLayer->resizeImageVector(2);
    imageLayer->setGrayImage(1, thresholdFilter->GetOutput());
}
