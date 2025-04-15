#pragma once 

class CommandController {
public:
    CommandController(const std::string& path);
    ~CommandController() = default;
    

private:    
    const std::string _path;

};