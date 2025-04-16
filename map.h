#pragma once 

struct Point {
    long long x;
    long long y;
    char symbol;

    Point() : x(0), y(0), symbol('.') {}

    Point& operator+(const Point& other) {
        this->x = this->x + other.x;
        this->y = this->y + other.y;
        
        return *this;
    } 

    Point& operator-(const Point& other) {
        this->x = this->x - other.x;
        this->y = this->y - other.y;
        
        return *this;
    }

};

struct ConfigurationAction {
    Point p;

    ConfigurationAction(Point&& point) :
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
    std::vector<Point> _point;
    Point _currentPoint;
};