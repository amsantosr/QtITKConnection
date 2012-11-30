#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QScrollArea>
#include <QLabel>
#include <QTabWidget>
#include <QToolBox>
#include <QPoint>
#include <QGraphicsView>
#include "imagelayer.h"
#include <itkRescaleIntensityImageFilter.h>
#include <itkNormalizeImageFilter.h>
//#include "customscrollarea.h"
#include "customgraphicsscene.h"
#include "binarythresholdfilterdialog.h"
#include "thresholdfilterdialog.h"
#include "cannyedgedetectionfilterdialog.h"
#include "rescaleintensityfilterdialog.h"
#include "sigmoidfilterdialog.h"
#include "gradientmagnituderecursivegaussianfilterdialog.h"
#include "derivativeimagefilterdialog.h"
#include "gradientanisotropicfilterdialog.h"
#include "connectedthresholdsegmentationdialog.h"
#include "confidenceconnectedsegmentationdialog.h"
#include "otsuthresholdsegmentationdialog.h"
#include "neighborhoodconnectedsegmentationdialog.h"
#include "isolatedconnectedsegmentationdialog.h"
#include "watershedsegmentationdialog.h"
#include "fastmarchingsegmentationdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeImageColorTable();

    ui->mainToolBar->hide();
    m_tabWidget = new QTabWidget(this);
    setCentralWidget(m_tabWidget);

    ImageLayer* imageLayer = ImageLayer::instance();
    connect(imageLayer, SIGNAL(imageVectorSizeChanged(int)), this, SLOT(setNumberOfTabs(int)));
    connect(imageLayer, SIGNAL(grayImageChanged(int)), this, SLOT(updateGrayImageTab(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeImageColorTable()
{
    m_colorTable.resize(256);
    for (int i = 0; i < 256; ++i) {
        m_colorTable[i] = qRgb(i, i, i);
    }
}

void MainWindow::updateGrayImageTab(int index)
{
    ImageLayer *imageLayer = ImageLayer::instance();
    unsigned char *data = imageLayer->grayImageData(index);
    int width = imageLayer->width();
    int height = imageLayer->height();
    int bpl = imageLayer->grayBytesPerLine();

    QImage image(data, width, height, bpl, QImage::Format_Indexed8);
    image.setColorTable(m_colorTable);
    QGraphicsView *graphicsView = dynamic_cast<QGraphicsView*>(m_tabWidget->widget(index));
    CustomGraphicsScene *graphicsScene = dynamic_cast<CustomGraphicsScene*>(graphicsView->scene());
    graphicsScene->addPixmap(QPixmap::fromImage(image));
}

void MainWindow::setNumberOfTabs(int numTabs)
{
    if (m_tabWidget->count() < numTabs) {
        for (int index = m_tabWidget->count(); index < numTabs; ++index) {
            appendNewTab();
        }
    } else {
        for (int index = m_tabWidget->count() - 1; index >= numTabs; --index) {
            QGraphicsView *graphicsView = dynamic_cast<QGraphicsView*>(m_tabWidget->widget(index));
            CustomGraphicsScene *graphicsScene = dynamic_cast<CustomGraphicsScene*>(graphicsView->scene());
            m_tabWidget->removeTab(index);
            delete graphicsView;
            delete graphicsScene;
        }
    }
}

void MainWindow::appendNewTab()
{
    CustomGraphicsScene *graphicsScene = new CustomGraphicsScene(this);
    QGraphicsView *graphicsView = new QGraphicsView(graphicsScene, this);
    int id = m_tabWidget->count();
    m_tabWidget->addTab(graphicsView, tr("Tab%1").arg(id));
}

void MainWindow::on_actionOpenImage_triggered()
{
    QString filename =
            QFileDialog::getOpenFileName(this, tr("Seleccionar imagen"),
                                         QString(), tr("Images (*.jpg *.png)"));

    if (!filename.isNull()) {
        ImageLayer *imageLayer = ImageLayer::instance();
        imageLayer->openGrayImage(filename.toStdString().c_str());
    }
}

void MainWindow::on_actionBinaryThresholdFilter_triggered()
{
    BinaryThresholdFilterDialog *btfDialog = new BinaryThresholdFilterDialog(this);
    btfDialog->setAttribute(Qt::WA_DeleteOnClose);
    btfDialog->show();
}

void MainWindow::on_actionGeneralThresholdFilter_triggered()
{
    ThresholdFilterDialog *tfDialog = new ThresholdFilterDialog(this);
    tfDialog->setAttribute(Qt::WA_DeleteOnClose);
    tfDialog->show();
}

void MainWindow::on_actionCannyEdgeDetectionFilter_triggered()
{
    CannyEdgeDetectionFilterDialog *cedfDialog = new CannyEdgeDetectionFilterDialog(this);
    cedfDialog->setAttribute(Qt::WA_DeleteOnClose);
    cedfDialog->show();
}

void MainWindow::on_actionRescaleIntensityFilter_triggered()
{
    RescaleIntensityFilterDialog *rifDialog = new RescaleIntensityFilterDialog(this);
    rifDialog->setAttribute(Qt::WA_DeleteOnClose);
    rifDialog->show();
}

void MainWindow::on_actionNormalizeFilter_triggered()
{
    ImageLayer *imageLayer = ImageLayer::instance();

    typedef itk::NormalizeImageFilter<ImageLayer::GrayImageType, ImageLayer::FloatImageType> NormalizeFilterType;
    typedef itk::RescaleIntensityImageFilter<ImageLayer::FloatImageType, ImageLayer::GrayImageType> RescaleFilterType;
    NormalizeFilterType::Pointer normalizeFilter = NormalizeFilterType::New();
    RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();

    imageLayer->resizeImageVector(2);
    normalizeFilter->SetInput(imageLayer->grayImagePointer(0));
    rescaleFilter->SetInput(normalizeFilter->GetOutput());
    rescaleFilter->SetOutputMinimum(0);
    rescaleFilter->SetOutputMaximum(255);
    rescaleFilter->Update();

    imageLayer->setGrayImage(1, rescaleFilter->GetOutput());
}

void MainWindow::on_actionSigmoidFilter_triggered()
{
    SigmoidFilterDialog *sfDialog = new SigmoidFilterDialog(this);
    sfDialog->setAttribute(Qt::WA_DeleteOnClose);
    sfDialog->show();
}

void MainWindow::on_actionDerivativeFilter_triggered()
{
    DerivativeImageFilterDialog *diFilterDialog = new DerivativeImageFilterDialog(this);
    diFilterDialog->setAttribute(Qt::WA_DeleteOnClose);
    diFilterDialog->show();
}

void MainWindow::on_actionGradientAnisotropicDifussionFilter_triggered()
{
    GradientAnisotropicFilterDialog *gaFilterDialog = new GradientAnisotropicFilterDialog(this);
    gaFilterDialog->setAttribute(Qt::WA_DeleteOnClose);
    gaFilterDialog->show();
}

void MainWindow::on_actionConnectedThresholdSegmentation_triggered()
{
    ConnectedThresholdSegmentationDialog *ctsDialog = new ConnectedThresholdSegmentationDialog(this);
    QGraphicsView *graphicsView = dynamic_cast<QGraphicsView*>(m_tabWidget->widget(0));
    CustomGraphicsScene *graphicsScene = dynamic_cast<CustomGraphicsScene*>(graphicsView->scene());
    ctsDialog->setPickPointGraphicsScene(graphicsScene);
    ctsDialog->setAttribute(Qt::WA_DeleteOnClose);
    ctsDialog->show();
}

void MainWindow::on_actionConfidenceConnectedSegmentation_triggered()
{
    ConfidenceConnectedSegmentationDialog *ccDialog = new ConfidenceConnectedSegmentationDialog(this);
    QGraphicsView *graphicsView = dynamic_cast<QGraphicsView*>(m_tabWidget->widget(0));
    CustomGraphicsScene *graphicsScene = dynamic_cast<CustomGraphicsScene*>(graphicsView->scene());
    ccDialog->setPickPointGraphicsScene(graphicsScene);
    ccDialog->setAttribute(Qt::WA_DeleteOnClose);
    ccDialog->show();
}

void MainWindow::on_actionOtsuThresholdSegmentation_triggered()
{
    OtsuThresholdSegmentationDialog *otsuDialog = new OtsuThresholdSegmentationDialog(this);
    otsuDialog->setAttribute(Qt::WA_DeleteOnClose);
    otsuDialog->show();
}

void MainWindow::on_actionNeighborhoodConnectedSegmentation_triggered()
{
    NeighborhoodConnectedSegmentationDialog *neighborhoodDialog = new NeighborhoodConnectedSegmentationDialog(this);
    QGraphicsView *graphicsView = dynamic_cast<QGraphicsView*>(m_tabWidget->widget(0));
    CustomGraphicsScene *graphicsScene = dynamic_cast<CustomGraphicsScene*>(graphicsView->scene());
    neighborhoodDialog->setPickPointGraphicsScene(graphicsScene);
    neighborhoodDialog->setAttribute(Qt::WA_DeleteOnClose);
    neighborhoodDialog->show();
}

void MainWindow::on_actionIsolatedConnected_triggered()
{
    IsolatedConnectedSegmentationDialog *isolatedDialog = new IsolatedConnectedSegmentationDialog(this);
    QGraphicsView *graphicsView = dynamic_cast<QGraphicsView*>(m_tabWidget->widget(0));
    CustomGraphicsScene *graphicsScene = dynamic_cast<CustomGraphicsScene*>(graphicsView->scene());
    isolatedDialog->setPickPointGraphicsScene(graphicsScene);
    isolatedDialog->setAttribute(Qt::WA_DeleteOnClose);
    isolatedDialog->show();
}

void MainWindow::on_actionWatershedSegmentation_triggered()
{
    WatershedSegmentationDialog *watershedDialog = new WatershedSegmentationDialog(this);
    watershedDialog->setAttribute(Qt::WA_DeleteOnClose);
    watershedDialog->show();
}

void MainWindow::on_actionFastMarchingSegmentation_triggered()
{
    FastMarchingSegmentationDialog *fastMarchingDialog = new FastMarchingSegmentationDialog(this);
    QGraphicsView *graphicsView = dynamic_cast<QGraphicsView*>(m_tabWidget->widget(0));
    CustomGraphicsScene *graphicsScene = dynamic_cast<CustomGraphicsScene*>(graphicsView->scene());
    fastMarchingDialog->setPickPointGraphicsScene(graphicsScene);
    fastMarchingDialog->setAttribute(Qt::WA_DeleteOnClose);
    fastMarchingDialog->show();
}
