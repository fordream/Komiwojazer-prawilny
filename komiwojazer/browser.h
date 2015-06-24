#ifndef BROWSER_H
#define BROWSER_H

#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>

namespace Ui {
class Browser;
}

class Browser : public QDialog
{
    Q_OBJECT

public:
    explicit Browser(QWidget *parent = 0);
    void showAddButton();
    void showList(std::vector<QListWidgetItem*> items);
    void lock();
    void unlock();
    void setItem(QListWidgetItem* item);
    ~Browser();

private slots:
    void on_button_add_clicked();

    void on_button_search_clicked();

    void on_input_textEdited(const QString &arg1);

    void setSelectedItem(QListWidgetItem* item);

signals:
    void add_button_clicked(QListWidgetItem* item);
    void search_button_clicked(QString text);
    void suggestion_clicked(QListWidgetItem* item);


private:
    Ui::Browser *ui;
    QListWidget list;
    QListWidgetItem* selectedItem;
};

#endif // BROWSER_H
