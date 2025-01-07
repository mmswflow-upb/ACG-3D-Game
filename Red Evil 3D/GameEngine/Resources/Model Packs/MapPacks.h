#pragma once
#include <string>
#include <glm.hpp>

enum class MapPack {
    Ice,
    Volcano,
    Rocky,
    Plain
};

struct MapAttributes {
    std::string name;
    std::string terrainModel;
    glm::vec3 ambientColor;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
    std::string texturePath;
};

inline MapAttributes getMapAttributes(MapPack pack) {
    switch (pack) {
    case MapPack::Ice:
        return { "Ice Map", "../Models/Map/map_ver2.obj",
                 glm::vec3(0.5f, 0.7f, 1.0f),
                 "../../Shaders/Maps Shaders/map_vertex_shader.glsl", "../../Shaders/Maps Shaders/map_fragment_shader.glsl" , "../Models/Map/map_ver2.bmp"};

    case MapPack::Volcano:
        return { "Volcano Map", "", // Placeholder paths
                 glm::vec3(0.9f, 0.2f, 0.2f),
                 "", "", ""};

    case MapPack::Rocky:
        return { "Rocky Map", "", // Placeholder paths
                 glm::vec3(0.6f, 0.6f, 0.6f),
                 "", "" , ""};

    case MapPack::Plain:
        return { "Plain Map", "", // Placeholder paths
                 glm::vec3(0.3f, 0.8f, 0.3f),
                 "", "" , ""};

    default:
        return { "Unknown", "", glm::vec3(1.0f, 1.0f, 1.0f), "", "", ""};
    }
}
