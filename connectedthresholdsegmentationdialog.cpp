#include "connectedthresholdsegmentationdialog.h"
#include "ui_connectedthresholdsegmentationdialog.h"
#include "imagelayer.h"
//#include "customscrollarea.h"
#include "customgraphicsscene.h"
#include <QDoubleValidator>

ConnectedThresholdSegmentationDialog::ConnectedThresholdSegmentationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectedThresholdSegmentationDialog)
{
    ui->setupUi(this);
    ui->sliderLowerThreshold->setValue(0);
    ui->sliderUpperThreshold->setValue(255);
    ui->spinBoxNumberOfIterations->setValue(5);
    ui->lineEditTimeStep->setValidator(new QDoubleValidator(this));
    ui->lineEditTimeStep->setText("0.125");

    curvatureFilter = CurvatureFlowFilterType::New();
    connectedFilter = ConnectedThresholdFilterType::New();
    castToIntFilter = CastToIntFilterType::New();
}

ConnectedThresholdSegmentationDialog::~ConnectedThresholdSegmentationDialog()
{
    delete ui;
}

void ConnectedThresholdSegmentationDialog::setPickPointGraphicsScene(CustomGraphicsScene *graphicsScene)
{
    connect(ui->pushButtonPickPoint, SIGNAL(toggled(bool)), graphicsScene, SLOT(enablePick(bool)));
    connect(graphicsScene, SIGNAL(pointPicked(QPoint)), this, SLOT(updateSeedPoint(QPoint)));
}

void ConnectedThresholdSegmentationDialog::updateSeedPoint(QPoint point)
{
    ui->lineEditXSeed->setText(QString::number(point.x()));
    ui->lineEditYSeed->setText(QString::number(point.y()));
    ui->pushButtonPickPoint->setChecked(false);
}

void ConnectedThresholdSegmentationDialog::on_pushButtonApply_clicked()
{
    ImageLayer *imageLayer = ImageLayer::instance();

    int connectedLowerThreshold = ui->sliderLowerThreshold->value();
    int connectedUpperThreshold = ui->sliderUpperThreshold->value();
    int curvatureFilterNumberOfIterations = ui->spinBoxNumberOfIterations->value();
    float curvatureFilterTimeStep = ui->lineEditTimeStep->text().toFloat();

    imageLayer->resizeImageVector(3);
    curvatureFilter->SetInput(imageLayer->floatGrayImagePointer(0));
    curvatureFilter->SetNumberOfIterations(curvatureFilterNumberOfIterations);
    curvatureFilter->SetTimeStep(curvatureFilterTimeStep);
    castToIntFilter->SetInput(curvatureFilter->GetOutput());
    castToIntFilter->Update();
    imageLayer->setGrayImage(1, castToIntFilter->GetOutput());

    connectedFilter->SetInput(curvatureFilter->GetOutput());
    connectedFilter->SetLower(connectedLowerThreshold);
    connectedFilter->SetUpper(connectedUpperThreshold);
    connectedFilter->SetReplaceValue(255.0f);
    ImageLayer::FloatImageType::IndexType seedIndex;
    seedIndex[0] = ui->lineEditXSeed->text().toInt();
    seedIndex[1] = ui->lineEditYSeed->text().toInt();
    connectedFilter->SetSeed(seedIndex);
    castToIntFilter->SetInput(connectedFilter->GetOutput());
    castToIntFilter->Update();
    imageLayer->setGrayImage(2, castToIntFilter->GetOutput());
}
