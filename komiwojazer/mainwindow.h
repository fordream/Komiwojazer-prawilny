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

class MainWindow : public QMainWindow, public AppInterface
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
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

public:
    virtual Route getRoute(Coordinates from, Coordinates to);
    virtual void drawRoute(std::vector<Route> routes);
    virtual void drawRoute(Marble::Route route);
    virtual void writeLog(QString text);

public slots:
    virtual void setProgress(int value);
    void placeSelected(double, double, QString);
    void addPlace();
    void deletePlace(QListWidgetItem *);
    void calculate(int pluginNum);
    void place_clicked(QListWidgetItem*);
    void suggestion_clicked(QListWidgetItem* item);
    void searchButton_clicked(QString text);

signals:
    void routeFoundSignal(Marble::Route* route);
};

#endif // MAINWINDOW_H
