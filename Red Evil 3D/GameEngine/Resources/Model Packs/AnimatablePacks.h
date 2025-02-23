#pragma once
#include <string>
#include <glm.hpp>

/// Enum class for Animatable Types
enum class AnimatableType {
    NormalTree,
    BurntTree,
    SeaWater
};

/// Struct for Animatable Model Attributes
struct AnimatableModelAttributes {
    std::string modelPath;
    std::string texturePath;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
};

/// Struct for Animatable Game Attributes
struct AnimatableGameAttributes {
    float scale;      // Scale of the object
    glm::vec3 offset; // Offset for the animation position
};

/// Function to get Animatable Model Attributes (shaders and paths)
inline AnimatableModelAttributes getAnimatableModelAttributes(AnimatableType type) {
    switch (type) {
    case AnimatableType::SeaWater:
        return {
            "Resources/Models/Animatable/SeaWater/seawater.obj",
            "",
            "Shaders/Animatable Shaders/SeaWater/seawater_vertex_shader.glsl",
            "Shaders/Animatable Shaders/SeaWater/seawater_fragment_shader.glsl"
        };
    
        
	case AnimatableType::NormalTree:
        return {
            "Resources/Models/Animatable/Trees/NormalTree/normalTree.obj",
			"Resources/Models/Animatable/Trees/NormalTree/normalTree.bmp",
			"Shaders/Animatable Shaders/Trees/NormalTree/normalTree_vertex_shader.glsl",
			"Shaders/Animatable Shaders/Trees/NormalTree/normalTree_fragment_shader.glsl"
		};

    case AnimatableType::BurntTree:
        return {
            "Resources/Models/Animatable/Trees/LavaTree/lavaTree.obj",
            "Resources/Models/Animatable/Trees/LavaTree/lavaTree.bmp",
            "Shaders/Animatable Shaders/Trees/LavaTree/lavaTree_vertex_shader.glsl",
            "Shaders/Animatable Shaders/Trees/LavaTree/lavaTree_fragment_shader.glsl"
        };
    default:
        return { "", "", "", "" };
    }
}

/// Function to get Animatable Game Attributes (modifies arguments by reference)
inline void getAnimatableGameAttributes(AnimatableType type, float& scale, glm::vec3& offset) {
    switch (type) {
    case AnimatableType::SeaWater:
        scale = 20.0f;
        offset = glm::vec3(0.0f, -2.0f, 0.0f);
        break;
    
    case AnimatableType::NormalTree:
		scale = 6.0f;
		offset = glm::vec3(0.0f);
		break;
	case AnimatableType::BurntTree:
		scale = 6.0f;
		offset = glm::vec3(0.0f);
		break;

    default:
        scale = 1.0f;
        offset = glm::vec3(0.0f);
        break;
    }
}
