#include "core/application.h"

const std::string PATH = "../input.txt";

int main() {
    try {
        // Use unique_ptr for automatic memory management
        auto app = std::make_unique<Application>(PATH);
        app->exec();
        // No need to delete - unique_ptr will handle cleanup
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }
    
    return 0;
}