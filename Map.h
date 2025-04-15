#pragma once 

class Map {
public:
    Map(const std::string& path);
    ~Map() = default;


private:    
    const std::string _path;

};