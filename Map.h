#pragma once 

struct Point {
    long long x;
    long long y;
    char symbol;

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

    virtual void MoveTo(const ConfigurationAction&) = 0;
    virtual void LineTo(const ConfigurationAction&) = 0;
    virtual void HandleSpecialAction() {
        return;
    }
};


class Map : public IMap {
public:
    Map(const std::string& path);
    ~Map() = default;

    void MoveTo(const ConfigurationAction&) override;
    void LineTo(const ConfigurationAction&) override;
    void HandleSpecialAction() override;

private:    
    void ClearPoint(const Point& point);

    const std::string _path;
    std::vector<Point> _point;

};