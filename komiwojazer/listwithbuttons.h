#ifndef LISTWITHBUTTONS_H
#define LISTWITHBUTTONS_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class ListWithButtons;
}

class ListWithButtons : public QDialog
{
    Q_OBJECT

public:
    explicit ListWithButtons(QWidget *parent = 0);
    ~ListWithButtons();
    void lock();
    void unlock();
    void addItem(QListWidgetItem* item);
    void addItemToBox(QString text, QVariant var);
    bool itemExist(QString name);

private slots:
    void on_button_delete_clicked();

    void on_button_calculate_clicked();

    void on_list_itemClicked(QListWidgetItem *item);

private:
    Ui::ListWithButtons *ui;

signals:
    void btn_delete_click(QListWidgetItem* item);
    void btn_calculate_click(int itemNum);
    void item_clicked(QListWidgetItem* item);
};

#endif // LISTWITHBUTTONS_H
