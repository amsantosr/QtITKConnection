#ifndef NEIGHBORHOODCONNECTEDSEGMENTATIONDIALOG_H
#define NEIGHBORHOODCONNECTEDSEGMENTATIONDIALOG_H

#include <QDialog>
#include "imagelayer.h"
#include <itkCastImageFilter.h>
#include <itkCurvatureFlowImageFilter.h>
#include <itkNeighborhoodConnectedImageFilter.h>

class CustomGraphicsScene;

namespace Ui {
    class NeighborhoodConnectedSegmentationDialog;
}

class NeighborhoodConnectedSegmentationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NeighborhoodConnectedSegmentationDialog(QWidget *parent = 0);
    void setPickPointGraphicsScene(CustomGraphicsScene *scrollArea);
    ~NeighborhoodConnectedSegmentationDialog();

private:
    Ui::NeighborhoodConnectedSegmentationDialog *ui;
    typedef itk::CastImageFilter<ImageLayer::FloatImageType, ImageLayer::GrayImageType> CastToIntFilterType;
    typedef itk::CurvatureFlowImageFilter<ImageLayer::FloatImageType, ImageLayer::FloatImageType> CurvatureFilterType;
    typedef itk::NeighborhoodConnectedImageFilter<ImageLayer::FloatImageType, ImageLayer::FloatImageType> NeighborhoodFilterType;
    CastToIntFilterType::Pointer castToIntFilter;
    CurvatureFilterType::Pointer curvatureFilter;
    NeighborhoodFilterType::Pointer neighborhoodFilter;

private slots:
    void on_pushButtonApply_clicked();
    void updateSeedPoint(QPoint point);
};

#endif // NEIGHBORHOODCONNECTEDSEGMENTATIONDIALOG_H
