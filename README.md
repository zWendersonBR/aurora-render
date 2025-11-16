![demo gif](https://github.com/user-attachments/assets/b86c1d97-0f9c-430d-980b-7e9058aae4c6)

# ✨ Aurora Render

## Low-Level, Open Source Graphics Renderer.

The **Aurora Render** is a **Graphics Renderer and Engine** focused on performance and control, created specifically for the **Modding** and 3D Asset Development community. Our mission is to offer a fast and precise platform to inspect, validate, and prepare your 3D models before injecting them into games like **MTA/FiveM/DayZ/ARK** and other customizable simulators.

> [!WARNING]
> The current version is **pre-alpha**, meaning the renderer is currently **limited** to importing models in the **.OBJ** format.

---

## 📚 Core Dependencies and Libraries

To ensure low-level control, performance, and portability, Aurora Render relies on the following libraries:

| Library | Version | Primary Function |
| :--- | :--- | :--- |
| **SDL (Simple DirectMedia Layer)** | 3.0+ | Window management, OpenGL context, input (mouse/keyboard), and timing. |
| **GLAD** | 0.1.36+ | OpenGL function *pointer* loader (GL functions). |
| **GLM (OpenGL Mathematics)** | 0.9.9+ | Vector and matrix mathematics library, essential for 3D transformations (Model, View, Projection). |
| **Assimp (Open Asset Import Library)** | 5.0+ | Loading of various 3D model formats (e.g., `.obj`, `.fbx`, `.dae`), abstracting mesh reading. |
| **iOSTREAM/cmath/vector** | C++ Standard Library | Basic I/O, mathematical functions (trigonometry), and data management (*containers*). |

---

## ⚙️ Architecture and Technical Details

Aurora is not a full Game Engine, but rather the low-level **graphics core**, ensuring maximum efficiency and control.

### 1. Core and Performance

* **Base Language:** **C++**. We prioritize C++ for total control over the *hardware* and runtime.
* **Memory Control:** Architecture focused on **manual and optimized memory allocation**. This eliminates *garbage collector* overhead and ensures that manipulating large vertex *meshes* is ultra-fast.
* **Graphics Backend:** We use **OpenGL 3.3+** (orchestrated via GLAD) for high performance and portability.

### 2. Extensibility

* **Scripting Engine:** The graphics engine is architected to support **C#** and **LUA bindings**. This will allow the community to create third-party *plugins*, specific format *parsers*, and automation tools using managed languages (FUTURE).
* **Rendering Pipeline:** The *shader* system is modular, allowing users to configure the *pipeline* to accurately simulate the lighting environment of their target game (FOR DEVS WHO WILL MODIFY THE SOURCE CODE).

---

## 🎯 Main Objective (Asset Validation)

Aurora Render serves as the last line of defense against visual *bugs* in *mods*:

| Feature | Function | Importance |
| :--- | :--- | :--- |
| **Normal Visualization** | **Real-time** check of lighting and normal vectors. | **CRITICAL:** Ensures the model's *shading* is correct (no dark/gray faces) for older games. |
| **Transformation Matrices** | Fine-tuning of **Scale, Rotation, and Translation**. | **ESSENTIAL:** Corrects **pivot** and **scale** issues that break the geometry or position of the *asset* in the game. |
| **6DOF Camera** | Free and controllable camera (FPS Style) with the mouse. | **EASY INSPECTION:** Allows rapid navigation for inspecting all mesh angles. |

---

## 🚀 Status and Compatibility

| Platform | Status | Notes |
| :--- | :--- | :--- |
| **Windows** | Unstable (Prototype) | Primary focus and under active development; currently unstable but functional. |
| **Linux** | In Development | Active portability via OpenGL/SDL. |
| **Android** | Planned | Future support for mobile asset visualization. |

---

## 🤝 Open Source and Contribution

**Aurora Render will be Open Source.** We encourage the community to join us!

1.  **Report Bugs:** Open an *issue* for any malfunction.
2.  **C++ Optimization:** Contribute *Pull Requests* (PRs) to optimize the *core* and memory management.
3.  **Plugin Development:** Utilize the C# and LUA *bindings* (future) to create specific tools for the community.

**Stay tuned for the first *alpha release* and the complete Contribution Guide!**
