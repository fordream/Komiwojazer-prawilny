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
            methodsBox.addItem(e.second, QVariant(e.first));
        }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_progBarDial;
}

void MainWindow::prepareGUI()
{
    this->map.setParent(this);
    this->map.resize(800, 600);
    this->searchInput.setParent(this);
    this->searchInput.move(190, 20);
    this->searchInput.resize(400, 30);
    this->searchButton.setParent(this);
    this->searchButton.move(590, 20);
    this->searchButton.resize(30, 30);
    QIcon loupIcon(":/images/loupe.png");
    this->searchButton.setIcon(loupIcon);
    this->map.setMapThemeId("earth/openstreetmap/openstreetmap.dgml");

    this->suggestionsList.setParent(this);
    this->suggestionsList.resize(400, 200);
    this->suggestionsList.move(190, 50);
    this->suggestionsList.hide();

    this->addPlaceButton.setParent(this);
    this->addPlaceButton.resize(400, 30);
    this->addPlaceButton.move(190, 50);
    this->addPlaceButton.setText("Add");
    this->addPlaceButton.hide();

    this->placesList.setParent(this);
    this->placesList.resize(200, 300);
    this->placesList.move(0, 200);
    this->deleteButton.setParent(this);
    this->deleteButton.resize(200, 30);
    this->deleteButton.move(0, 500);
    this->deleteButton.setText("Delete");
    this->calculateButton.setParent(this);
    this->calculateButton.resize(200, 30);
    this->calculateButton.move(0, 530);
    this->calculateButton.setText("Calculate");
    this->methodsBox.setParent(this);
    this->methodsBox.resize(200, 30);
    this->methodsBox.move(0, 560);
    this->hideList.setParent(this);
    this->hideList.resize(30, 30);
    this->hideList.move(200, 200);
    this->hideList.setText("-");
    this->showList.setText("+");
    this->showList.setParent(this);
    this->showList.resize(30, 30);
    this->showList.move(0, 200);
    this->showList.hide();

    connect(&this->map, SIGNAL(placeSelected(double,double,QString)), this, SLOT(placeSelected(double,double,QString)));
    connect(&this->searchButton, SIGNAL(clicked()), this, SLOT(searchButton_clicked()));
    connect(&this->suggestionsList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(suggestion_clicked(QListWidgetItem*)));
    connect(&this->searchInput, SIGNAL(textEdited(QString)), &this->addPlaceButton, SLOT(hide()));
    connect(&this->addPlaceButton, SIGNAL(clicked()), this, SLOT(addPlace()));
    connect(&this->deleteButton, SIGNAL(clicked()), this, SLOT(deletePlace()));
    connect(&this->calculateButton, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(&this->hideList, SIGNAL(clicked()), this, SLOT(hideListWithButtons()));
    connect(&this->showList, SIGNAL(clicked()), this, SLOT(showListWithButtons()));
    connect(&this->placesList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(place_clicked(QListWidgetItem*)));

    connect(&this->map, SIGNAL(zoomChanged(int)), this, SLOT(showZoom(int)));
}

void MainWindow::placeSelected(double lon, double lat, QString description)
{
    this->searchInput.setText(description);
    Place* place=new Place(Coordinates(lon, lat), description);
    this->selectPlace(place);
}

void MainWindow::searchButton_clicked()
{
    this->suggestionsList.clear();
    QVector<Place*> places=this->map.findPlaceByName(this->searchInput.text());
    for(int i=0; i<places.size(); i++)
    {
        GeoListItem* item = new GeoListItem(places.at(i));
        this->suggestionsList.addItem(item);
        //std::cout<<item->text().toStdString()<<"  "<<item->getCoordinates().longitude()<<"  "<<item->getCoordinates().latitude()<<std::endl;

    }
    if(places.size()>0)
    {
        this->suggestionsList.show();
    }
}

void MainWindow::suggestion_clicked(QListWidgetItem* item)
{
    GeoListItem* geoItem = dynamic_cast<GeoListItem*>(item);
    this->searchInput.setText(geoItem->text());
    this->suggestionsList.hide();
    //std::cout<<geoItem->text().toStdString()<<"  "<<geoItem->getCoordinates().longitude()<<"  "<<geoItem->getCoordinates().latitude()<<std::endl;
    this->selectPlace(geoItem->getPlace());
}


void MainWindow::showZoom(int zoom)
{
    std::cout<<"zoom:  "<<zoom<<std::endl;
}

void MainWindow::addPlace()
{
    std::cout<<"add place  "<<std::endl;
    if (this->selectedPlace!=nullptr && 0==this->placesList.findItems(this->selectedPlace->getName(), Qt::MatchExactly).size())
    {
        std::cout<<"no place  "<<std::endl;
        GeoListItem* item=new GeoListItem(this->selectedPlace);
        this->placesList.addItem(item);
        std::cout<<item->getPlace()->getCoordinates().getLat()<<"  "<<item->getPlace()->getCoordinates().getLon()<<std::endl;
        this->map.putMarker(this->selectedPlace->getCoordinates());
        this->selectedPlace=nullptr;
    }
}

void MainWindow::deletePlace()
{
    int currentRow = this->placesList.currentRow();
    if(currentRow > -1)
    {
        GeoListItem* item=dynamic_cast<GeoListItem*>(this->placesList.takeItem(currentRow));
        this->map.deleteMarker(item->getPlace()->getCoordinates());
        delete item;
    }
}

void MainWindow::hideListWithButtons()
{
    this->placesList.hide();
    this->deleteButton.hide();
    this->calculateButton.hide();
    this->methodsBox.hide();
    this->hideList.hide();
    this->showList.show();
}

void MainWindow::showListWithButtons()
{
    this->placesList.show();
    this->deleteButton.show();
    this->calculateButton.show();
    this->methodsBox.show();
    this->hideList.show();
    this->showList.hide();
}

void MainWindow::calculate()
{
    lockGUI();
    this->m_progBarDial->show();
    KomiwojazerPluginInterface* inteface = pluginManager.getPluginByIndex(methodsBox.currentIndex());
    QMetaObject::Connection connectionProgresBar = QObject::connect(plugin, SIGNAL(setProgress(int)), this, SLOT(setProgress(int)));
    QMetaObject::Connection connection = QObject::connect(m_progBarDial, SIGNAL(cancelButtonClicked()),
                    dynamic_cast<QObject*>(inteface), SLOT(cancel()));
    std::vector<Place> v_places;
    for(int i=0; i<this->placesList.size(); i++)
    {
        QListWidgetItem* item = this->placesList.item(i);
        GeoListItem* geoItem = dynamic_cast<GeoListItem*>(item);
        v_places.push_back(geoItem->getPlace());
    }
    inteface->calculate(v_places);
    QObject::disconnect(connection);
    QObject::disconnect(connectionProgresBar);
    //pobierz plugin, podepnij sygnaly i sloty (cancel i set progress)
    this->m_progBarDial->hide();
    unlockGUI();
}

void MainWindow::selectPlace(Place* p)
{
    if (this->selectedPlace!=nullptr)
    {
        this->map.deleteMarker(this->selectedPlace->getCoordinates());
    }
    this->map.putMarker(p->getCoordinates(), MapWidget::Selected);
    delete this->selectedPlace;
    this->selectedPlace = p;
    this->addPlaceButton.show();
    //this->map.center(p->getCoordinates());
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
    return Marble::Route();
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
    //michal ppk todo
}

void MainWindow::unlockGUI()
{
    //michal ppk todo
}
