#include "browser.h"
#include "ui_browser.h"
#include <geolistitem.h>

Browser::Browser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Browser)
{
    ui->setupUi(this);
    ui->button_add->setEnabled(false);
    connect(&list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(setSelectedItem(QListWidgetItem*)));
}

Browser::~Browser()
{
    delete ui;
}

void Browser::on_button_add_clicked()
{
    emit add_button_clicked();
}

void Browser::on_button_search_clicked()
{
    emit search_button_clicked(ui->input->text());
}

void Browser::on_input_textEdited(const QString &arg1)
{
    ui->button_add->setEnabled(false);
}

void Browser::showAddButton()
{
    ui->button_add->setEnabled(true);
}

void Browser::showList(std::vector<QListWidgetItem*> items)
{
    if (items.size()>0)
    {
        list.clear();
        for(auto it=items.begin(); it!=items.end(); ++it)
        {
            list.addItem(*it);
        }
        ui->gridLayout->addWidget(&list, 1, 0, 2, 1);
        list.show();
    }
}

void Browser::lock()
{
    ui->button_add->setEnabled(false);
    ui->button_search->setEnabled(false);
    ui->input->setEnabled(false);
}

void Browser::unlock()
{
    ui->button_add->setEnabled(true);
    ui->button_search->setEnabled(true);
    ui->input->setEnabled(true);
}

void Browser::setSelectedItem(QListWidgetItem* item)
{
    setText(item->text());
    list.hide();
    emit suggestion_clicked(item);
}

void Browser::setText(QString text)
{
    ui->input->setText(text);
}
