#include "browser.h"
#include "ui_browser.h"
#include <geolistitem.h>

Browser::Browser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Browser)
{
    ui->setupUi(this);
    ui->button_add->hide();
    selectedItem = nullptr;
    connect(&list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(setSelectedItem(QListWidgetItem*)));
}

Browser::~Browser()
{
    delete ui;
}

void Browser::on_button_add_clicked()
{
    if(selectedItem!=nullptr)
    {
        emit add_button_clicked(selectedItem);
    }
    selectedItem = nullptr;
}

void Browser::on_button_search_clicked()
{
    emit search_button_clicked(ui->input->text());
}

void Browser::on_input_textEdited(const QString &arg1)
{
    ui->button_add->hide();
}

void Browser::showAddButton()
{
    ui->button_add->show();
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
    setItem(item);
    list.hide();
    emit suggestion_clicked(item);
}

void Browser::setItem(QListWidgetItem* item)
{
    ui->input->setText(item->text());
    selectedItem = item;
}
