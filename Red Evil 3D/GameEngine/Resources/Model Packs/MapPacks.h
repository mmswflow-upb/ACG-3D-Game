#pragma once
#include <string>
#include <glm.hpp>

enum class MapPack {
    Ver1,
    Volcano,
    Rocky,
    Plain
};

struct MapAttributes {
    std::string terrainModel;
    glm::vec3 ambientColor;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
    std::string texturePath;
};

inline MapAttributes getMapModelAttributes(MapPack pack) {
    switch (pack) {
    case MapPack::Ver1:
        return {  "Resources/Models/Map/map.obj",
                 glm::vec3(0.5f, 0.7f, 1.0f),
                 "Shaders/Maps Shaders/map_normal_vertex_shader.glsl", "Shaders/Maps Shaders/map_normal_fragment_shader.glsl" , "Resources/Models/Map/map_ver2.bmp"};

    case MapPack::Volcano:
        return {  "", // Placeholder paths
                 glm::vec3(0.9f, 0.2f, 0.2f),
                 "", "", ""};

    case MapPack::Rocky:
        return {  "", // Placeholder paths
                 glm::vec3(0.6f, 0.6f, 0.6f),
                 "", "" , ""};

    case MapPack::Plain:
        return {  "", // Placeholder paths
                 glm::vec3(0.3f, 0.8f, 0.3f),
                 "", "" , ""};

    default:
        return {  "", glm::vec3(1.0f, 1.0f, 1.0f), "", "", ""};
    }
}
