#pragma once

#include "commands/command.h"

/**
 * @brief Represents the result of an operation
 */
struct Result {
    /**
     * @brief Result type enumeration
     */
    enum class Type {
        Success,
        Error 
    };
    
    Type type;
    std::string message;

    /**
     * @brief Creates a success result
     * @return Result object with Success type
     */
    static Result Success() {
        return { Type::Success, "" };
    }

    /**
     * @brief Creates an error result with message
     * @param msg Error message
     * @return Result object with Error type
     */
    static Result Error(const std::string& msg) {
        return { Type::Error, msg };
    }

    /**
     * @brief Checks if the result is an error
     * @return true if the result is an error, false otherwise
     */
    bool isError() const {
        return type == Type::Error;
    }
};

/**
 * @brief Data structure for file reading results
 */
struct DataReadFile {
    int N;                                  ///< Dimension of the map
    std::vector<Command> commands;          ///< Commands read from file
    Result result;                          ///< Result of the file reading operation
};

/**
 * @brief Namespace for file operations
 */
namespace File {

/**
 * @brief Parses a file and extracts commands
 * @param path Path to the file to parse
 * @return DataReadFile containing the parsed data
 */
DataReadFile parseFile(const std::string& path);

/**
 * @brief Writes data to a file
 * @param path Path to the output file
 * @return Result of the write operation
 */
Result Writefile(const std::string& path);

} // namespace File
