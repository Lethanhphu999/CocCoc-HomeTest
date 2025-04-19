#include "data/map.h"

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

void IMap::lineTo(const ConfigurationAction& configuration) {
    Bresenham(getCurrentPoint(), configuration.nextPoint);
    moveTo(configuration.nextPoint);
}

void Map::init(long long dimension) {
    _dimension = dimension;
    _points.reserve(dimension * dimension);

    for (int y = 0; y < dimension; ++y) {
        for (int x = 0; x < dimension; ++x) {
            _points.emplace_back(x, y);  
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

SparseMap::Slice::Slice(std::set<Point>&& pts, PointRange r)
: points(std::move(pts)),
range(r) {

}

void SparseMap::init(long long dimension) {
    _dimension = dimension;
}

void SparseMap::print() const {
    for (long long y = 0; y < _dimension; ++y) {
        for (long long x = 0; x < _dimension; ++x) {
            if(contains({x,y})) {
                std::cout << '+' << ' '; 
            } else {
                std::cout << '.' << ' '; 
            }
        }
        std::cout << "\n";
    }
}

void SparseMap::handleSpecialAction() {

}

void SparseMap::clearPoint(const Point& point) {
    addNew(point);
}

bool SparseMap::inRange(const PointRange& range, const Point& point) const {
    return range.from <= toPointId(point) && toPointId(point) <= range.till;
}

bool SparseMap::contains(const Point& point) const {
    for (const auto& slice : _slices) {
        if (inRange(slice.range, point)) {
            return true;
        }
    }
    return false;
}

void SparseMap::mergeSlices(std::vector<Slice>::iterator dst,
        std::vector<Slice>::iterator src) {
    dst->points.insert(src->points.begin(), src->points.end());
    updateRange(dst->range, src->range.from);
    updateRange(dst->range, src->range.till);
    _slices.erase(src);
}

void SparseMap::updateRange(PointRange &range, PointId pointId) {
    long long fromId = range.from;
    long long tillId = range.till;

    if (pointId < fromId) {
        range.from = pointId;
    }
    if (pointId > tillId) {
        range.till = pointId;
    }

}

void SparseMap::addNew(const Point& point) {
    long long pointId = toPointId(point); 
    PointRange pointRange(point, point, _dimension);

    auto it = std::lower_bound(_slices.begin(), _slices.end(), pointId,
        [](const Slice& slice, long long id) {
            return slice.range.till < id;
        });

    bool mergedLeft = false;
    bool mergedRight = false;

    if (it != _slices.begin()) {
        auto prev = std::prev(it);
        long long prevTillId = prev->range.till;
        if (prevTillId + 1 == pointId) {
            prev->points.insert(point);
            updateRange(prev->range, toPointId(point));
            mergedLeft = true;
            it = prev;
        }
    }

    if (it != _slices.end()) {
        long long nextFromId = it->range.from;
        if (pointId + 1 == nextFromId) {
            if (mergedLeft) {
                mergeSlices(it - 1, it);
            } else {
                it->points.insert(point);
                updateRange(it->range, toPointId(point));
            }
            mergedRight = true;
        }
    }

    if (!mergedLeft && !mergedRight) {
        std::set<Point> pts{ point };
        _slices.emplace(it, std::move(pts), pointRange);
    }
}
