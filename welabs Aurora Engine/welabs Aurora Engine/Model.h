#pragma once
#include <vector>
#include <string>
#include <glad/glad.h>
#include <iostream>
#include <SDL.h> // Incluído para compatibilidade geral

// Assimp Includes
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex {
	// Estrutura simplificada para eliminar caracteres invisíveis/UTF-8 (E0007, C3873)
	float Position[3]; // layout = 0
	float Normal[3];   // layout = 1
};

struct Mesh {
	unsigned int VAO, VBO, EBO;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	void SetupMesh();
	void Draw();
};

class Model {
public:
	Model() = default;

	// Deve retornar bool (corrigindo E0711, C2451)
	bool LoadModel(const std::string& path);

	void Draw();

	// A função deve ser pública (corrigindo E0135, C2039)
	bool IsLoaded() const { return isLoaded; }

private:
	bool isLoaded = false;
	std::vector<Mesh> meshes;
	std::string directory;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};