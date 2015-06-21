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
signals:
    void cancelButtonClicked();
public slots:
    void getProgress(int prog);
private:
    Ui::ProgressBarDialog *ui;
};

#endif // PROGRESSBARDIALOG_H
