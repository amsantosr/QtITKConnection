#ifndef BINARYTHRESHOLDFILTERDIALOG_H
#define BINARYTHRESHOLDFILTERDIALOG_H

#include <QDialog>

namespace Ui {
    class BinaryThresholdFilterDialog;
}

class BinaryThresholdFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BinaryThresholdFilterDialog(QWidget *parent = 0);
    ~BinaryThresholdFilterDialog();

private:
    Ui::BinaryThresholdFilterDialog *ui;

private slots:
    void on_pushButtonApply_clicked();
};

#endif // BINARYTHRESHOLDFILTERDIALOG_H
