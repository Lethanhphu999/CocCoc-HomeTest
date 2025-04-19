#pragma once 

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

    friend inline constexpr auto operator<=>(Point, Point) = default;

};

struct ConfigurationAction {
    Point nextPoint;

    ConfigurationAction(const Point& point) :
        nextPoint(point) {

    }

};

class IMap {
public: 
    IMap() = default;
    virtual ~IMap() = default; 

    virtual void init(long long dimention) = 0;
    virtual void print() const = 0;
    void lineTo(const ConfigurationAction&);
    
    virtual void handleSpecialAction() {
        return;
    }

    virtual void moveTo(const ConfigurationAction& configuration)  {
        _currentPoint = configuration.nextPoint;
    }

    virtual Point getCurrentPoint() const {
        return _currentPoint;
    }

protected:
    virtual void clearPoint(const Point&) = 0;
    void Bresenham(const Point& start, const Point& end);
    Point _currentPoint;
    long long _dimension;
};


class Map : public IMap {
public:
    Map();
    ~Map() = default;

    void init(long long size) override;
    void print() const override;
    void handleSpecialAction() override;

protected:
    void clearPoint(const Point&) override;

private:    
    std::vector<Point> _points;

};

#define PointId long long 

struct PointRange {
	PointRange() noexcept = default;
	PointRange(Point from, Point till, long long dimension) noexcept
	: from(from.x + from.y * dimension)
	, till(till.x + till.y * dimension) {
	}

	//friend inline constexpr bool operator==(PointRange, PointRange) = default;

	PointId from;
	PointId till;
};


class SparseMap : public IMap {
public:
    SparseMap();
    ~SparseMap() = default;

    void init(long long dimension) override;
    void print() const override;
    void handleSpecialAction() override;

protected:
    void clearPoint(const Point&) override;

private:
    struct Slice {
        Slice(std::set<Point>&& pts, PointRange r);

        std::set<Point> points;
        PointRange range;

        inline bool operator<(const Slice &other) const {
            return range.from < other.range.from;
        }

    };

    inline long long toPointId(const Point& p) const {
        return p.x + p.y * _dimension;
    }

    bool inRange(const PointRange& range, const Point& pt) const;
    bool contains(const Point& pt) const;

    void mergeSlices(std::vector<Slice>::iterator dst,
        std::vector<Slice>::iterator src);
    void updateRange(PointRange& range, PointId pointId);
    void addNew(const Point& point);

    std::vector<Slice> _slices;

};
