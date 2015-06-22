#include "progressbardialog.h"
#include "ui_progressbardialog.h"

ProgressBarDialog::ProgressBarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressBarDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButtonCancel, &QAbstractButton::clicked,
                     this, &ProgressBarDialog::cancelButtonClicked);
}

ProgressBarDialog::~ProgressBarDialog()
{
    delete ui;
}

void ProgressBarDialog::setProgress(int prog)
{
    ui->progressBar->setValue(prog);
}
