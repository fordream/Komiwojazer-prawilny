#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "komi_main_lib.h"
#include <QMainWindow>
#include <mapwidget.h>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QVector>
#include <geolistitem.h>
#include <qcombobox.h>
#include <coordinates.h>
#include <place.h>
#include <marble/Route.h>
#include <appinterface.h>
#include <komipluginmanager.h>
#include "progressbardialog.h"
#include <QTextEdit>
#include <QGridLayout>
#include <listwithbuttons.h>
#include<browser.h>
#include <QTextBrowser>

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 * Główne okno aplikacji
 */
class MainWindow : public QMainWindow, public AppInterface
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow
     * Konstruktor
     * @param parent rodzic
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * @brief ~MainWindow
     * Destruktor
     */
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MapWidget map;
    QTextBrowser textEditLog;
    QGridLayout controlsLayout;
    ListWithButtons list;
    Browser browser;
    void prepareGUI();
    Place *selectedPlace;
    void selectPlace(Place *p);
    bool checkIfItemAdded(QString text);
    KomiPluginManager pluginManager;
    ProgressBarDialog* m_progBarDial;
    void lockGUI();
    void unlockGUI();
    bool placesListChanged;
    std::vector<Place*> v_places;
    Marble::Route** routes;

public:
    /**
     * @brief getRoute
     * Znajduje drogę pomiędzy dwoma punktami na mapie
     * @param from Miejsce startowe
     * @param to Miejsce docelowe
     * @returns Znaleziona droga
     */
    virtual Route getRoute(Coordinates from, Coordinates to);
    /**
     * @brief drawRoute
     * Rysuje drogi na mapie.
     * @param routes Wektor dróg do narysowania
     */
    virtual void drawRoute(std::vector<Route> routes);
    /**
     * @brief drawRoute
     * Rysuje pojedyńczą drogę na mapie
     * @param route Droga do narysowania
     */
    virtual void drawRoute(Marble::Route route);
    /**
     * @brief writeLog
     * Zapisuje wiadomość w logu aplikacji
     * @param text Wiadomość do wyświetlenia
     */
    virtual void writeLog(QString text);

public slots:
    /**
     * @brief setProgress
     * Przekazuje aktualny postęp algorytmu do okna dialogowego
     * @param value Aktualny stan postępu algorytmu
     */
    virtual void setProgress(int value);
    /**
     * @brief placeSelected
     * Wstawia wybrane miejsce
     * @param double Długość geograficzna
     * @param double Długość geograficzna
     * @param double Szerokość geograficzna
     * @param QString Nazwa miejsca
     */
    void placeSelected(double, double, QString);
    /**
     * @brief addPlace
     * Dodaje aktualnie zaznaczone miejsce
     */
    void addPlace();
    /**
     * @brief deletePlace
     * Usuwa miejsce z listy
     * @param QListWidgetItem Miejsce do usunięcia
     */
    void deletePlace(QListWidgetItem *);
    /**
     * @brief calculate
     * Główna funkcja obliczeniowa. Pobiera odpowiedni plugin na podstawie jego ID z plugin manager, przygotowuje trasy i uruchamia algorytm obliczeniowy pluginu
     * @param pluginNum Id pluginu na piście pluginów
     */
    void calculate(int pluginNum);
    /**
     * @brief place_clicked
     * Podświetla wybrane miejsce
     * @param QListWidgetItem Wybrane miejsce
     */
    void place_clicked(QListWidgetItem*);
    /**
     * @brief suggestion_clicked
     * @param item Wybrany element
     */
    void suggestion_clicked(QListWidgetItem* item);
    /**
     * @brief searchButton_clicked
     * Wyszukuje miejsce wpisane w wyszukiwarce
     * @param text Nazwa miejsca do wyszukania
     */
    void searchButton_clicked(QString text);

signals:
    /**
     * @brief routeFoundSignal
     * Sygnał informujący o znalezieniu drogi
     * @param Znaleziona droga
     */
    void routeFoundSignal(Marble::Route* route);
};

#endif // MAINWINDOW_H
