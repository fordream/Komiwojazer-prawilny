#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include <place.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_progBarDial(new ProgressBarDialog(this))
{
    ui->setupUi(this);
    this->prepareGUI();
    this->selectedPlace = nullptr;
    QMap<int, QString> pluginIndexNameMap;
    pluginManager.loadPlugin(pluginIndexNameMap);
    for(auto e: pluginIndexNameMap.toStdMap())
    {
        this->list.addItemToBox(e.second, QVariant(e.first));
        pluginManager.getPluginByIndex(e.first)->setMap(this);
    }
    placesListChanged = false;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_progBarDial;
    if(v_places.size()>0)
    {
        for(int i = 0; i < (int)v_places.size(); ++i)
        {
            delete[] routes[i];
        }
        delete[] routes;
    }
    m_routesUnorderedMap.clear();
}

void MainWindow::prepareGUI()
{

    this->ui->mapLayout->addWidget(&this->map, 0, 0);
    this->map.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->textEditLog.append("Application log\nApplication started\n");
    this->textEditLog.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    this->ui->controlsLayout->addWidget(&this->browser, 0, 0);
    this->ui->controlsLayout->addWidget(&this->list, 1, 0);
    this->ui->controlsLayout->addWidget(&this->textEditLog, 2, 0);

    this->map.setMapThemeId("earth/openstreetmap/openstreetmap.dgml");
    connect(&this->map, SIGNAL(placeSelected(double,double,QString)), this, SLOT(placeSelected(double,double,QString)));
    connect(&this->browser, SIGNAL(search_button_clicked(QString)), this, SLOT(searchButton_clicked(QString)));
    connect(&this->browser, SIGNAL(add_button_clicked()), this, SLOT(addPlace()));
    connect(&this->browser, SIGNAL(suggestion_clicked(QListWidgetItem*)), this, SLOT(suggestion_clicked(QListWidgetItem*)));
    connect(&this->list, SIGNAL(btn_delete_click(QListWidgetItem*)), this, SLOT(deletePlace(QListWidgetItem*)));
    connect(&this->list, SIGNAL(btn_calculate_click(int)), this, SLOT(calculate(int)));
    connect(&this->list, SIGNAL(item_clicked(QListWidgetItem*)), this, SLOT(place_clicked(QListWidgetItem*)));
}


void MainWindow::suggestion_clicked(QListWidgetItem* item)
{
GeoListItem* geoItem = dynamic_cast<GeoListItem*>(item);
//std::cout<<geoItem->text().toStdString()<<" "<<geoItem->getCoordinates().longitude()<<" "<<geoItem->getCoordinates().latitude()<<std::endl;
this->selectPlace(geoItem->getPlace());
}

void MainWindow::placeSelected(double lon, double lat, QString description)
{
    Place* place=new Place(Coordinates(lon, lat), description);
    browser.setText(description);
    this->selectPlace(place);
}


void MainWindow::searchButton_clicked(QString text)
{
    QVector<Place*> places=this->map.findPlaceByName(text);
    std::vector<QListWidgetItem*> items;
    for(int i=0; i<places.size(); i++)
    {
        QListWidgetItem* item = new GeoListItem(places.at(i));
        items.push_back(item);
        //std::cout<<item->text().toStdString()<<"  "<<item->getCoordinates().longitude()<<"  "<<item->getCoordinates().latitude()<<std::endl;
    }
    browser.showList(items);
}

void MainWindow::addPlace()
{
    std::cout<<"add place  "<<std::endl;
    //GeoListItem* geoItem = dynamic_cast<GeoListItem*>(item);
    //Place* place=geoItem->getPlace();
    //std::cout<<"add place  "<<std::endl;
    if (this->selectedPlace!=nullptr && !list.itemExist(selectedPlace->getName()))
    {
        std::cout<<"no place  "<<std::endl;
        GeoListItem* geoItem = new GeoListItem(this->selectedPlace);
        list.addItem(geoItem);
        //std::cout<<place->getCoordinates().getLat()<<"  "<<place->getCoordinates().getLon()<<std::endl;
        this->map.putMarker(selectedPlace->getCoordinates());
        this->selectedPlace=nullptr;
        placesListChanged = true;
    }
}

void MainWindow::deletePlace(QListWidgetItem* item)
{

    GeoListItem* geoItem = dynamic_cast<GeoListItem*>(item);
    this->map.deleteMarker(geoItem->getPlace()->getCoordinates());
    delete geoItem;
    placesListChanged = true;
}

void MainWindow::calculate(int pluginNum)
{
    lockGUI();
    if (placesListChanged)
    {
        //std::vector<Place*> v_places;
        std::vector<QListWidgetItem*> items = list.getAllItems();
        int size = items.size();
        if(size==0)
        {
            return;
        }
        if(v_places.size()>0)
        {
            for(int i = 0; i < (int)v_places.size(); ++i)
            {
                delete[] routes[i];
            }
            delete[] routes;
        }
        v_places.clear();
        for(int i=0; i<size; i++)
        {
            QListWidgetItem* item = items.at(i);
            GeoListItem* geoItem = dynamic_cast<GeoListItem*>(item);
            v_places.push_back(geoItem->getPlace());
        }
        std::unordered_map<std::pair<Coordinates, Coordinates>, Route, pairhash> unordered_map;
        routes = new Marble::Route*[size];
        for(int i = 0; i < size; ++i)
        {
            routes[i] =  new Marble::Route[size];
            for(int j = 0; j < size; ++j)
            {
                Coordinates from = v_places[i]->getCoordinates();
                Coordinates to = v_places[j]->getCoordinates();
                std::pair<Coordinates, Coordinates> pair = std::make_pair(from, to);
                std::unordered_map<std::pair<Coordinates, Coordinates>, Route, pairhash>::const_iterator got = m_routesUnorderedMap.find(pair);
                Route route;
                if(got == m_routesUnorderedMap.end())
                {
                    route = getRoute(from, to);
                    writeLog(QString("Found route from position %1 to %2").arg(i).arg(j));
                }
                else
                {
                    route = got->second;
                    writeLog(QString("Already have route from position %1 to %2").arg(i).arg(j));
                }

                routes[i][j] = route;
                unordered_map[pair] = route;

            }
        }
        placesListChanged = false;
        m_routesUnorderedMap.clear();
        m_routesUnorderedMap = std::move(unordered_map);
    }
    this->m_progBarDial->show();
    this->m_progBarDial->setProgress(0);
    this->m_progBarDial->update();
    this->m_progBarDial->repaint();
    this->repaint();
    KomiwojazerPluginInterface* interface = pluginManager.getPluginByIndex(pluginNum);
    interface->connectToSLOT(m_progBarDial, SIGNAL(cancelButtonClicked()), true);
    interface->calculate(v_places, routes);
    interface->connectToSLOT(m_progBarDial, SIGNAL(cancelButtonClicked()), true);
    this->m_progBarDial->hide();
    this->m_progBarDial->update();
    this->m_progBarDial->repaint();
    this->repaint();
    setMarkerNumber();
    unlockGUI();
}

void MainWindow::setMarkerNumber()
{
    for(int i=0; i<v_places.size(); i++)
    {
        this->map.putMarker(v_places.at(i)->getCoordinates(), MapWidget::MarkerType::Normal, QString::number(i+1));
    }
}

void MainWindow::selectPlace(Place* p)
{
    if (this->selectedPlace!=nullptr)
    {
        this->map.deleteMarker(this->selectedPlace->getCoordinates());
    }
    this->map.putMarker(p->getCoordinates(), MapWidget::Selected);
    this->selectedPlace = p;
    browser.showAddButton();
    this->map.center(p->getCoordinates());
}

void MainWindow::place_clicked(QListWidgetItem* item)
{
    GeoListItem* geoItem = dynamic_cast<GeoListItem*>(item);
    this->map.center(geoItem->getPlace()->getCoordinates());

}

void MainWindow::setProgress(int value)
{
    m_progBarDial->setProgress(value);
}

Marble::Route MainWindow::getRoute(Coordinates from, Coordinates to)
{
    return this->map.findRoute(from, to);
}

void MainWindow::drawRoute(Marble::Route route)
{
    this->map.drawRoute(route);
}

void MainWindow::drawRoute(std::vector<Route> routes)
{
    this->map.drawRoute(routes);
}

void MainWindow::writeLog(QString text)
{
    this->textEditLog.append(text);
}

void MainWindow::lockGUI()
{
    list.lock();
    browser.lock();
    map.setEnabled(false);
}

void MainWindow::unlockGUI()
{
    list.unlock();
    browser.unlock();
    map.setEnabled(true);
}

