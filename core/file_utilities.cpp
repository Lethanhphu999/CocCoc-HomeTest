#include "data/map.h"
#include "commands/command.h"

#include "core/file_utilities.h"

struct Point;
enum class TypeCommand;

namespace {

const std::string kTripleQuote = "“””";
const std::unordered_map<std::string, TypeCommand> kKeywordCommandMap = {
    {"MOVE_TO", TypeCommand::MOVE_TO},
    {"LINE_TO", TypeCommand::LINE_TO},
    {"SPECIAL", TypeCommand::SPECIAL}
};

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

    std::string line;
    std::vector<std::string> lines;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }

    if (lines.size() < 2 
        || lines.front() != kTripleQuote 
        || lines.back() != kTripleQuote) {
        data.result = Result::Error("The file is not wrapped with “””\n");
        return data;
    }

    for (size_t i = 1; i + 1 < lines.size(); ++i) {
        std::istringstream iss(lines[i]);
        std::string keyword;
        iss >> keyword;

        if (keyword == "DIMENSION") {
            if (!(iss >> data.N)) {
                data.result = Result::Error("Failed to read DIMENSION\n");
                return data;
            }
        } else if (keyword == "MOVE_TO"
                || keyword == "LINE_TO"
                || keyword == "SPECIAL") {
            std::string coords;
            if (!(iss >> coords)) {
                data.result = Result::Error("Error reading coordinates at line:" + lines[i] + "\n");
                return data;
            }

            size_t comma = coords.find(',');
            if (comma == std::string::npos) {
                data.result = Result::Error("Invalid coordinate format:" + coords + + "\n");
                return data;
            }

            try {
                int x = std::stoi(coords.substr(0, comma));
                int y = std::stoi(coords.substr(comma + 1));
                auto it = kKeywordCommandMap.find(keyword);
                if (it != kKeywordCommandMap.end()) {
                    data.commands.push_back({it->second, {x, y}});
                } else {
                    data.result = Result::Error("Invalid keyword: " + keyword + "\n");
                }
            } catch (const std::exception& e) {
                data.result = Result::Error("Failed to parse coordinates: " + coords + "\n");
                return data;
            }
        } else {
            data.result = Result::Error("Invalid keyword: " + keyword + "\n");
            return data;
        }
    }

    data.result = Result::Success();
    return data;
}

} // namespace File


