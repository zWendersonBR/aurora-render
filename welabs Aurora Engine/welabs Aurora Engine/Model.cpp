#include "Model.h"
#include <iostream>
#include <stddef.h> // OBRIGATÓRIO para usar offsetof()

// --- Implementação da Estrutura Mesh ---

void Mesh::SetupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // layout = 0: Posição
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // layout = 1: Normais (Corrigindo C2618)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    glBindVertexArray(0);
}

void Mesh::Draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

// --- Implementação da Classe Model ---

bool Model::LoadModel(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERRO::ASSIMP:: Falha ao carregar modelo: " << importer.GetErrorString() << std::endl;
        this->isLoaded = false;
        return false; // Retorna FALSO
    }

    size_t lastSlash = path.find_last_of('/');
    if (lastSlash == std::string::npos) {
        lastSlash = path.find_last_of('\\');
    }
    directory = (lastSlash == std::string::npos) ? "" : path.substr(0, lastSlash);

    this->meshes.clear();
    processNode(scene->mRootNode, scene);

    this->isLoaded = true;
    return true; // Retorna VERDADEIRO
}

void Model::Draw() {
    if (isLoaded) {
        for (auto& mesh : meshes) {
            mesh.Draw();
        }
    }
}

void Model::processNode(aiNode* node, const aiScene* scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    Mesh newMesh;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        // Posições
        vertex.Position[0] = mesh->mVertices[i].x;
        vertex.Position[1] = mesh->mVertices[i].y;
        vertex.Position[2] = mesh->mVertices[i].z;

        // Normais
        if (mesh->HasNormals()) {
            vertex.Normal[0] = mesh->mNormals[i].x;
            vertex.Normal[1] = mesh->mNormals[i].y;
            vertex.Normal[2] = mesh->mNormals[i].z;
        }
        else {
            vertex.Normal[0] = 0.0f; vertex.Normal[1] = 0.0f; vertex.Normal[2] = 0.0f;
        }
        newMesh.vertices.push_back(vertex);
    }

    // Índices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            newMesh.indices.push_back(face.mIndices[j]);
    }

    newMesh.SetupMesh();
    return newMesh;
}