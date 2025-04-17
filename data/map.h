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

    Point operator+(const Point& other) const {
        return {x + other.x, y + other.y};
    }

    Point operator-(const Point& other) const {
        return {x - other.x, y - other.y};
    }

};

struct ConfigurationAction {
    Point p;

    ConfigurationAction(const Point& point) :
        p(point) {

    }

};

class IMap {
public: 
    IMap() = default;
    virtual ~IMap() = default; 

    virtual void moveTo(const ConfigurationAction&) = 0;
    virtual void lineTo(const ConfigurationAction&) = 0;
    virtual void handleSpecialAction() {
        return;
    }
};


class Map : public IMap {
public:
    Map(const std::string& path);
    ~Map() = default;

    void moveTo(const ConfigurationAction&) override;
    void lineTo(const ConfigurationAction&) override;
    void handleSpecialAction() override;

private:    
    void clearPoint(const Point& point);

    const std::string _path;
    std::vector<Point> _points;
    Point _currentPoint;
};