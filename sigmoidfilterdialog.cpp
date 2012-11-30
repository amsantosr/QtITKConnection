#include "sigmoidfilterdialog.h"
#include "ui_sigmoidfilterdialog.h"
#include "imagelayer.h"

SigmoidFilterDialog::SigmoidFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SigmoidFilterDialog)
{
    ui->setupUi(this);
    sigmoidFilter = SigmoidFilterType::New();
}

SigmoidFilterDialog::~SigmoidFilterDialog()
{
    delete ui;
}

void SigmoidFilterDialog::on_pushButtonApply_clicked()
{
    ImageLayer *imageLayer = ImageLayer::instance();
    int outputMinimum = ui->spinBoxMinimum->value();
    int outputMaximum = ui->spinBoxMaximum->value();
    double alpha = ui->spinBoxAlpha->value();
    double beta = ui->spinBoxBeta->value();

    sigmoidFilter->SetInput(imageLayer->grayImagePointer(0));
    sigmoidFilter->SetOutputMinimum(outputMinimum);
    sigmoidFilter->SetOutputMaximum(outputMaximum);
    sigmoidFilter->SetAlpha(alpha);
    sigmoidFilter->SetBeta(beta);
    sigmoidFilter->Update();

    imageLayer->resizeImageVector(2);
    imageLayer->setGrayImage(1, sigmoidFilter->GetOutput());
}
