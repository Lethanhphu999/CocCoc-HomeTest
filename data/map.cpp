#include "data/map.h"


void IMap::lineTo(const ConfigurationAction& configuration) {
    Bresenham(getCurrentPoint(), configuration.nextPoint);
    moveTo(configuration.nextPoint);
}

void IMap::Bresenham(const Point& start, const Point& end) {
    long long x0 = start.x;
    long long y0 = start.y;
    long long x1 = end.x;
    long long y1 = end.y;

    long long dx = std::abs(x1 - x0);
    long long dy = std::abs(y1 - y0);
    long long sx = (x0 < x1) ? 1 : -1;
    long long sy = (y0 < y1) ? 1 : -1;
    long long err = dx - dy;

    while (true) {
        clearPoint({x0, y0});  

        if (x0 == x1 && y0 == y1) break;

        long long e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }

}

Map::Map() {
    
}

void Map::init(long long dimension) {
    _dimension = dimension;
    _points.reserve(dimension * dimension);

    for (int y = 0; y < dimension; ++y) {
        for (int x = 0; x < dimension; ++x) {
            _points.emplace_back(y, x);  
        }
    }
}

void Map::print() const {
    for (int y = 0; y < _dimension; ++y) {
        for (int x = 0; x < _dimension; ++x) {
            std::cout << _points[y * _dimension + x].symbol << ' '; 
        }
        std::cout << "\n";
    }

}


void Map::handleSpecialAction() {

}

void Map::clearPoint(const Point& point) {
    _points[point.y * _dimension + point.x].symbol = '+';
}

