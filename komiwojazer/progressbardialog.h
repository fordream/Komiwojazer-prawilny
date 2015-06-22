#ifndef PROGRESSBARDIALOG_H
#define PROGRESSBARDIALOG_H

#include <QDialog>

namespace Ui {
class ProgressBarDialog;
}

class ProgressBarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressBarDialog(QWidget *parent = 0);
    ~ProgressBarDialog();

    void setProgress(int prog);
signals:
    void cancelButtonClicked();
private:
    Ui::ProgressBarDialog *ui;
};

#endif // PROGRESSBARDIALOG_H
