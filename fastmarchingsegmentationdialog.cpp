#include "fastmarchingsegmentationdialog.h"
#include "ui_fastmarchingsegmentationdialog.h"
#include "customgraphicsscene.h"
#include <QTextStream>
#include <QValidator>

FastMarchingSegmentationDialog::FastMarchingSegmentationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FastMarchingSegmentationDialog)
{
    ui->setupUi(this);
    thresholdFilter = ThresholdingFilterType::New();
    rescaleFilter = RescaleFilterType::New();
    curvatureFilter = CurvatureFilterType::New();
    gradientFilter = GradientFilterType::New();
    sigmoidFilter = SigmoidFilterType::New();
    fastMarchingFilter = FastMarchingFilterType::New();
    castToIntPointer = CastToIntFilterType::New();

    rescaleFilter->SetOutputMinimum(0);
    rescaleFilter->SetOutputMaximum(255);

    ui->lineEditCurvatureConductance->setValidator(new QDoubleValidator(this));
    ui->lineEditCurvatureTimeStep->setValidator(new QDoubleValidator(this));
    ui->lineEditGradientSigma->setValidator(new QDoubleValidator(this));
    ui->lineEditSigmoidAlpha->setValidator(new QDoubleValidator(this));
    ui->lineEditSigmoidBeta->setValidator(new QDoubleValidator(this));
    ui->lineEditStoppingValue->setValidator(new QDoubleValidator(this));

    ui->lineEditGradientSigma->setText("1.0");
    ui->lineEditSigmoidAlpha->setText("-0.5");
    ui->lineEditSigmoidBeta->setText("3.0");
    ui->lineEditStoppingValue->setText("100");
    ui->lineEditCurvatureConductance->setText("9.0");
    ui->lineEditCurvatureTimeStep->setText("0.125");
    ui->spinBoxCurvatureIterations->setValue(5);
    ui->spinBoxTimeThreshold->setValue(100);
}

FastMarchingSegmentationDialog::~FastMarchingSegmentationDialog()
{
    delete ui;
}

void FastMarchingSegmentationDialog::setPickPointGraphicsScene(CustomGraphicsScene *graphicsScene)
{
    this->graphicsScene = graphicsScene;
    connect(graphicsScene, SIGNAL(pointPicked(QPoint)), this, SLOT(addPoint(QPoint)));
    connect(ui->pushButtonChoose, SIGNAL(toggled(bool)), graphicsScene, SLOT(enablePick(bool)));
}

void FastMarchingSegmentationDialog::addPoint(QPoint point)
{
    QString pointString;
    QTextStream(&pointString) << "(" << point.x() << ", " << point.y() << ")";
    QListWidgetItem *pointItem = new QListWidgetItem(pointString);
    pointItem->setData(Qt::UserRole, point);
    ui->listTrialPoints->addItem(pointItem);
}

void FastMarchingSegmentationDialog::on_pushButtonRemove_clicked()
{
    QListWidgetItem *listItem = ui->listTrialPoints->takeItem(ui->listTrialPoints->currentRow());
    if (listItem != 0)
        delete listItem;
}

void FastMarchingSegmentationDialog::on_pushButtonApply_clicked()
{
    typedef FastMarchingFilterType::NodeContainer NodeContainer;
    typedef FastMarchingFilterType::NodeType NodeType;

    ImageLayer *imageLayer = ImageLayer::instance();
    int curvatureIterations = ui->spinBoxCurvatureIterations->value();
    float curvatureConductance = ui->lineEditCurvatureConductance->text().toFloat();
    float curvatureTimeStep = ui->lineEditCurvatureTimeStep->text().toFloat();
    float gradientSigma = ui->lineEditGradientSigma->text().toFloat();
    float sigmoidAlpha = ui->lineEditSigmoidAlpha->text().toFloat();
    float sigmoidBeta = ui->lineEditSigmoidBeta->text().toFloat();
    float stoppingValue = ui->lineEditStoppingValue->text().toFloat();
    int timeThreshold = ui->spinBoxTimeThreshold->value();

    imageLayer->resizeImageVector(5);
    curvatureFilter->SetInput(imageLayer->floatGrayImagePointer(0));
    curvatureFilter->SetTimeStep(curvatureTimeStep);
    curvatureFilter->SetNumberOfIterations(curvatureIterations);
    curvatureFilter->SetConductanceParameter(curvatureConductance);
    castToIntPointer->SetInput(curvatureFilter->GetOutput());
    castToIntPointer->Update();
    imageLayer->setGrayImage(1, castToIntPointer->GetOutput());

    gradientFilter->SetInput(curvatureFilter->GetOutput());
    gradientFilter->SetSigma(gradientSigma);
    castToIntPointer->SetInput(gradientFilter->GetOutput());
    castToIntPointer->Update();
    imageLayer->setGrayImage(2, castToIntPointer->GetOutput());

    sigmoidFilter->SetInput(gradientFilter->GetOutput());
    sigmoidFilter->SetAlpha(sigmoidAlpha);
    sigmoidFilter->SetBeta(sigmoidBeta);
    sigmoidFilter->SetOutputMinimum(0.0f);
    sigmoidFilter->SetOutputMaximum(1.0f);
    rescaleFilter->SetInput(sigmoidFilter->GetOutput());
    rescaleFilter->Update();
    imageLayer->setGrayImage(3, rescaleFilter->GetOutput());

    fastMarchingFilter->SetInput(sigmoidFilter->GetOutput());
    NodeContainer::Pointer seeds = NodeContainer::New();
    seeds->Initialize();

    for (int itemRow = 0; itemRow < ui->listTrialPoints->count(); ++itemRow) {
        NodeType node;
        ImageLayer::FloatImageType::IndexType seedPosition;
        QListWidgetItem *listItem = ui->listTrialPoints->item(itemRow);
        QPoint point = listItem->data(Qt::UserRole).toPoint();
        seedPosition[0] = point.x();
        seedPosition[1] = point.y();
        node.SetValue(0.0f);
        node.SetIndex(seedPosition);
        seeds->InsertElement(itemRow, node);
    }

    fastMarchingFilter->SetTrialPoints(seeds);
    fastMarchingFilter->SetOutputSize(imageLayer->floatGrayImagePointer(0)->GetBufferedRegion().GetSize());
    fastMarchingFilter->SetStoppingValue(stoppingValue);
    thresholdFilter->SetInput(fastMarchingFilter->GetOutput());
    thresholdFilter->SetLowerThreshold(0);
    thresholdFilter->SetUpperThreshold(timeThreshold);
    thresholdFilter->SetInsideValue(255);
    thresholdFilter->SetOutsideValue(0);
    thresholdFilter->Update();
    imageLayer->setGrayImage(4, thresholdFilter->GetOutput());
}
