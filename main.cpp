#include"core/application.h"

const std::string path = "./input.txt";

int main() {
    Application* app = new Application(path);
    app->exec();
    delete(app);
}