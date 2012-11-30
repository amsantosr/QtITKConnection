#include "gradientanisotropicfilterdialog.h"
#include "ui_gradientanisotropicfilterdialog.h"
#include "imagelayer.h"

GradientAnisotropicFilterDialog::GradientAnisotropicFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GradientAnisotropicFilterDialog)
{
    ui->setupUi(this);
    ui->spinBoxIterations->setValue(2);
    ui->lineEditConductance->setText(tr("5.0"));
    ui->lineEditTimeStep->setText(tr("0.12"));
    rescaleFilter = RescaleIntensityFilterType::New();
    gradientAnisotropicFilter = GradientAnisotropicFilterType::New();
}

GradientAnisotropicFilterDialog::~GradientAnisotropicFilterDialog()
{
    delete ui;
}

void GradientAnisotropicFilterDialog::on_pushButtonApply_clicked()
{
    ImageLayer *imageLayer = ImageLayer::instance();
    int iterations = ui->spinBoxIterations->value();
    float timeStep = ui->lineEditTimeStep->text().toFloat();
    float conductance = ui->lineEditConductance->text().toFloat();

    imageLayer->resizeImageVector(2);
    gradientAnisotropicFilter->SetInput(imageLayer->floatGrayImagePointer(0));
    gradientAnisotropicFilter->SetNumberOfIterations(iterations);
    gradientAnisotropicFilter->SetTimeStep(timeStep);
    gradientAnisotropicFilter->SetConductanceParameter(conductance);
    rescaleFilter->SetInput(gradientAnisotropicFilter->GetOutput());
    rescaleFilter->SetOutputMinimum(0);
    rescaleFilter->SetOutputMaximum(255);
    rescaleFilter->Update();

    imageLayer->setGrayImage(1, rescaleFilter->GetOutput());
}
