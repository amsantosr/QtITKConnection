#include "confidenceconnectedsegmentationdialog.h"
#include "ui_confidenceconnectedsegmentationdialog.h"
#include "imagelayer.h"
//#include "customscrollarea.h"
#include "customgraphicsscene.h"
#include <QTextStream>
#include <QIntValidator>

ConfidenceConnectedSegmentationDialog::ConfidenceConnectedSegmentationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfidenceConnectedSegmentationDialog)
{
    ui->setupUi(this);
    ui->lineEditMultiplier->setText(QString::number(2.5f));
    ui->lineEditTimeStep->setText(QString::number(0.125f));
    ui->spinBoxCurvatureIterations->setValue(5);
    ui->spinBoxNeighborhoodRadius->setValue(2);
    ui->spinBoxConfidenceIterations->setValue(1);

    windowingFilter = WindowingFloatFilterType::New();
    curvatureFilter = CurvatureFlowFilterType::New();
    confidenceFilter = ConfidenceConnectedFilterType::New();
}

ConfidenceConnectedSegmentationDialog::~ConfidenceConnectedSegmentationDialog()
{
    delete ui;
}

void ConfidenceConnectedSegmentationDialog::setPickPointGraphicsScene(CustomGraphicsScene *graphicsScene)
{
    connect(graphicsScene, SIGNAL(pointPicked(QPoint)), this, SLOT(updateSeedPoint(QPoint)));
    connect(ui->pushButtonPick, SIGNAL(toggled(bool)), graphicsScene, SLOT(enablePick(bool)));
    int maxX = graphicsScene->width() - 1;
    int maxY = graphicsScene->height() - 1;
    ui->spinBoxXSeed->setValue(maxX);
    ui->spinBoxYSeed->setValue(maxY);
}

void ConfidenceConnectedSegmentationDialog::updateSeedPoint(QPoint point)
{
    ui->spinBoxXSeed->setValue(point.x());
    ui->spinBoxYSeed->setValue(point.y());
    ui->pushButtonPick->setChecked(false);
}

void ConfidenceConnectedSegmentationDialog::on_pushButtonApply_clicked()
{
    ImageLayer *imageLayer = ImageLayer::instance();
    int curvatureFilterNumberOfIterations = ui->spinBoxCurvatureIterations->value();
    float curvatureFilterTimeStep = ui->lineEditTimeStep->text().toFloat();
    float confidenceFilterMultiplier = ui->lineEditMultiplier->text().toFloat();
    int confidenceFilterNumberOfIterations = ui->spinBoxConfidenceIterations->value();
    int confidenceFilterNeighborhoodRadius = ui->spinBoxNeighborhoodRadius->value();

    imageLayer->resizeImageVector(3);

    curvatureFilter->SetInput(imageLayer->floatGrayImagePointer(0));
    curvatureFilter->SetNumberOfIterations(curvatureFilterNumberOfIterations);
    curvatureFilter->SetTimeStep(curvatureFilterTimeStep);
    castToIntFilter->SetInput(curvatureFilter->GetOutput());
    castToIntFilter->Update();
    imageLayer->setGrayImage(1, castToIntFilter->GetOutput());

    confidenceFilter->SetInput(curvatureFilter->GetOutput());
    confidenceFilter->SetMultiplier(confidenceFilterMultiplier);
    confidenceFilter->SetNumberOfIterations(confidenceFilterNumberOfIterations);
    confidenceFilter->SetReplaceValue(255);
    ImageLayer::FloatImageType::IndexType seedIndex;
    seedIndex[0] = ui->spinBoxXSeed->value();
    seedIndex[1] = ui->spinBoxYSeed->value();
    confidenceFilter->SetSeed(seedIndex);
    confidenceFilter->SetInitialNeighborhoodRadius(confidenceFilterNeighborhoodRadius);
    castToIntFilter->SetInput(confidenceFilter->GetOutput());
    castToIntFilter->Update();
    imageLayer->setGrayImage(2, castToIntFilter->GetOutput());
}
