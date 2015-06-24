#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"

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

    /*michal ppk settings and testing*
    RoutingManager *const routingManager = map.model()->routingManager();
    routingManager->readSettings();
    //bool const startupWarning = settings.value( "showGuidanceModeStartupWarning", QVariant( true ) ).toBool();
    //routingManager->setShowGuidanceModeStartupWarning( startupWarning );

    QColor tempColor;
    tempColor = QColor(Oxygen::skyBlue4.name());
    tempColor.setAlpha(200);
    routingManager->setRouteColorStandard( tempColor );

    tempColor = QColor(Oxygen::skyBlue1.name());
    tempColor.setAlpha(200);
    routingManager->setRouteColorHighlighted( tempColor );

    tempColor = QColor(Oxygen::aluminumGray4.name());
    tempColor.setAlpha(200);
    routingManager->setRouteColorAlternative( tempColor );

    // Access the shared route request (start, destination and parameters)
    RoutingManager* manager = map.model()->routingManager();
    RouteRequest* request = manager->routeRequest();

    // Use default routing settings for cars
    request->setRoutingProfile( manager->defaultProfile( RoutingProfile::Motorcar ) );

    // Set start and destination
    request->append( GeoDataCoordinates( 8.38942, 48.99738, 0.0, GeoDataCoordinates::Degree ) );
    request->append( GeoDataCoordinates( 8.42002, 49.0058, 0.0, GeoDataCoordinates::Degree ) );

    // Calculate the route
    manager->retrieveRoute();

    // Center the map on the route start point and show it
    map.centerOn( request->at( 0 ) );
    map.setDistance( 0.75 );
    map.show();
    /*michal ppk*/
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_progBarDial;
}

void MainWindow::prepareGUI()
{

    this->ui->mapLayout->addWidget(&this->map, 0, 0);
    this->map.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->ui->mapLayout->addWidget(&this->textEditLog, 1, 0);
    this->ui->mapLayout->setRowMinimumHeight(0, 500);
    this->ui->mapLayout->setRowMinimumHeight(1, 100);
    this->ui->mapLayout->setRowStretch(0, 1);
    this->ui->mapLayout->setRowStretch(1, 0);
    this->textEditLog.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->controlsLayout.setSpacing(5);
    this->controlsLayout.addWidget(&this->browser, 0, 1);
    this->controlsLayout.addWidget(&this->list, 1, 0);
    this->ui->mapLayout->addLayout(&this->controlsLayout, 0, 0);

    this->map.setMapThemeId("earth/openstreetmap/openstreetmap.dgml");
    connect(&this->map, SIGNAL(placeSelected(double,double,QString)), this, SLOT(placeSelected(double,double,QString)));
    connect(&this->browser, SIGNAL(search_button_clicked(QString)), this, SLOT(searchButton_clicked(QString)));
    connect(&this->browser, SIGNAL(add_button_clicked(QListWidgetItem*)), this, SLOT(addPlace(QListWidgetItem*)));
    connect(&this->browser, SIGNAL(suggestion_clicked(QListWidgetItem*)), this, SLOT(suggestion_clicked(QListWidgetItem*)));
    connect(&this->list, SIGNAL(btn_delete_click(QListWidgetItem*)), this, SLOT(deletePlace(QListWidgetItem*)));
    connect(&this->list, SIGNAL(btn_calculate_click(int)), this, SLOT(calculate(int)));
    connect(&this->list, SIGNAL(item_clicked(QListWidgetItem*)), this, SLOT(place_clicked(QListWidgetItem*)));
    connect(this->map.model()->routingManager(), SIGNAL(routeRetrieved(GeoDataDocument*)), this, SLOT(routeRetrivedSlot(GeoDataDocument*)));
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
    GeoListItem* item = new GeoListItem(place);
    browser.setItem(item);
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

void MainWindow::addPlace(QListWidgetItem* item)
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
    }
}

void MainWindow::deletePlace(QListWidgetItem* item)
{

    GeoListItem* geoItem = dynamic_cast<GeoListItem*>(item);
    this->map.deleteMarker(geoItem->getPlace()->getCoordinates());
    delete geoItem;
}

void MainWindow::calculate(int pluginNum)
{
    //this->map.findRoute(Coordinates(0, 0), Coordinates(0,0));
//    lockGUI();
//    this->m_progBarDial->show();
//    KomiwojazerPluginInterface* interface = pluginManager.getPluginByIndex(methodsBox.currentIndex());
//    QMetaObject::Connection connectionProgresBar = QObject::connect(dynamic_cast<QObject*>(interface), SIGNAL(setProgress(int)), this, SLOT(setProgress(int)));
//    QMetaObject::Connection connection = QObject::connect(m_progBarDial, SIGNAL(cancelButtonClicked()),
//                    dynamic_cast<QObject*>(interface), SLOT(cancel()));
//    std::vector<Place*> v_places;
//    for(int i=0; i<this->placesList.count(); i++)
//    {
//        QListWidgetItem* item = this->placesList.item(i);
//        GeoListItem* geoItem = dynamic_cast<GeoListItem*>(item);
//        v_places.push_back(geoItem->getPlace());
//    }
//    interface->calculate(v_places);
//    QObject::disconnect(connection);
//    QObject::disconnect(connectionProgresBar);
//    //pobierz plugin, podepnij sygnaly i sloty (cancel i set progress)
//    this->m_progBarDial->hide();
//    unlockGUI();
}

//void MainWindow::calculate()
//{
//    lockGUI();
//    this->m_progBarDial->show();
//    KomiwojazerPluginInterface* interface = pluginManager.getPluginByIndex(methodsBox.currentIndex());
//    interface->connectToSLOT(m_progBarDial, SIGNAL(cancelButtonClicked()), true);
//    //QMetaObject::Connection connection = QObject::connect(m_progBarDial, SIGNAL(cancelButtonClicked()),
//    //                qobject_cast<QObject*>(interface), SLOT(cancel()));
//    std::vector<Place*> v_places;
//    for(int i=0; i<this->placesList.count(); i++)
//    {
//        QListWidgetItem* item = this->placesList.item(i);
//        GeoListItem* geoItem = dynamic_cast<GeoListItem*>(item);
//        v_places.push_back(geoItem->getPlace());
//    }
//    interface->connectToSLOT(m_progBarDial, SIGNAL(cancelButtonClicked()), false);
//    interface->calculate(v_places);
//    //QObject::disconnect(connection);
//    //pobierz plugin, podepnij sygnaly i sloty (cancel i set progress)
//    this->m_progBarDial->hide();
//    unlockGUI();
//}

void MainWindow::selectPlace(Place* p)
{
    if (this->selectedPlace!=nullptr)
    {
        this->map.deleteMarker(this->selectedPlace->getCoordinates());
    }
    this->map.putMarker(p->getCoordinates(), MapWidget::Selected);
    delete this->selectedPlace;
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

void MainWindow::routeRetrivedSlot(GeoDataDocument* doc)
{
    Route route = this->map.model()->routingManager()->routingModel()->route();
    emit routeFoundSignal(&route);
}
