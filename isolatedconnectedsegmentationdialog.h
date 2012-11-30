#ifndef ISOLATEDCONNECTEDSEGMENTATIONDIALOG_H
#define ISOLATEDCONNECTEDSEGMENTATIONDIALOG_H

#include <QDialog>
#include <itkCurvatureFlowImageFilter.h>
#include <itkIsolatedConnectedImageFilter.h>
#include <itkCastImageFilter.h>
#include "imagelayer.h"

class CustomGraphicsScene;

namespace Ui {
    class IsolatedConnectedSegmentationDialog;
}

class IsolatedConnectedSegmentationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IsolatedConnectedSegmentationDialog(QWidget *parent = 0);
    ~IsolatedConnectedSegmentationDialog();
    void setPickPointGraphicsScene(CustomGraphicsScene *graphicsScene);

private slots:
    void on_pushButtonApply_clicked();
    void pushButtonInsidePickHandler(bool checked);
    void pushButtonOutsidePickHandler(bool checked);
    void updateInsidePoint(QPoint point);
    void updateOutsidePoint(QPoint point);

private:
    Ui::IsolatedConnectedSegmentationDialog *ui;
    typedef itk::CurvatureFlowImageFilter<ImageLayer::FloatImageType, ImageLayer::FloatImageType> CurvatureFlowFilterType;
    typedef itk::IsolatedConnectedImageFilter<ImageLayer::FloatImageType, ImageLayer::FloatImageType> IsolatedConnectedFilterType;
    typedef itk::CastImageFilter<ImageLayer::FloatImageType, ImageLayer::GrayImageType> CastToIntFilterType;
    CurvatureFlowFilterType::Pointer curvatureFilter;
    IsolatedConnectedFilterType::Pointer isolatedFilter;
    CastToIntFilterType::Pointer castToIntFilter;
    CustomGraphicsScene *graphicsScene;
};

#endif // ISOLATEDCONNECTEDSEGMENTATIONDIALOG_H
