#ifndef LISTWITHBUTTONS_H
#define LISTWITHBUTTONS_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class ListWithButtons;
}
/**
 * @brief The ListWithButtons class
 * Widget składający się z listy, przycisków "delete" i "calculate" oraz combobox-a do wyoru pluginów.
 */
class ListWithButtons : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief ListWithButtons
     * Konstruktor
     * @param parent
     */
    explicit ListWithButtons(QWidget *parent = 0);
    ~ListWithButtons();
    /**
     * @brief lock
     * Blokuje wszytskie elementy.
     */
    void lock();
    /**
     * @brief unlock
     * Odblokowuje wszystkie elementy.
     */
    void unlock();
    /**
     * @brief addItem
     * Dodaje element do listy.
     * @param item element do dodania
     */
    void addItem(QListWidgetItem* item);
    /**
     * @brief addItemToBox
     * Dodaje element do combobox-a.
     * @param text nazwa, która ma się pojawić w combobox-ie
     * @param var element do dodania
     */
    void addItemToBox(QString text, QVariant var);
    /**
     * @brief itemExist
     * Sprawdza, czy element o podanej nazwie jest na liście.
     * @param name nazwa
     * @return true jeżeli jest, w przeciwnym wypadku - false
     */
    bool itemExist(QString name);
    /**
     * @brief getAllItems
     * Zwraca listę wskaźników do wszystkich elementów z listy.
     * @return lista wskaźników do wszystkich elementów z listy
     */
    std::vector<QListWidgetItem *> getAllItems();
    /**
     * @brief getComboBoxItemNum
     * Zwraca numer wybranego elementu combobox-a
     * @return numer wybranego elementu combobox-a
     */
    int getComboBoxItemNum();

private slots:
    void on_button_delete_clicked();

    void on_button_calculate_clicked();

    void on_list_itemClicked(QListWidgetItem *item);

private:
    Ui::ListWithButtons *ui;

signals:
    /**
     * @brief btn_delete_click
     * Sygnał wysyłany po kliknięcie na przycisk delete.
     * @param item Wskaźnik na aktualnie wybrany element listy.
     */
    void btn_delete_click(QListWidgetItem* item);
    /**
     * @brief btn_calculate_click
     * Sygnał wysyłany po kliknięciu na przycisk calculate.
     * @param itemNum Wskaźnik na aktualnie wybrany element combobox-a
     */
    void btn_calculate_click(int itemNum);
    /**
     * @brief item_clicked
     * Sygnał wysyłany po kliknięciu na element na liście.
     * @param item wskaźnik do wybranego elementu
     */
    void item_clicked(QListWidgetItem* item);
};

#endif // LISTWITHBUTTONS_H
