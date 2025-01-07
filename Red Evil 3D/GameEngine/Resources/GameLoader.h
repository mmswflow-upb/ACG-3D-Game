#pragma once
#include <string>
#include <vector>
#include "../Model Loading/mesh.h"
#include "../Model Loading/texture.h"
#include "../Shaders/shader.h"
#include "../Model Loading/meshLoaderObj.h"
#include "Model Packs/CelestialPacks.h"
#include "Model Packs/CharacterPacks.h"
#include "Model Packs/GunPacks.h"
#include "Model Packs/ProjectilePacks.h"
#include "Model Packs/DropPacks.h"
#include "Model Packs/MapPacks.h"



class GameLoader {
private:
    // Helper function to load a single texture
    static std::vector<Texture> loadTexture(const std::string& texturePath) {
        GLuint tex = loadBMP(texturePath.c_str());
        std::vector<Texture> textures;
        textures.push_back(Texture());
        textures[0].id = tex;
        textures[0].type = "texture_diffuse";
        return textures;
    }

public:
    // Load Celestial Mesh
    static Mesh loadCelestialMesh(CelestialPack pack) {
        CelestialAttributes attributes = getCelestialAttributes(pack);
        MeshLoaderObj loader;
        
        if (!attributes.texturePath.empty()) {
            auto textures = loadTexture(attributes.texturePath);
            return loader.loadObj(attributes.modelPath, textures);

        }
        
        return loader.loadObj(attributes.modelPath);
            
        

    }

    // Load Celestial Shader
    static Shader loadCelestialShader(CelestialPack pack) {
        CelestialAttributes attributes = getCelestialAttributes(pack);
        return Shader(attributes.vertexShaderPath.c_str(), attributes.fragmentShaderPath.c_str());
    }

    // Load Character Mesh
    static Mesh loadCharacterMesh(CharacterPack pack) {
        CharacterAttributes attributes = getCharacterAttributes(pack);
        MeshLoaderObj loader;
        auto textures = loadTexture(attributes.texturePath);
        return loader.loadObj(attributes.modelPath, textures);
    }

    // Load Projectile Mesh
    static Mesh loadProjectileMesh(ProjectileType type) {
        ProjectileAttributes attributes = getProjectileAttributes(type);
        MeshLoaderObj loader;
        auto textures = loadTexture(attributes.texturePath);
        return loader.loadObj(attributes.modelPath, textures);
    }

    // Load Drop Mesh
    static Mesh loadDropMesh(DropType type) {
        DropAttributes attributes = getDropAttributes(type);
        MeshLoaderObj loader;
        auto textures = loadTexture(attributes.texturePath);
        return loader.loadObj(attributes.modelPath, textures);
    }

    // Load Map Mesh
    static Mesh loadMapMesh(MapPack pack) {
        MapAttributes attributes = getMapAttributes(pack);
        MeshLoaderObj loader;
        auto textures = loadTexture(attributes.texturePath);
        return loader.loadObj(attributes.terrainModel, textures);
    }

    // Load Map Shader
    static Shader loadMapShader(MapPack pack) {
        MapAttributes attributes = getMapAttributes(pack);
        return Shader(attributes.vertexShaderPath.c_str(), attributes.fragmentShaderPath.c_str());
    }
};