#include "core/file_utilities.h"
#include "data/map.h"
#include "commands/command.h"

// Forward declarations
struct Point;
enum class TypeCommand;

namespace {

/**
 * @brief Map of command keywords to their corresponding TypeCommand values
 */
const std::unordered_map<std::string, TypeCommand> kKeywordCommandMap = {
    {"MOVE_TO", TypeCommand::MOVE_TO},
    {"LINE_TO", TypeCommand::LINE_TO},
    {"SPECIAL", TypeCommand::SPECIAL}
};

/**
 * @brief Creates a regex pattern for command matching
 * @return String containing the regex pattern for commands
 */
const std::string chainCommand() {
    std::string result;
    bool firstCmd = true;
    for (const auto& [cmd, _] : kKeywordCommandMap) {
        if (!firstCmd) {
            result += "|";
        }
        result += cmd;
        firstCmd = false;
    }

    return result;
}

} // namespace

namespace File {

DataReadFile parseFile(const std::string& path) {
    std::ifstream file(path);
    DataReadFile data;
    
#ifdef DEBUG
    std::cout << "Current working directory: " 
              << std::filesystem::current_path() << std::endl;
#endif
    
    if (!file.is_open()) {
        data.result = Result::Error("Cannot open file: " + path);
        return data;
    }

    // Compile regex patterns once
    const std::regex regexDimension(R"(^DIMENSION\s(\d+)$)");
    const std::regex regexCommand("^(" + chainCommand() + R"()\s(\d+),(\d+)$)");
    std::smatch match;

    int lineNumber = 1;
    std::string line;
    std::vector<std::string> errors;
    
    // Process each line
    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) {
            ++lineNumber;
            continue;
        }
        
        // Parse dimension (first line)
        if (std::regex_match(line, match, regexDimension) || lineNumber == 1) {
            try {
                data.N = std::stoll(match[1]);
                if (data.N <= 0) {
                    errors.push_back("Dimension must be positive at line " + std::to_string(lineNumber));
                }
            } catch (const std::exception& e) {
                errors.push_back("Invalid dimension at line " + std::to_string(lineNumber) + ": " + line);
            }
        } 
        // Parse command
        else if (std::regex_match(line, match, regexCommand)) {
            const std::string& cmd = match[1];
            try {
                const long long x = std::stoll(match[2]);
                const long long y = std::stoll(match[3]);
    
                auto it = kKeywordCommandMap.find(cmd);
                if (it != kKeywordCommandMap.end()) {
                    if (0 <= x && x < data.N && 0 <= y && y < data.N) {
                        data.commands.push_back({it->second, {x, y}});
                    } else {
                        errors.push_back("Coordinates out of bounds at line " + std::to_string(lineNumber) + 
                                        ": " + cmd + " " + std::to_string(x) + "," + std::to_string(y));
                    }
                } else {
                    errors.push_back("Invalid command keyword at line " + std::to_string(lineNumber) + ": " + cmd);
                }
            } catch (const std::exception& e) {
                errors.push_back("Failed to parse coordinates at line " + std::to_string(lineNumber));
            }
        } else {
            errors.push_back("Invalid format at line " + std::to_string(lineNumber) + ": " + line);
        }
    
        ++lineNumber;
    }

    // Check for empty file
    if (lineNumber == 1) {
        errors.push_back("File is empty");
    }
    
    // Set error result if there were any errors
    if (!errors.empty()) {
        std::string errorMessages;
        for (const auto& err : errors) {
            errorMessages += err + "\n";
        }
        data.result = Result::Error(errorMessages);
    } else {
        data.result = Result::Success();
    }
    
    return data;
}

Result Writefile(const std::string& path) {
    // Implementation for writing to file
    // This is a placeholder - implement as needed
    return Result::Success();
}

} // namespace File


