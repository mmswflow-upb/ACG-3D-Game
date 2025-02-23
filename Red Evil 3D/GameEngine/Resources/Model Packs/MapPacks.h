#pragma once
#include <string>
#include <glm.hpp>

enum class MapPack {
    FullNoTrees
};

struct MapAttributes {
    std::string terrainModel;
    std::string texturePath;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
};

inline MapAttributes getMapModelAttributes(MapPack pack) {
    switch (pack) {
    case MapPack::FullNoTrees:
        return {  
            "Resources/Models/Map/mapWithNoTrees/mapWithNoTrees.obj",
            "Resources/Models/Map/mapWithNoTrees/mapWithNoTrees.bmp",
            "Shaders/Maps Shaders/FullNoTrees/fullNoTrees_vertex_shader.glsl", 
            "Shaders/Maps Shaders/FullNoTrees/fullNoTrees_fragment_shader.glsl"
        };

    default:
        return {  "", "", "", ""};
    }
}
