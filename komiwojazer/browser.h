#ifndef BROWSER_H
#define BROWSER_H

#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>

namespace Ui {
class Browser;
}

/**
 * @brief The Browser class
 * Widget służący do wyszukiwania na podstawie wpisanego tekstu z rozwijaną listą wyników wyszukiwania.
 */
class Browser : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Browser
     * Konstruktor
     * @param parent
     */
    explicit Browser(QWidget *parent = 0);
    /**
     * @brief showAddButton
     * Pokazuje przycisk służący do pokazania przycisku służącego do dodania elementu, którego nazwa
     *  jest wyświetlona w polu tekstowym.
     */
    void showAddButton();
    /**
     * @brief showList
     * Pokazuje listę z wynikami wyszukiwania.
     * @param items lista wyszukanych obiektów.
     */
    void showList(std::vector<QListWidgetItem*> items);
    /**
     * @brief lock
     * Blokuje wszystkie elementy w widget-cie.
     */
    void lock();
    /**
     * @brief unlock
     * Odblokowuje wszystkie elementy w widget-cie.
     */
    void unlock();
    /**
     * @brief setText
     * Wstawia tekst do pola tekstowego.
     * @param text
     */
    void setText(QString text);

    ~Browser();

private slots:
    /**
     * @brief on_button_add_clicked
     * Slot wywoływany po naciśnięciu przycisku dodawania. Wysyła sygnał 'add_button_clicked()'.
     */
    void on_button_add_clicked();
    /**
     * @brief on_button_search_clicked
     * Slot wywoływany po naciśnięciu przycisku wyszukiwania. Wysyła sygnał 'search_button_clicked()'.
     */
    void on_button_search_clicked();
    /**
     * @brief on_input_textEdited
     * Slot wywoływany, gdy rozpocznie się edytowanie w polu tekstowym, blokuje przycisk dodawania.
     * @param arg1
     */
    void on_input_textEdited(const QString &arg1);
    /**
     * @brief setSelectedItem
     * Slot wywoływany po wybraniu elementu z listy z wynikiem wyszukiwania. Wysyła sygnał 'suggestion_clicked()'.
     * @param item
     */
    void setSelectedItem(QListWidgetItem* item);

signals:
    /**
     * @brief add_button_clicked
     * Sygnał informujący o naciśnięciu przycisku dodawania.
     */
    void add_button_clicked();
    /**
     * @brief search_button_clicked
     * Sygnał informujący o naciśnięciu przycisku wyszukiwania. Przekazuje zawartość pola tekstowego.
     * @param text zawartość pola tekstowego
     */
    void search_button_clicked(QString text);
    /**
     * @brief suggestion_clicked
     * Sygnał informujący o wybraniu jednego z wyników wyszukiwania. Przekazuje element z listy wyników wyszukiwania.
     * @param item wybrany element
     */
    void suggestion_clicked(QListWidgetItem* item);


private:
    /**
     * @brief ui
     * Interfejs użytkownika składający się z pola tekstowego, przycisku wyszukiwania i przycisku dodawania.
     */
    Ui::Browser *ui;
    /**
     * @brief list
     * Lista z wynikiem wyszukiwania.
     */
    QListWidget list;
};

#endif // BROWSER_H
