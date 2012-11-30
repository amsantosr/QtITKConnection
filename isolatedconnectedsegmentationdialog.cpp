#include "isolatedconnectedsegmentationdialog.h"
#include "ui_isolatedconnectedsegmentationdialog.h"
#include "customgraphicsscene.h"
#include <QDoubleValidator>

IsolatedConnectedSegmentationDialog::IsolatedConnectedSegmentationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IsolatedConnectedSegmentationDialog)
{
    ui->setupUi(this);
    ui->spinBoxCurvatureIterations->setValue(5);
    ui->lineEditCurvatureTimeStep->setValidator(new QDoubleValidator(this));
    ui->lineEditCurvatureTimeStep->setText(tr("0.125"));

    curvatureFilter = CurvatureFlowFilterType::New();
    isolatedFilter = IsolatedConnectedFilterType::New();
    castToIntFilter = CastToIntFilterType::New();
}

IsolatedConnectedSegmentationDialog::~IsolatedConnectedSegmentationDialog()
{
    delete ui;
}

void IsolatedConnectedSegmentationDialog::setPickPointGraphicsScene(CustomGraphicsScene *graphicsScene)
{
    this->graphicsScene = graphicsScene;
    connect(ui->pushButtonInsidePick, SIGNAL(toggled(bool)), this, SLOT(pushButtonInsidePickHandler(bool)));
    connect(ui->pushButtonOutsidePick, SIGNAL(toggled(bool)), this, SLOT(pushButtonOutsidePickHandler(bool)));
}

void IsolatedConnectedSegmentationDialog::on_pushButtonApply_clicked()
{
    ImageLayer *imageLayer = ImageLayer::instance();
    imageLayer->resizeImageVector(3);
    int curvatureIterations = ui->spinBoxCurvatureIterations->value();
    float curvatureTimeStep = ui->lineEditCurvatureTimeStep->text().toFloat();
    float isolatedLower = ui->spinBoxIsolatedLowerThreshold->value();
    ImageLayer::FloatImageType::IndexType seed1, seed2;
    seed1[0] = ui->spinBoxInsideXSeed->value();
    seed1[1] = ui->spinBoxInsideYSeed->value();
    seed2[0] = ui->spinBoxOutsideYSeed->value();
    seed2[1] = ui->spinBoxOutsideYSeed->value();

    curvatureFilter->SetInput(imageLayer->floatGrayImagePointer(0));
    curvatureFilter->SetNumberOfIterations(curvatureIterations);
    curvatureFilter->SetTimeStep(curvatureTimeStep);
    castToIntFilter->SetInput(curvatureFilter->GetOutput());
    castToIntFilter->Update();
    imageLayer->setGrayImage(1, castToIntFilter->GetOutput());

    isolatedFilter->SetInput(curvatureFilter->GetOutput());
    isolatedFilter->SetLower(isolatedLower);
    isolatedFilter->SetSeed1(seed1);
    isolatedFilter->SetSeed2(seed2);
    isolatedFilter->SetReplaceValue(255.0f);
    castToIntFilter->SetInput(isolatedFilter->GetOutput());
    castToIntFilter->Update();
    imageLayer->setGrayImage(2, castToIntFilter->GetOutput());
}

void IsolatedConnectedSegmentationDialog::updateInsidePoint(QPoint point)
{
    ui->spinBoxInsideXSeed->setValue(point.x());
    ui->spinBoxInsideYSeed->setValue(point.y());
    ui->pushButtonInsidePick->setChecked(false);
}

void IsolatedConnectedSegmentationDialog::updateOutsidePoint(QPoint point)
{
    ui->spinBoxOutsideXSeed->setValue(point.x());
    ui->spinBoxOutsideYSeed->setValue(point.y());
    ui->pushButtonOutsidePick->setChecked(false);
}

void IsolatedConnectedSegmentationDialog::pushButtonInsidePickHandler(bool checked)
{
    if (checked) {
        ui->pushButtonOutsidePick->setChecked(false);
        connect(graphicsScene, SIGNAL(pointPicked(QPoint)), this, SLOT(updateInsidePoint(QPoint)));
        graphicsScene->enablePick(true);
    } else {
        if (!ui->pushButtonOutsidePick->isChecked())
            graphicsScene->enablePick(false);
        disconnect(graphicsScene, 0, this, 0);
    }
}

void IsolatedConnectedSegmentationDialog::pushButtonOutsidePickHandler(bool checked)
{
    if (checked) {
        ui->pushButtonInsidePick->setChecked(false);
        connect(graphicsScene, SIGNAL(pointPicked(QPoint)), this, SLOT(updateOutsidePoint(QPoint)));
        graphicsScene->enablePick(true);
    } else {
        if (!ui->pushButtonInsidePick->isChecked())
            graphicsScene->enablePick(false);
        disconnect(graphicsScene, 0, this, 0);
    }
}
