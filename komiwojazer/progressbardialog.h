#ifndef PROGRESSBARDIALOG_H
#define PROGRESSBARDIALOG_H

#include <QDialog>

namespace Ui {
class ProgressBarDialog;
}

/**
 * @brief The ProgressBarDialog class
 * Dialog odpowiadający za informowanie użytkownika o stanie postępu algorytmu
 */
class ProgressBarDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief ProgressBarDialog
     * Konstruktor
     * @param parent Rodzic okna
     */
    explicit ProgressBarDialog(QWidget *parent = 0);
    /**
     * @brief ~ProgressBarDialog
     * Destruktor
     */
    ~ProgressBarDialog();
    /**
     * @brief setProgress
     * Ustawia postęp algorytmu na pasku postępu
     * @param prog Postęp algorytmu z przedziału 0-100
     */
    void setProgress(int prog);
    /**
     * @brief closeEvent
     * Do przechwycenia eventu zamknięcia
     * @param event Event który wywołał funkcję
     */
    void closeEvent(QCloseEvent *event);
signals:
    /**
     * @brief cancelButtonClicked
     * Sygnał oznaczający chęć anulowania dalszego wykonywania algorytmu.
     */
    void cancelButtonClicked();
private:
    Ui::ProgressBarDialog *ui;
};

#endif // PROGRESSBARDIALOG_H
