#include "gradientmagnituderecursivegaussianfilterdialog.h"
#include "ui_gradientmagnituderecursivegaussianfilterdialog.h"
#include "imagelayer.h"

GradientMagnitudeRecursiveGaussianFilterDialog::GradientMagnitudeRecursiveGaussianFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GradientMagnitudeRecursiveGaussianFilterDialog)
{
    ui->setupUi(this);
    castToIntFilter = CastToIntFilterType::New();
    gradientRecursiveFilter = GradientMagnitudeRecursiveGaussianFilterType::New();
}

GradientMagnitudeRecursiveGaussianFilterDialog::~GradientMagnitudeRecursiveGaussianFilterDialog()
{
    delete ui;
}

void GradientMagnitudeRecursiveGaussianFilterDialog::on_pushButtonApply_clicked()
{
    ImageLayer *imageLayer = ImageLayer::instance();
    float sigma = ui->lineEditSigma->text().toInt();

    gradientRecursiveFilter->SetInput(imageLayer->floatGrayImagePointer(0));
    gradientRecursiveFilter->SetSigma(sigma);
    castToIntFilter->SetInput(gradientRecursiveFilter->GetOutput());
    castToIntFilter->Update();

    imageLayer->resizeImageVector(2);
    imageLayer->setGrayImage(1, castToIntFilter->GetOutput());
}
