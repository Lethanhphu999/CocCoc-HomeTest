#include "data/map.h"

/**
 * @brief Draws a horizontal line on the map
 * @param start Starting point
 * @param end Ending point
 */
void IMap::drawLineH(Point start, Point end) {
    if (start.x > end.x) {
        std::swap(start, end);
    } 
    long long dx = end.x - start.x;
    long long dy = std::abs(end.y - start.y);
    long long yStep = (start.y < end.y) ? 1 : -1;
    long long delta = 2 * dy - dx;

    long long y = start.y;
    for (long long x = start.x; x <= end.x; ++x) {
        clearPoint({x, y});
        if (delta > 0) {
            y += yStep;
            delta -= 2 * dx;
        }
        delta += 2 * dy;
    }
}

/**
 * @brief Draws a vertical line on the map
 * @param start Starting point
 * @param end Ending point
 */
void IMap::drawLineV(Point start, Point end) {
    if (start.y > end.y) {
        std::swap(start, end);
    } 
    long long dx = std::abs(end.x - start.x);
    long long dy = end.y - start.y;
    long long xStep = (start.x < end.x) ? 1 : -1;
    long long delta = 2 * dx - dy;

    long long x = start.x;
    for (long long y = start.y; y <= end.y; ++y) {
        clearPoint({x, y});
        if (delta > 0) {
            x += xStep;
            delta -= 2 * dy;
        }
        delta += 2 * dx;
    }
}

/**
 * @brief Draws a line using Bresenham's algorithm
 * @param start Starting point
 * @param end Ending point
 */
void IMap::drawBresenhamLine(const Point& start, const Point& end) {
    if (std::abs(end.x - start.x) > std::abs(end.y - start.y)) {
        drawLineH(start, end);
    } else {
        drawLineV(start, end);
    }
}

/**
 * @brief Draws a line from current point to the target point
 * @param configuration Configuration containing the target point
 */
void IMap::lineTo(const ConfigurationAction& configuration) {
    drawBresenhamLine(getCurrentPoint(), configuration.nextPoint);
    moveTo(ConfigurationAction(configuration.nextPoint));
}

/**
 * @brief Initializes the map with the given dimension
 * @param dimension Size of the map
 */
void Map::init(long long dimension) {
    _dimension = dimension;
    _points.reserve(dimension * dimension);

    for (long long y = 0; y < dimension; ++y) {
        for (long long x = 0; x < dimension; ++x) {
            _points.emplace_back(x, y);  
        }
    }
}

/**
 * @brief Prints the map to the console
 */
void Map::print() const {
    for (long long y = 0; y < _dimension; ++y) {
        for (long long x = 0; x < _dimension; ++x) {
            std::cout << _points[y * _dimension + x].symbol << ' '; 
        }
        std::cout << "\n";
    }
}

/**
 * @brief Handles special actions on the map
 */
void Map::handleSpecialAction() {
    // Default implementation does nothing
}

/**
 * @brief Clears a point on the map
 * @param point Point to clear
 */
void Map::clearPoint(const Point& point) {
    _points[point.y * _dimension + point.x].symbol = '+';
}

/**
 * @brief Constructor for Slice
 * @param pts Set of points
 * @param r Range of the slice
 */
SparseMap::Slice::Slice(std::set<Point>&& pts, PointRange r)
    : points(std::move(pts))
    , range(r) {
}

/**
 * @brief Initializes the sparse map with the given dimension
 * @param dimension Size of the map
 */
void SparseMap::init(long long dimension) {
    _dimension = dimension;
}

/**
 * @brief Prints the sparse map to the console
 */
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

/**
 * @brief Handles special actions on the sparse map
 */
void SparseMap::handleSpecialAction() {
    // Default implementation does nothing
}

/**
 * @brief Clears a point on the sparse map
 * @param point Point to clear
 */
void SparseMap::clearPoint(const Point& point) {
    addNew(point);
}

/**
 * @brief Checks if a point is in the given range
 * @param range Range to check
 * @param point Point to check
 * @return true if the point is in the range, false otherwise
 */
bool SparseMap::inRange(const PointRange& range, const Point& point) const {
    return range.from <= toPointId(point) && toPointId(point) <= range.till;
}

/**
 * @brief Checks if the map contains a point
 * @param point Point to check
 * @return true if the map contains the point, false otherwise
 */
bool SparseMap::contains(const Point& point) const {
    for (const auto& slice : _slices) {
        if (inRange(slice.range, point)) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Merges two slices
 * @param targetSlice Target slice
 * @param sourceSlice Source slice
 */
void SparseMap::mergeSlices(std::vector<Slice>::iterator targetSlice,
    std::vector<Slice>::iterator sourceSlice) {
    targetSlice->points.insert(sourceSlice->points.begin(), sourceSlice->points.end());
    updateRange(targetSlice->range, sourceSlice->range.from);
    updateRange(targetSlice->range, sourceSlice->range.till);
    _slices.erase(sourceSlice);
}

/**
 * @brief Updates the range of a slice
 * @param range Range to update
 * @param pointId Point ID to include in the range
 */
void SparseMap::updateRange(PointRange& range, PointId pointId) {
    long long fromId = range.from;
    long long tillId = range.till;

    if (pointId < fromId) {
        range.from = pointId;
    }
    if (pointId > tillId) {
        range.till = pointId;
    }
}

/**
 * @brief Adds a new point to the map
 * @param point Point to add
 */
void SparseMap::addNew(const Point& point) {
    long long pointId = toPointId(point); 
    PointRange pointRange(point, point, _dimension);

    auto it = std::lower_bound(_slices.begin(), _slices.end(), pointId,
        [](const Slice& slice, long long id) {
            return slice.range.till < id;
        });

    bool mergedLeft = false;
    bool mergedRight = false;

    if (it != _slices.end()
        && (it->range.from <= pointId
        && pointId <= it->range.till)) {
        return;
    }   

    if (it != _slices.begin()) {
        auto prev = std::prev(it);
        long long prevTillId = prev->range.till;
        if (prevTillId + 1 == pointId) {
            prev->points.insert(point);
            updateRange(prev->range, pointId);
            mergedLeft = true;
        }
    }

    if (it != _slices.end()) {
        long long nextFromId = it->range.from;
        if (pointId + 1 == nextFromId) {
            if (mergedLeft) {
                mergeSlices(it - 1, it);
            } else {
                it->points.insert(point);
                updateRange(it->range, pointId);
            }
            mergedRight = true;
        }
    }

    if (!mergedLeft && !mergedRight) {
        std::set<Point> newPoint{ point };
        _slices.emplace(it, std::move(newPoint), pointRange);
        std::sort(_slices.begin(), _slices.end(), [](const Slice& s1, const Slice& s2) {
            return s1.range.from < s2.range.from;
        });
    }
}
