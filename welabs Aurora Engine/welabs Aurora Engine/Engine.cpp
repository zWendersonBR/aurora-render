#include "Engine.h"
#include "Render.h"
#include "Shaders.h" 
#include "Model.h" 
#include <glad/glad.h>
#include <iostream>
#include <cmath>
#include <vector>

// --- Includes GLM CORRIGIDOS ---
// Certifique-se de que o caminho de inclusão do seu projeto aponta para C:\Libs (e não C:\Libs\glm)
#include <glm.hpp>             
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
// --------------------

// --- Variáveis globais (Definidas aqui) ---
unsigned int shaderProgram;
Model g_Model;
SDL_Window* window = nullptr;

// VARIÁVEIS DE CÂMERA LIVRE (CORRIGIDAS: Mais longe para ver o modelo inicial)
glm::vec3 cameraPos = glm::vec3(0.0f, 3.0f, 10.0f); // Mova para Z=10
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float cameraSpeed = 5.0f;
float yaw = -90.0f;
float pitch = 0.0f;

// VARIÁVEIS DE CONTROLE DO MOUSE
float lastX = 400;
float lastY = 300;
bool firstMouse = true;
bool isLMBDown = false;

// VARIÁVEIS DA GRADE
unsigned int gridShaderProgram;
unsigned int gridVAO;

// VARIÁVEIS DO GIZMO
unsigned int gizmoShaderProgram;
unsigned int gizmoVAO;
// ------------------------------------------

// --- Implementação do Renderer ---

void Renderer_Init() {
    // 1. Compilação do MODEL SHADER
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 2. CARREGAMENTO DO MODELO
    // Use apenas o nome se o arquivo FBX estiver na mesma pasta do executável (x64/Debug)
    g_Model.LoadModel("./auroramodel.obj");
   // g_Model.LoadModel("./auroramodel.fbx");

    // 3. INICIALIZAÇÃO DA GRADE (GRID)
    unsigned int gvs_grid = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(gvs_grid, 1, &gridVertexShaderSource, NULL);
    glCompileShader(gvs_grid);
    unsigned int gfs_grid = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(gfs_grid, 1, &gridFragmentShaderSource, NULL);
    glCompileShader(gfs_grid);
    gridShaderProgram = glCreateProgram();
    glAttachShader(gridShaderProgram, gvs_grid);
    glAttachShader(gridShaderProgram, gfs_grid);
    glLinkProgram(gridShaderProgram);
    glDeleteShader(gvs_grid);
    glDeleteShader(gfs_grid);

    std::vector<float> gridVertices;
    int gridSize = 20;
    float step = 1.0f;
    float halfSize = (float)gridSize / 2.0f;
    for (int i = 0; i <= gridSize; ++i) {
        float z = (float)i * step - halfSize;
        gridVertices.push_back(-halfSize); gridVertices.push_back(0.0f); gridVertices.push_back(z);
        gridVertices.push_back(halfSize); gridVertices.push_back(0.0f); gridVertices.push_back(z);
        float x = (float)i * step - halfSize;
        gridVertices.push_back(x); gridVertices.push_back(0.0f); gridVertices.push_back(-halfSize);
        gridVertices.push_back(x); gridVertices.push_back(0.0f); gridVertices.push_back(halfSize);
    }

    unsigned int gridVBO;
    glGenVertexArrays(1, &gridVAO);
    glGenBuffers(1, &gridVBO);
    glBindVertexArray(gridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBufferData(GL_ARRAY_BUFFER, gridVertices.size() * sizeof(float), &gridVertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

  /* // 4. INICIALIZAÇÃO DO GIZMO
    unsigned int gvs_gizmo = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(gvs_gizmo, 1, &gizmoVertexShaderSource, NULL);
    glCompileShader(gvs_gizmo);
    unsigned int gfs_gizmo = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(gfs_gizmo, 1, &gizmoFragmentShaderSource, NULL);
    glCompileShader(gfs_gizmo);

    gizmoShaderProgram = glCreateProgram();
    glAttachShader(gizmoShaderProgram, gvs_gizmo);
    glAttachShader(gizmoShaderProgram, gfs_gizmo);
    glLinkProgram(gizmoShaderProgram);
    glDeleteShader(gvs_gizmo);
    glDeleteShader(gfs_gizmo);

    float gizmoVertices[] = {
        // Posição            | Cor (RGB)
         0.0f, 0.0f, 0.0f,     1.0f, 0.0f, 0.0f, // X (Vermelho)
         1.0f, 0.0f, 0.0f,     1.0f, 0.0f, 0.0f,
         0.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f, // Y (Verde)
         0.0f, 1.0f, 0.0f,     0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 0.0f,     0.0f, 0.0f, 1.0f, // Z (Azul)
         0.0f, 0.0f, 1.0f,     0.0f, 0.0f, 1.0f
    };

    unsigned int gizmoVBO;
    glGenVertexArrays(1, &gizmoVAO);
    glGenBuffers(1, &gizmoVBO);

    glBindVertexArray(gizmoVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gizmoVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gizmoVertices), gizmoVertices, GL_STATIC_DRAW);*/ 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Renderer_Draw() {
    // --- CÁLCULO DAS MATRIZES ---

    // 1. Matriz Model (do Objeto)
    glm::mat4 model = glm::mat4(1.0f);

    // ESCALA FINAL MAIOR: Usando 0.5f para garantir visibilidade
    model = glm::scale(model, glm::vec3(0.5f));

    // TRANSLAÇÃO: Centraliza o modelo na origem (0,0,0)
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

    // Rotação continua
    model = glm::rotate(model, (float)SDL_GetTicks() * 0.0005f, glm::vec3(0.0f, 1.0f, 0.0f));
    // Esta linha é CRÍTICA para que a iluminação funcione em modelos rotacionados
    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
    glUniformMatrix3fv(glGetUniformLocation(shaderProgram, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
    // 2. Matriz View (Câmera Livre)
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

    glm::mat4 view = glm::lookAt(
        cameraPos,
        cameraPos + cameraFront,
        cameraUp
    );

    // 3. Matriz Projection (Perspectiva para o mundo 3D)
    int width, height;
    SDL_GetWindowSizeInPixels(window, &width, &height);
    if (height == 0) height = 1;
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        (float)width / (float)height,
        0.001f,
        500.0f
    );

    // --- 1. DESENHAR A GRADE ---
    glUseProgram(gridShaderProgram);
    glm::mat4 gridModel = glm::mat4(1.0f);
    glUniformMatrix4fv(glGetUniformLocation(gridShaderProgram, "model"), 1, GL_FALSE, &gridModel[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(gridShaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(gridShaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
    glBindVertexArray(gridVAO);
    glDrawArrays(GL_LINES, 0, (20 + 1) * 4);
    glBindVertexArray(0);


    // --- 2. DESENHAR O MODELO ---
    glUseProgram(shaderProgram);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);

    glm::vec3 lightPos(10.0f, 10.0f, 10.0f);
    glUniform3fv(glGetUniformLocation(shaderProgram, "lightPos"), 1, &lightPos[0]);
    glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, glm::value_ptr(cameraPos));

    g_Model.Draw();

    /*
    // --- 3. DESENHAR O GIZMO FIXO (PEQUENO e no CANTO) ---
    glUseProgram(gizmoShaderProgram);

    // Projeção Ortográfica (PARA O GIZMO - Espaço de tela -1 a 1)
    glm::mat4 OrthoProjection = glm::ortho(
        -1.0f, 1.0f,    // left, right
        -1.0f, 1.0f,    // bottom, top
        0.01f, 100.0f
    );

    glm::mat4 gizmoModel_mat = glm::mat4(1.0f);

    // ESCALA: MUITO menor (0.05f) para ficar minúsculo
    gizmoModel_mat = glm::scale(gizmoModel_mat, glm::vec3(0.05f));

    // POSIÇÃO: Quase no canto (-0.85f em X, 0.85f em Y) no espaço ortográfico
    gizmoModel_mat = glm::translate(gizmoModel_mat, glm::vec3(-0.85f, 0.85f, 0.0f));

    // View (SÓ ROTAÇÃO): Remove a translação da câmera (CRÍTICO)
    glm::mat4 gizmoView = view;
    gizmoView[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    glUniformMatrix4fv(glGetUniformLocation(gizmoShaderProgram, "gizmoModel"), 1, GL_FALSE, &gizmoModel_mat[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(gizmoShaderProgram, "view"), 1, GL_FALSE, &gizmoView[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(gizmoShaderProgram, "projection"), 1, GL_FALSE, &OrthoProjection[0][0]);

    glDisable(GL_DEPTH_TEST);
    glLineWidth(5.0f);

    glBindVertexArray(gizmoVAO);
    glDrawArrays(GL_LINES, 0, 6);
    glBindVertexArray(0);*/

    glEnable(GL_DEPTH_TEST);
}
// --- Implementação da Classe Engine ---

bool Engine::Init(int width, int height, const char* title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Falha ao inicializar SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cout << "Falha ao criar janela SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cout << "Falha ao criar contexto GL: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        return false;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cout << "Erro ao inicializar GLAD!" << std::endl;
        SDL_DestroyWindow(window);
        return false;
    }

    // CRÍTICO: Configuração do Viewport para a janela
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    Renderer_Init();
    return true;
}

void Engine::Run() {
    bool running = true;
    SDL_Event e;

    // CÁLCULO DO DELTA TIME
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    while (running) {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }
            else if (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE) {
                running = false;
            }

            // TRATAMENTO DO CLIQUE E MOVIMENTO DO MOUSE (SDL3 CORRIGIDO)
            else if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    isLMBDown = true;
               
                }
            }
            else if (e.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    isLMBDown = false;
                    firstMouse = true;
             
                }
            }

            else if (e.type == SDL_EVENT_MOUSE_MOTION) {
                if (isLMBDown) {
                    float xoffset = (float)e.motion.xrel;
                    float yoffset = (float)e.motion.yrel * -1; // Inverter Y

                    float sensitivity = 0.1f;
                    yaw += xoffset * sensitivity;
                    pitch += yoffset * sensitivity;

                    if (pitch > 89.0f) pitch = 89.0f;
                    if (pitch < -89.0f) pitch = -89.0f;
                }
            }

            else if (e.type == SDL_EVENT_MOUSE_WHEEL) {
                float scrollSpeed = 20.0f;
                cameraPos += cameraFront * e.wheel.y * scrollSpeed * (float)deltaTime;
            }
        }

        // TRATAMENTO DE MOVIMENTO WASD (SDL3 CORRIGIDO: const bool*)
        const bool* state = SDL_GetKeyboardState(NULL);
        float velocity = cameraSpeed * (float)deltaTime;

        if (state[SDL_SCANCODE_W])
            cameraPos += velocity * cameraFront;
        if (state[SDL_SCANCODE_S])
            cameraPos -= velocity * cameraFront;
        if (state[SDL_SCANCODE_A])
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;
        if (state[SDL_SCANCODE_D])
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;

        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Renderer_Draw();

        SDL_GL_SwapWindow(window);
    }
}

void Engine::Cleanup() {
    glDeleteProgram(gizmoShaderProgram);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(gridShaderProgram);

    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    std::cout << "Engine finalizada." << std::endl;
}