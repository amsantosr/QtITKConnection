#include "derivativeimagefilterdialog.h"
#include "ui_derivativeimagefilterdialog.h"
#include "imagelayer.h"

DerivativeImageFilterDialog::DerivativeImageFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DerivativeImageFilterDialog)
{
    ui->setupUi(this);
    derivativeFilter = DerivativeImageFilterType::New();
    castToIntFilter = CastToIntFilterType::New();
}

DerivativeImageFilterDialog::~DerivativeImageFilterDialog()
{
    delete ui;
}

void DerivativeImageFilterDialog::on_pushButtonApply_clicked()
{
    ImageLayer *imageLayer = ImageLayer::instance();
    int order = ui->lineEditOrder->text().toInt();
    int direction = ui->lineEditDirection->text().toInt();

    derivativeFilter->SetInput(imageLayer->floatGrayImagePointer(0));
    derivativeFilter->SetOrder(order);
    derivativeFilter->SetDirection(direction);
    castToIntFilter->SetInput(derivativeFilter->GetOutput());
    castToIntFilter->Update();

    imageLayer->resizeImageVector(2);
    imageLayer->setGrayImage(1, castToIntFilter->GetOutput());
}
