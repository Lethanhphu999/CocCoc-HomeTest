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