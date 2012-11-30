#include "otsuthresholdsegmentationdialog.h"
#include "ui_otsuthresholdsegmentationdialog.h"
#include "imagelayer.h"

OtsuThresholdSegmentationDialog::OtsuThresholdSegmentationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OtsuThresholdSegmentationDialog)
{
    ui->setupUi(this);
    ui->spinBoxInsideValue->setValue(255);
    ui->spinBoxOutsideValue->setValue(0);
    int index128 = ui->comboBoxHistogramBins->findText(tr("128"));
    ui->comboBoxHistogramBins->setCurrentIndex(index128);

    otsuFilter = OtsuThresholdFilterType::New();
}

OtsuThresholdSegmentationDialog::~OtsuThresholdSegmentationDialog()
{
    delete ui;
}

void OtsuThresholdSegmentationDialog::on_pushButtonApply_clicked()
{
    ImageLayer *imageLayer = ImageLayer::instance();
    int insideValue = ui->spinBoxInsideValue->value();
    int outsideValue = ui->spinBoxOutsideValue->value();
    int histogramBins = ui->comboBoxHistogramBins->currentText().toInt();

    imageLayer->resizeImageVector(2);
    otsuFilter->SetInput(imageLayer->grayImagePointer(0));
    otsuFilter->SetInsideValue(insideValue);
    otsuFilter->SetOutsideValue(outsideValue);
    otsuFilter->SetNumberOfHistogramBins(histogramBins);
    otsuFilter->Update();

    imageLayer->setGrayImage(1, otsuFilter->GetOutput());
}
