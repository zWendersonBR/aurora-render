![demo gif](https://github.com/user-attachments/assets/b86c1d97-0f9c-430d-980b-7e9058aae4c6)

# ✨ Aurora Render



## Renderizador Gráfico de Baixo Nível, Open Source.

O **Aurora Render** é um **Renderizador e Motor Gráfico** focado em performance e controle, criado especificamente para a comunidade de **Modding** e Desenvolvimento de Assets 3D. Nossa missão é oferecer uma plataforma rápida e precisa para inspecionar, validar e preparar seus modelos 3D antes de injetá-los em jogos como **MTA/FiveM/DayZ/ARK** e simuladores que suportam customização.

---

## 📚 Dependências e Bibliotecas Principais

Para garantir o baixo nível de controle, performance e portabilidade, o Aurora Render depende das seguintes bibliotecas:

| Biblioteca | Versão | Função Principal |
| :--- | :--- | :--- |
| **SDL (Simple DirectMedia Layer)** | 3.0+ | Gerenciamento de janelas, contexto OpenGL, input (mouse/teclado) e temporização. |
| **GLAD** | 0.1.36+ | Carregador de *pointers* de função OpenGL (funções GL). |
| **GLM (OpenGL Mathematics)** | 0.9.9+ | Biblioteca de matemática de vetores e matrizes, essencial para as transformações 3D (Model, View, Projection). |
| **Assimp (Open Asset Import Library)** | 5.0+ | Carregamento de diversos formatos de modelos 3D (e.g., `.obj`, `.fbx`, `.dae`), abstraindo a leitura da malha. |
| **iOSTREAM/cmath/vector** | C++ Standard Library | Funções básicas de I/O, matemática (trigonometria) e gerenciamento de dados (*containers*). |

---

## ⚙️ Arquitetura e Detalhes Técnicos

O Aurora não é um motor de jogo (Game Engine), mas sim o **coração gráfico** de baixo nível, garantindo a máxima eficiência e controle.

### 1. Core e Performance

* **Linguagem Base:** **C++**. Priorizamos o C++ para controle total sobre o *hardware* e o tempo de execução.
* **Controle de Memória:** Arquitetura focada em **alocação de memória manual e otimizada**. Isso elimina os *gargalos* do *garbage collector* e garante que a manipulação de grandes malhas de vértices (*meshes*) seja ultrarrápida.
* **Backend Gráfico:** Utilizamos **OpenGL 3.3+** (orquestrado via GLAD) para alto desempenho e portabilidade.

### 2. Extensibilidade

* **Motor de Script:** O motor gráfico está arquitetado para suportar *bindings* de **C#** e **LUA**. Isso permitirá que a comunidade crie *plugins* de terceiros, *parsers* de formatos específicos e ferramentas de automação usando linguagens gerenciadas.
* **Pipeline de Rendering:** O sistema de *shaders* é modular, permitindo que os usuários configurem o *pipeline* para simular com precisão o ambiente de iluminação do seu jogo de destino.

---

## 🎯 Objetivo Principal (Validação de Assets)

O Aurora Render serve como a última linha de defesa contra *bugs* visuais em *mods*:

| Recurso | Função | Importância |
| :--- | :--- | :--- |
| **Visualização de Normais** | Checagem de iluminação e vetores normais em **tempo real**. | **CRÍTICO:** Garante que o *shading* do modelo esteja correto (sem faces escuras/cinzas) para jogos mais antigos. |
| **Matrizes de Transformação** | Ajuste fino de **Escala, Rotação e Translação**. | **ESSENCIAL:** Corrige problemas de **pivô** e **escala** que quebram a geometria ou a posição do *asset* no jogo. |
| **Câmera 6DOF** | Câmera livre e controlável (FPS Style) com o mouse. | **FÁCIL INSPEÇÃO:** Permite a navegação rápida para inspeção de todos os ângulos da malha. |

---

## 🚀 Status e Compatibilidade

| Plataforma | Status | Notas |
| :--- | :--- | :--- |
| **Windows** | Instavel (Protótipo) | Foco principal e em desenvolvimento, completamente instavel porem fucional. |
| **Linux** | Em Desenvolvimento | Portabilidade ativa via OpenGL/SDL. |
| **Android** | Planejado | Suporte futuro para visualização móvel de *assets*. |

---

## 🤝 Código Aberto e Contribuição

O **Aurora Render será Open Source**. Encorajamos a comunidade a se juntar a nós!

1.  **Reporte Bugs:** Abra uma *issue* para qualquer falha.
2.  **Otimização C++:** Contribua com *Pull Requests* (PRs) para otimizar o *core* e o gerenciamento de memória.
3.  **Desenvolvimento de Plugins:** Utilize as *bindings* de C# e LUA (futuras) para criar ferramentas específicas para a comunidade.

**Fique ligado para o primeiro *alpha release* e o Guia de Contribuição completo!**
