#include"Application.h"

int main() {
    Application* App = new Application("path");
    App->Exec();
    delete(App);
}