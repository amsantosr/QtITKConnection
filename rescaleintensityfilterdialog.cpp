#include "rescaleintensityfilterdialog.h"
#include "ui_rescaleintensityfilterdialog.h"
#include "imagelayer.h"

RescaleIntensityFilterDialog::RescaleIntensityFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RescaleIntensityFilterDialog)
{
    ui->setupUi(this);
    rescaleFilter = RescaleFilterType::New();
}

RescaleIntensityFilterDialog::~RescaleIntensityFilterDialog()
{
    delete ui;
}

void RescaleIntensityFilterDialog::on_pushButtonApply_clicked()
{
    ImageLayer *imageLayer = ImageLayer::instance();
    int minimum = ui->spinBoxMinimum->value();
    int maximum = ui->spinBoxMaximum->value();

    rescaleFilter->SetInput(imageLayer->grayImagePointer(0));
    rescaleFilter->SetOutputMinimum(minimum);
    rescaleFilter->SetOutputMaximum(maximum);
    rescaleFilter->Update();

    imageLayer->resizeImageVector(2);
    imageLayer->setGrayImage(1, rescaleFilter->GetOutput());
}
