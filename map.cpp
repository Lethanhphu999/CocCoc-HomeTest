#include "map.h"

Map::Map(const std::string& path)
: _path(path) {
    
}


void Map::moveTo(const ConfigurationAction& configurationAction) {
    _currentPoint = configurationAction.p;
}

void Map::lineTo(const ConfigurationAction& configurationAction) {

}

void Map::handleSpecialAction() {

}

void Map::clearPoint(const Point& point) {

}

