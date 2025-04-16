#include"core/application.h"

int main() {
    Application* app = new Application("path");
    app->exec();
    delete(app);
}