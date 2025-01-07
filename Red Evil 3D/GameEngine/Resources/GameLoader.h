#pragma once
#include <string>
#include "../Model Loading/meshLoaderObj.h"
#include "../Model Loading/mesh.h"
#include "Model Packs/CharacterPacks.h"
#include "Model Packs/ProjectilePacks.h"
#include "Model Packs/DropPacks.h"
#include "Model Packs/MapPack.h"
#include "../Model Loading/texture.h"

class GameLoader {
private:
    static std::vector<Texture> loadTexture(const std::string& texturePath) {
        GLuint tex = loadBMP(texturePath.c_str());
        std::vector<Texture> textures;
        textures.push_back(Texture());
        textures[0].id = tex;
        textures[0].type = "texture_diffuse";
        return textures;
    }

public:
    static Mesh loadCharacterMesh(CharacterPack pack) {
        CharacterAttributes attributes = getCharacterAttributes(pack);
        MeshLoaderObj loader;
        auto textures = loadTexture(attributes.texturePath);
        return loader.loadObj(attributes.modelPath, textures);
    }

    static Mesh loadProjectileMesh(ProjectileType type) {
        ProjectileAttributes attributes = getProjectileAttributes(type);
        MeshLoaderObj loader;
        auto textures = loadTexture(attributes.texturePath);
        return loader.loadObj(attributes.modelPath, textures);
    }

    static Mesh loadDropMesh(DropType type) {
        DropAttributes attributes = getDropAttributes(type);
        MeshLoaderObj loader;
        auto textures = loadTexture(attributes.texturePath);
        return loader.loadObj(attributes.modelPath, textures);
    }

    static Mesh loadMapMesh(MapPack pack) {
        MapAttributes attributes = getMapAttributes(pack);
        MeshLoaderObj loader;
        auto textures = loadTexture(attributes.texturePath);
        return loader.loadObj(attributes.terrainModel, textures);
    }
};
