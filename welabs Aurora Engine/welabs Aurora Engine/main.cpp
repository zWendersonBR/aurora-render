#include "Engine.h"

int main(int argc, char* argv[]) {
    Engine app;

    if (app.Init(1280, 720, "Aurora Engine - 0.1.0-aplha.7 ")) {
        app.Run();
		std::cout << "Aurora Engine inicializado com sucesso!" << std::endl;
    }
    
    app.Cleanup();
    return 0;
}