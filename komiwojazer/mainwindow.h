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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public AppInterface
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MapWidget map;
    QPushButton searchButton;
    QLineEdit searchInput;
    QListWidget suggestionsList;
    QPushButton addPlaceButton;
    QListWidget placesList;
    QPushButton deleteButton;
    QPushButton calculateButton;
    QComboBox methodsBox;
    QPushButton hideList;
    QPushButton showList;
    QTextEdit textEditLog;
    void prepareGUI();
    Place *selectedPlace;
    void selectPlace(Place *p);
    bool checkIfItemAdded(QString text);
    KomiPluginManager pluginManager;
    ProgressBarDialog* m_progBarDial;
    void lockGUI();
    void unlockGUI();

public:
    virtual Marble::Route getRoute(Coordinates from, Coordinates to);
    virtual void drawRoute(Marble::Route route);
    virtual void writeLog(QString text);

public slots:
    virtual void setProgress(int value);
    void placeSelected(double, double, QString);
    void searchButton_clicked();
    void suggestion_clicked(QListWidgetItem* item);
    void showZoom(int);
    void addPlace();
    void deletePlace();
    void hideListWithButtons();
    void showListWithButtons();
    void calculate();
    void place_clicked(QListWidgetItem*);
};

#endif // MAINWINDOW_H
