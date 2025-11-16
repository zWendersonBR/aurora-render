#pragma once

#include <SDL.h> 
#include <iostream>

// Variável global para a janela
extern SDL_Window* window;

// Funções de Inicialização (Chamadas a partir de Engine::Init)
void Renderer_Init();

// Função principal de desenho
void Renderer_Draw();

class Engine {
public:
    Engine() = default;
    ~Engine() = default;

    // Métodos principais
    bool Init(int width, int height, const char* title);
    void Run();
    void Cleanup();
};