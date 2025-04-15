#pragma once 

struct Point {
    long long x;
    long long y;
};

class Map {
public:
    Map(const std::string& path);
    ~Map() = default;


private:    
    const std::string _path;

};