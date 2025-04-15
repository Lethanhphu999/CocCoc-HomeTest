#pragma once 

struct Point {
    long long x;
    long long y;
};

class IMap {
public: 
    IMap() = default;
    virtual ~IMap() = default; 

    virtual void MoveTo() = 0;
    virtual void LineTo() = 0;
    virtual void HandleSpecialAction() {
        return;
    }
};


class Map : public IMap {
public:
    Map(const std::string& path);
    ~Map() = default;

    void MoveTo() override;
    void LineTo() override;
    void HandleSpecialAction() override;

private:    
    const std::string _path;
    std::vector<Point> _point;

};