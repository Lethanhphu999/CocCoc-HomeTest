#pragma once

#include <memory>
#include <string>
#include "commands/command_controller.h"

// Forward declarations
class IMap;

/**
 * @brief Main application class that orchestrates the program execution
 * 
 * This class is responsible for initializing components, reading input,
 * executing commands, and managing the application lifecycle.
 */
class Application {
public:
    /**
     * @brief Constructs an Application with the specified input file path
     * @param path Path to the input file
     */
    explicit Application(const std::string& path);
    
    /**
     * @brief Destructor
     */
    ~Application() = default;
    
    /**
     * @brief Executes the application
     * 
     * This is the main entry point for application execution.
     * It reads the input file, processes commands, and displays results.
     */
    void exec();

private:
    /**
     * @brief Initializes the application
     */
    void start();
    
    /**
     * @brief Cleanup and finalization
     */
    void end();

private:
    std::string _path;
    std::unique_ptr<CommandController> _commandController;
    std::shared_ptr<IMap> _map;
};
