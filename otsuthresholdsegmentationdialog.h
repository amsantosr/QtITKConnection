#ifndef OTSUTHRESHOLDSEGMENTATIONDIALOG_H
#define OTSUTHRESHOLDSEGMENTATIONDIALOG_H

#include <QDialog>
#include <imagelayer.h>
#include <itkOtsuThresholdImageFilter.h>

namespace Ui {
    class OtsuThresholdSegmentationDialog;
}

class OtsuThresholdSegmentationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OtsuThresholdSegmentationDialog(QWidget *parent = 0);
    ~OtsuThresholdSegmentationDialog();

private:
    Ui::OtsuThresholdSegmentationDialog *ui;
    typedef itk::OtsuThresholdImageFilter<ImageLayer::GrayImageType, ImageLayer::GrayImageType> OtsuThresholdFilterType;
    OtsuThresholdFilterType::Pointer otsuFilter;

private slots:
    void on_pushButtonApply_clicked();
};

#endif // OTSUTHRESHOLDSEGMENTATIONDIALOG_H
