#include "listwithbuttons.h"
#include "ui_listwithbuttons.h"

ListWithButtons::ListWithButtons(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListWithButtons)
{
    ui->setupUi(this);
}

ListWithButtons::~ListWithButtons()
{
    delete ui;
}

void ListWithButtons::on_button_delete_clicked()
{
    int currentRow = ui->list->currentRow();
    if(currentRow>-1)
    {
        QListWidgetItem* item = ui->list->takeItem(currentRow);
        emit btn_delete_click(item);
    }
}

void ListWithButtons::on_button_calculate_clicked()
{
    emit btn_calculate_click(ui->comboBox->currentIndex());
}

void ListWithButtons::on_list_itemClicked(QListWidgetItem *item)
{
    emit item_clicked(item);
}

void ListWithButtons::lock()
{
    ui->button_calculate->setEnabled(false);
    ui->list->setEnabled(false);
    ui->button_delete->setEnabled(false);
    ui->comboBox->setEnabled(false);
}

void ListWithButtons::unlock()
{
    ui->button_calculate->setEnabled(true);
    ui->list->setEnabled(true);
    ui->button_delete->setEnabled(true);
    ui->comboBox->setEnabled(true);
}

void ListWithButtons::addItem(QListWidgetItem* item)
{
    ui->list->addItem(item);
}

void ListWithButtons::addItemToBox(QString text, QVariant var)
{
    ui->comboBox->addItem(text, var);
}

bool ListWithButtons::itemExist(QString name)
{
    return 0!=ui->list->findItems(name, Qt::MatchExactly).size();
}

std::vector<QListWidgetItem*> ListWithButtons::getAllItems()
{
    std::vector<QListWidgetItem*> items;
    for(int i=0; i<ui->list->count(); i++)
    {
        QListWidgetItem* item = ui->list->item(i);
        items.push_back(item);
    }
    return items;
}

int ListWithButtons::getComboBoxItemNum()
{
    return ui->comboBox->currentIndex();
}
