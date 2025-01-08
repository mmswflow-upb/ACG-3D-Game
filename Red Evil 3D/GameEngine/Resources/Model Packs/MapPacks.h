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
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
    std::string texturePath;
};

inline MapAttributes getMapModelAttributes(MapPack pack) {
    switch (pack) {
    case MapPack::Ver1:
        return {  "Resources/Models/Map/map_ver2.obj",
                 "Shaders/Maps Shaders/map_normal_vertex_shader.glsl", "Shaders/Maps Shaders/map_normal_fragment_shader.glsl" , "Resources/Models/Map/map_ver2.bmp"};

    case MapPack::Volcano:
        return {  "", // Placeholder paths
                 "", "", ""};

    case MapPack::Rocky:
        return {  "", // Placeholder paths
                 "", "" , ""};

    case MapPack::Plain:
        return {  "", // Placeholder paths
                 "", "" , ""};

    default:
        return {  "", "", "", ""};
    }
}
