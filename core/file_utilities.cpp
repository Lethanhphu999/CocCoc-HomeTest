#include "data/map.h"
#include "commands/command.h"

#include "core/file_utilities.h"

struct Point;
enum class TypeCommand;

namespace {

const std::unordered_map<std::string, TypeCommand> kKeywordCommandMap = {
    {"MOVE_TO", TypeCommand::MOVE_TO},
    {"LINE_TO", TypeCommand::LINE_TO},
    {"SPECIAL", TypeCommand::SPECIAL}
};

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

} // namesapce

namespace File {

DataReadFile parseFile(const std::string &path) {
    std::ifstream file(path);
    DataReadFile data;
    using Type = TypeCommand;
#ifdef DEBUG
    std::cout << "Current working directory: " 
              << std::filesystem::current_path() << std::endl;
#endif
    if (!file.is_open()) {
        data.result = Result::Error("Can not open file: " + path + "\n");
        return data;
    }

    std::regex regexDimension(R"(^DIMENSION\s(\d+)$)");
    std::regex regexCommand("^(" + chainCommand() + R"()\s(\d+),(\d+)$)");
    std::smatch match;

    int lineNumber = 1;
    std::string line;
    std::vector<std::string> errors;
    
    while (std::getline(file, line)) {
        if (std::regex_match(line, match, regexDimension)
            || lineNumber == 1) {
            try {
                data.N = std::stoll(match[1]);
            } catch (...) {
                errors.push_back("Invalid dimention at line " + std::to_string(lineNumber) + ": " + line);
            }
        } else if (std::regex_match(line, match, regexCommand)) {
            const std::string& cmd = match[1];
            try {
                long long x = std::stoll(match[2]);
                long long y = std::stoll(match[3]);
    
                auto it = kKeywordCommandMap.find(cmd);
                if (it != kKeywordCommandMap.end()) {
                    data.commands.push_back({it->second, {x, y}});
                } else {
                    errors.push_back("Invalid keyword " + cmd + " at line " + std::to_string(lineNumber));
                }
            } catch (...) {
                errors.push_back("Failed to parse coordinates at line " + std::to_string(lineNumber));
            }
        } else {
            errors.push_back("Invalid format at line " + std::to_string(lineNumber) + ": " + line);
        }
    
        ++lineNumber;
    }

    if (lineNumber == 1) {
        errors.push_back("File input is empty\n");
    }
    
    if (!errors.empty()) {
        std::string errorMessages;
        for (const auto& err : errors) {
            errorMessages += err + "\n";
        }
        data.result = Result::Error(errorMessages);
    }
    return data;
}

} // namespace File


