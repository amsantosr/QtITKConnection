#include "imagelayer.h"
#include "itkBinaryThresholdImageFilter.h"
#include "binarythresholdfilterdialog.h"
#include "ui_binarythresholdfilterdialog.h"

BinaryThresholdFilterDialog::BinaryThresholdFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BinaryThresholdFilterDialog)
{
    ui->setupUi(this);
}

BinaryThresholdFilterDialog::~BinaryThresholdFilterDialog()
{
    delete ui;
}

void BinaryThresholdFilterDialog::on_pushButtonApply_clicked()
{
    ImageLayer *imageLayer = ImageLayer::instance();
    int insideValue = ui->spinBoxInsideValue->value();
    int outsideValue = ui->spinBoxOutsideValue->value();
    int lowerThreshold = ui->spinBoxLowerThreshold->value();
    int upperThreshold = ui->spinBoxUpperThreshold->value();
    imageLayer->resizeImageVector(2);

    typedef itk::BinaryThresholdImageFilter<ImageLayer::GrayImageType, ImageLayer::GrayImageType> BinaryThresholdFilterType;

    BinaryThresholdFilterType::Pointer binaryThresholdFilter = BinaryThresholdFilterType::New();
    binaryThresholdFilter->SetInsideValue(insideValue);
    binaryThresholdFilter->SetOutsideValue(outsideValue);
    binaryThresholdFilter->SetLowerThreshold(lowerThreshold);
    binaryThresholdFilter->SetUpperThreshold(upperThreshold);
    binaryThresholdFilter->SetInput(imageLayer->grayImagePointer(0));
    binaryThresholdFilter->Update();

    imageLayer->setGrayImage(1, binaryThresholdFilter->GetOutput());
}
