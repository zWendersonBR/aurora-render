#pragma once

// --- 1. MODEL SHADER (Com Iluminação Phong) ---

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix; // Necessário para objetos rotacionados

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = normalMatrix * aNormal; // Multiplica a Normal pela Matriz Normal
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 viewPos; // Posição da Câmera (View)

// Valores da Luz
uniform vec3 lightColor = vec3(1.0f, 1.0f, 1.0f); // Luz branca
uniform vec3 objectColor = vec3(0.9f, 0.5f, 0.1f); // CORRIGIDO: Laranja mais forte

void main()
{
    // --- 1. Componente Ambiente ---
    float ambientStrength = 0.2f;
    vec3 ambient = ambientStrength * lightColor;

    // --- 2. Componente Difusa ---
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // --- 3. Componente Especular ---
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

    // Cor final (Iluminação x Cor do Objeto)
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
)";


// --- 2. GRID SHADER ---

const char* gridVertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";

const char* gridFragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    // Cor da Grade
    FragColor = vec4(0.4f, 0.4f, 0.4f, 1.0f); 
}
)";


// --- 3. GIZMO SHADER (Eixos XYZ) ---

const char* gizmoVertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 gizmoModel;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    ourColor = aColor;
    // O gizmo deve ser desenhado no espaço de tela, mas orientado pela câmera
    gl_Position = projection * view * gizmoModel * vec4(aPos, 1.0);
}
)";

const char* gizmoFragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
}
)";

