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
#include "Model Packs/AnimatablePacks.h"  // Include animatable pack definitions

class GameLoader {
private:
    // Helper function to load a single texture.
    static std::vector<Texture> loadTexture(const std::string& texturePath) {
        GLuint tex = loadBMP(texturePath.c_str());

        std::vector<Texture> textures;
        textures.push_back(Texture());
        textures[0].id = tex;
        textures[0].type = "texture_diffuse";
        return textures;
    }

public:
    // Load Celestial Mesh and Shader
    static Mesh loadCelestialMesh(CelestialPack pack) {
        CelestialModelAttributes attributes = getCelestialModelAttributes(pack);
        MeshLoaderObj loader;
        if (!attributes.texturePath.empty()) {
            auto textures = loadTexture(attributes.texturePath);
            return loader.loadObj(attributes.modelPath, textures);
        }
        return loader.loadObj(attributes.modelPath); // No texture
    }

    static Shader loadCelestialShader(CelestialPack pack) {
        CelestialModelAttributes attributes = getCelestialModelAttributes(pack);
        return Shader(attributes.vertexShaderPath.c_str(), attributes.fragmentShaderPath.c_str());
    }

    // Load Character Mesh and Shader
    static Mesh loadCharacterMesh(CharacterPack pack) {
        CharacterModelAttributes attributes = getCharacterModelAttributes(pack);
        MeshLoaderObj loader;
        if (!attributes.texturePath.empty()) {
            auto textures = loadTexture(attributes.texturePath);
            return loader.loadObj(attributes.modelPath, textures);
        }
        return loader.loadObj(attributes.modelPath); // No texture
    }

    static Shader loadCharacterShader(CharacterPack pack) {
        CharacterModelAttributes attributes = getCharacterModelAttributes(pack);
        return Shader(attributes.vertexShaderPath.c_str(), attributes.fragmentShaderPath.c_str());
    }

    // Load Projectile Mesh and Shader
    static Mesh loadProjectileMesh(ProjectileType type) {
        ProjectileModelAttributes attributes = getProjectileModelAttributes(type);
        MeshLoaderObj loader;
        if (!attributes.texturePath.empty()) {
            auto textures = loadTexture(attributes.texturePath);
            return loader.loadObj(attributes.modelPath, textures);
        }
        return loader.loadObj(attributes.modelPath); // No texture
    }

    static Shader loadProjectileShader(ProjectileType type) {
        ProjectileModelAttributes attributes = getProjectileModelAttributes(type);
        return Shader(attributes.vertexShaderPath.c_str(), attributes.fragmentShaderPath.c_str());
    }

    // Load Drop Mesh and Shader
    static Mesh loadDropMesh(DropType type) {
        DropModelAttributes attributes = getDropModelAttributes(type);
        MeshLoaderObj loader;
        if (!attributes.texturePath.empty()) {
            auto textures = loadTexture(attributes.texturePath);
            return loader.loadObj(attributes.modelPath, textures);
        }
        return loader.loadObj(attributes.modelPath); // No texture
    }

    static Shader loadDropShader(DropType type) {
        DropModelAttributes attributes = getDropModelAttributes(type);
        return Shader(attributes.vertexShaderPath.c_str(), attributes.fragmentShaderPath.c_str());
    }

    // Load Gun Mesh and Shader
    static Mesh loadGunMesh(GunPack pack) {
        GunModelAttributes attributes = getGunModelAttributes(pack);
        MeshLoaderObj loader;
        if (!attributes.texturePath.empty()) {
            auto textures = loadTexture(attributes.texturePath);
            return loader.loadObj(attributes.modelPath, textures);
        }
        return loader.loadObj(attributes.modelPath); // No texture
    }

    static Shader loadGunShader(GunPack pack) {
        GunModelAttributes attributes = getGunModelAttributes(pack);
        return Shader(attributes.vertexShaderPath.c_str(), attributes.fragmentShaderPath.c_str());
    }

    // Load Map Mesh and Shader
    static Mesh loadMapMesh(MapPack pack) {
        MapAttributes attributes = getMapModelAttributes(pack);
        MeshLoaderObj loader;
        if (!attributes.texturePath.empty()) {
            std::cout << "\n\n\n\nLoading map with texture\n\n\n\n";
            auto textures = loadTexture(attributes.texturePath);
            return loader.loadObj(attributes.terrainModel, textures);
        }
        return loader.loadObj(attributes.terrainModel); // No texture
    }

    static Shader loadMapShader(MapPack pack) {
        MapAttributes attributes = getMapModelAttributes(pack);
        return Shader(attributes.vertexShaderPath.c_str(), attributes.fragmentShaderPath.c_str());
    }

    // Load Animatable Mesh and Shader
    static Mesh loadAnimatableMesh(AnimatableType type) {
        AnimatableModelAttributes attributes = getAnimatableModelAttributes(type);
        MeshLoaderObj loader;
        if (!attributes.texturePath.empty()) {
            auto textures = loadTexture(attributes.texturePath);
            return loader.loadObj(attributes.modelPath, textures);
        }
        return loader.loadObj(attributes.modelPath); // No texture
    }

    static Shader loadAnimatableShader(AnimatableType type) {
        AnimatableModelAttributes attributes = getAnimatableModelAttributes(type);
        return Shader(attributes.vertexShaderPath.c_str(), attributes.fragmentShaderPath.c_str());
    }
};
