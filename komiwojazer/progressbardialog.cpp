#include "progressbardialog.h"
#include "ui_progressbardialog.h"

#include <QCloseEvent>

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

void ProgressBarDialog::closeEvent(QCloseEvent *event)
{
    event->ignore();
    emit(ui->pushButtonCancel->clicked());
}
