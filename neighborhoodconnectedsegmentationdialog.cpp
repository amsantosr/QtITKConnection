#include "neighborhoodconnectedsegmentationdialog.h"
#include "ui_neighborhoodconnectedsegmentationdialog.h"
#include "imagelayer.h"
//#include "customscrollarea.h"
#include "customgraphicsscene.h"
#include <QDoubleValidator>

NeighborhoodConnectedSegmentationDialog::NeighborhoodConnectedSegmentationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NeighborhoodConnectedSegmentationDialog)
{
    ui->setupUi(this);
    ui->lineEditCurvatureTimeStep->setValidator(new QDoubleValidator(this));
    ui->lineEditCurvatureMultiplier->setEnabled(false);

    ui->spinBoxNeighborhoodXRadius->setMinimum(1);
    ui->spinBoxNeighborhoodXRadius->setMaximum(10);
    ui->spinBoxNeighborhoodYRadius->setMinimum(1);
    ui->spinBoxNeighborhoodYRadius->setMaximum(10);

    ui->spinBoxNeighborhoodLower->setMinimum(0);
    ui->spinBoxNeighborhoodLower->setMaximum(255);
    ui->spinBoxNeighborhoodUpper->setMinimum(0);
    ui->spinBoxNeighborhoodUpper->setMaximum(255);

    ui->sliderNeighborhoodLower->setMinimum(0);
    ui->sliderNeighborhoodLower->setMaximum(255);
    ui->sliderNeighborhoodUpper->setMinimum(0);
    ui->sliderNeighborhoodUpper->setMaximum(255);

    ui->spinBoxNeighborhoodXRadius->setValue(2);
    ui->spinBoxNeighborhoodYRadius->setValue(2);
    ui->spinBoxCurvatureIterations->setValue(5);
    ui->lineEditCurvatureTimeStep->setText("0.125");

    castToIntFilter = CastToIntFilterType::New();
    curvatureFilter = CurvatureFilterType::New();
    neighborhoodFilter = NeighborhoodFilterType::New();
}

NeighborhoodConnectedSegmentationDialog::~NeighborhoodConnectedSegmentationDialog()
{
    delete ui;
}

void NeighborhoodConnectedSegmentationDialog::setPickPointGraphicsScene(CustomGraphicsScene *graphicsScene)
{
    connect(ui->pushButtonPick, SIGNAL(toggled(bool)), graphicsScene, SLOT(enablePick(bool)));
    connect(graphicsScene, SIGNAL(pointPicked(QPoint)), this, SLOT(updateSeedPoint(QPoint)));
    int size0 = graphicsScene->width();
    int size1 = graphicsScene->height();
    ui->spinBoxNeighborhoodXSeed->setMinimum(0);
    ui->spinBoxNeighborhoodYSeed->setMinimum(0);
    ui->spinBoxNeighborhoodXSeed->setMaximum(size0 - 1);
    ui->spinBoxNeighborhoodYSeed->setMaximum(size1 - 1);
}

void NeighborhoodConnectedSegmentationDialog::updateSeedPoint(QPoint point)
{
    ui->spinBoxNeighborhoodXSeed->setValue(point.x());
    ui->spinBoxNeighborhoodYSeed->setValue(point.y());
    ui->pushButtonPick->setChecked(false);
}

void NeighborhoodConnectedSegmentationDialog::on_pushButtonApply_clicked()
{
    ImageLayer *imageLayer = ImageLayer::instance();
    int curvatureIterations = ui->spinBoxCurvatureIterations->value();
    int curvatureTimeStep = ui->lineEditCurvatureTimeStep->text().toFloat();
    int neighborhoodLower = ui->spinBoxNeighborhoodLower->value();
    int neighborhoodUpper = ui->spinBoxNeighborhoodUpper->value();

    imageLayer->resizeImageVector(3);
    curvatureFilter->SetInput(imageLayer->floatGrayImagePointer(0));
    curvatureFilter->SetNumberOfIterations(curvatureIterations);
    curvatureFilter->SetTimeStep(curvatureTimeStep);
    castToIntFilter->SetInput(curvatureFilter->GetOutput());
    imageLayer->setGrayImage(1, castToIntFilter->GetOutput());

    neighborhoodFilter->SetInput(curvatureFilter->GetOutput());
    neighborhoodFilter->SetLower(neighborhoodLower);
    neighborhoodFilter->SetUpper(neighborhoodUpper);
    ImageLayer::FloatImageType::SizeType radius;
    radius[0] = ui->spinBoxNeighborhoodXRadius->value();
    radius[1] = ui->spinBoxNeighborhoodYRadius->value();
    neighborhoodFilter->SetRadius(radius);
    ImageLayer::FloatImageType::IndexType index;
    index[0] = ui->spinBoxNeighborhoodXSeed->text().toInt();
    index[1] = ui->spinBoxNeighborhoodYSeed->text().toInt();
    neighborhoodFilter->SetSeed(index);
    neighborhoodFilter->SetReplaceValue(255.0f);
    castToIntFilter->SetInput(neighborhoodFilter->GetOutput());
    castToIntFilter->Update();
    imageLayer->setGrayImage(2, castToIntFilter->GetOutput());
}
