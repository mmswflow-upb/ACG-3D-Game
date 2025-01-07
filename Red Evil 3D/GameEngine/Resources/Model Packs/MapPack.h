#pragma once
#include <string>
#include <glm.hpp>

/// Enum class for Map Packs
enum class MapPack {
    Ice,
    Volcano,
    Rocky,
    Plain
};

/// Struct to Define Map Attributes
struct MapAttributes {
    std::string name;          // Map name
    std::string terrainModel;  // Path to the terrain model
    std::string texturePath;   // Path to the texture for the terrain
    glm::vec3 ambientColor;    // Ambient lighting color for the map
};

/// Function to Get Attributes for Each Map Pack
inline MapAttributes getMapAttributes(MapPack pack) {
    switch (pack) {
    case MapPack::Ice:
        return {
            "Ice Map",
            "assets/maps/ice.obj",
            "assets/maps/ice.png",
            glm::vec3(0.5f, 0.7f, 1.0f), // Cool blue ambient light
        };

    case MapPack::Volcano:
        return {
            "Volcano Map",
            "assets/maps/volcano.obj",
            "assets/maps/volcano.png",
            glm::vec3(0.9f, 0.2f, 0.2f), // Fiery red ambient light
        };

    case MapPack::Rocky:
        return {
            "Rocky Map",
            "assets/maps/rocky.obj",
            "assets/maps/rocky.png",
            glm::vec3(0.6f, 0.6f, 0.6f), // Neutral gray ambient light
        };

    case MapPack::Plain:
        return {
            "Plain Map",
            "assets/maps/plain.obj",
            "assets/maps/plain.png",
            glm::vec3(0.3f, 0.8f, 0.3f), // Lush green ambient light
        };

    default:
        return { "Unknown", "", "", glm::vec3(1.0f, 1.0f, 1.0f)};
    }
}