#pragma once 

/**
 * @brief Represents a 2D point with x and y coordinates
 */
struct Point {
    long long x;
    long long y;
    char symbol = '.';

    Point() : x(0), y(0) {}
    Point(long long x_, long long y_) : x(x_), y(y_) {}

    Point(const Point&) = default;
    Point(Point&&) = default;
    Point& operator=(const Point&) = default;
    Point& operator=(Point&&) = default;

    // C++20 spaceship operator
    auto operator<=>(const Point& other) const = default;
};

/**
 * @brief Configuration for map actions
 */
struct ConfigurationAction {
    Point nextPoint;

    explicit ConfigurationAction(const Point& point) : nextPoint(point) {}
};

/**
 * @brief Interface for map operations
 */
class IMap {
public: 
    IMap() = default;
    virtual ~IMap() = default; 

    virtual void init(long long dimension) = 0;
    virtual void print() const = 0;
    void lineTo(const ConfigurationAction&);
    
    virtual void handleSpecialAction() {
        return;
    }

    virtual void moveTo(const ConfigurationAction& configuration) {
        _currentPoint = configuration.nextPoint;
    }

    virtual Point getCurrentPoint() const {
        return _currentPoint;
    }

protected:
    virtual void clearPoint(const Point&) = 0;
    void drawLineV(Point start, Point end);
    void drawLineH(Point start, Point end);
    void drawBresenhamLine(const Point& start, const Point& end);
    Point _currentPoint;
    long long _dimension;
};

/**
 * @brief Simple map implementation using a vector of points
 */
class Map : public IMap {
public:
    Map() = default;
    ~Map() override = default;

    void init(long long size) override;
    void print() const override;
    void handleSpecialAction() override;

protected:
    void clearPoint(const Point&) override;

private:    
    std::vector<Point> _points;
};

/**
 * @brief Type alias for point ID
 */
using PointId = long long;

/**
 * @brief Represents a range of points
 */
struct PointRange {
    PointRange() noexcept = default;
    PointRange(Point from, Point till, long long dimension) noexcept
        : from(from.x + from.y * dimension)
        , till(till.x + till.y * dimension) {
    }

    auto operator<=>(const PointRange& other) const = default;

    PointId from;
    PointId till;
};

/**
 * @brief Sparse map implementation using slices
 */
class SparseMap : public IMap {
public:
    SparseMap() = default;
    ~SparseMap() override = default;

    void init(long long dimension) override;
    void print() const override;
    void handleSpecialAction() override;

protected:
    void clearPoint(const Point&) override;

private:
    /**
     * @brief Represents a slice of points in the map
     */
    struct Slice {
        Slice(std::set<Point>&& pts, PointRange r);

        std::set<Point> points;
        PointRange range;

        bool operator<(const Slice& other) const {
            return range.from < other.range.from;
        }
    };

    long long toPointId(const Point& p) const {
        return p.x + p.y * _dimension;
    }

    bool inRange(const PointRange& range, const Point& pt) const;
    bool contains(const Point& pt) const;

    void mergeSlices(std::vector<Slice>::iterator targetSlice,
        std::vector<Slice>::iterator sourceSlice);
    void updateRange(PointRange& range, PointId pointId);
    void addNew(const Point& point);

    std::vector<Slice> _slices;
};

/**
 * @brief Template for map operations
 * @tparam MapType Type of map to operate on
 */
template<typename MapType>
class MapOperations {
public:
    static void drawLine(MapType& map, const Point& start, const Point& end) {
        map.drawBresenhamLine(start, end);
    }

    static void moveTo(MapType& map, const Point& point) {
        map.moveTo(ConfigurationAction(point));
    }

    static void clearPoint(MapType& map, const Point& point) {
        map.clearPoint(point);
    }
};

/**
 * @brief Template for point operations
 * @tparam T Type for calculations
 */
template<typename T>
class PointOperations {
public:
    static T distance(const Point& p1, const Point& p2) {
        return static_cast<T>(std::sqrt(
            std::pow(p2.x - p1.x, 2) + 
            std::pow(p2.y - p1.y, 2)
        ));
    }

    static bool isInRange(const Point& p, const Point& min, const Point& max) {
        return p.x >= min.x && p.x <= max.x && 
               p.y >= min.y && p.y <= max.y;
    }

    static Point interpolate(const Point& p1, const Point& p2, T t) {
        return Point(
            static_cast<long long>(p1.x + (p2.x - p1.x) * t),
            static_cast<long long>(p1.y + (p2.y - p1.y) * t)
        );
    }
};
