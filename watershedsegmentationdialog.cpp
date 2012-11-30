#include "watershedsegmentationdialog.h"
#include "ui_watershedsegmentationdialog.h"
#include <QDoubleValidator>

WatershedSegmentationDialog::WatershedSegmentationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WatershedSegmentationDialog)
{
    ui->setupUi(this);

    ui->spinBoxDiffusionIterations->setValue(10);
    ui->lineEditDiffusionConductance->setText("2.0");
    ui->lineEditDiffusionConductance->setValidator(new QDoubleValidator(this));
    ui->lineEditDiffusionTimeStep->setText("0.125");
    ui->lineEditDiffusionTimeStep->setValidator(new QDoubleValidator(this));
    ui->doubleSpinBoxWatershedLevel->setValue(0.10);
    ui->doubleSpinBoxWatershedThreshold->setValue(0.001);

    diffusionFilter = DiffusionFilterType::New();
    gradientFilter = GradientFilterType::New();
    watershedFilter = WatershedFilterType::New();
    colorMapper = ColorMapFilterType::New();
    castToIntFilter = CastToIntFilterType::New();
}

WatershedSegmentationDialog::~WatershedSegmentationDialog()
{
    delete ui;
}

void WatershedSegmentationDialog::on_pushButtonApply_clicked()
{
    ImageLayer *imageLayer = ImageLayer::instance();
    int diffusionIterations = ui->spinBoxDiffusionIterations->value();
    float diffusionConductance = ui->lineEditDiffusionConductance->text().toFloat();
    float diffusionTimeStep = ui->lineEditDiffusionTimeStep->text().toFloat();
    double watershedLevel = ui->doubleSpinBoxWatershedLevel->value();
    double watershedThreshold = ui->doubleSpinBoxWatershedThreshold->value();

    imageLayer->resizeImageVector(4);
    diffusionFilter->SetInput(imageLayer->floatGrayImagePointer(0));
    diffusionFilter->SetNumberOfIterations(diffusionIterations);
    diffusionFilter->SetConductanceParameter(diffusionConductance);
    diffusionFilter->SetTimeStep(diffusionTimeStep);
    castToIntFilter->SetInput(diffusionFilter->GetOutput());
    castToIntFilter->Update();
    imageLayer->setGrayImage(1, castToIntFilter->GetOutput());

    gradientFilter->SetInput(diffusionFilter->GetOutput());
    castToIntFilter->SetInput(gradientFilter->GetOutput());
    castToIntFilter->Update();
    imageLayer->setGrayImage(2, castToIntFilter->GetOutput());

    watershedFilter->SetInput(gradientFilter->GetOutput());
    watershedFilter->SetLevel(watershedLevel);
    watershedFilter->SetThreshold(watershedThreshold);
    colorMapper->SetInput(watershedFilter->GetOutput());
    colorMapper->Update();
    imageLayer->setRgbImage(3, colorMapper->GetOutput());
}
