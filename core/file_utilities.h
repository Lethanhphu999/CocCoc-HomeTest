#pragma once

struct Command;

struct Result {
    enum class Type {
        Success,
        Error 
    };
    
    Type type;
    std::string message;

    static Result Success() {
        return { Type::Success, "" };
    }

    static Result Error(const std::string& msg) {
        return { Type::Error, msg };
    }

    bool isError() const {
        return type == Type::Error;
    }

};

struct DataReadFile {
    int N;
    std::vector<Command> commands;
    Result result;
};

namespace File {

DataReadFile parseFile(const std::string &path);
Result Writefile(const std::string& path);

}
