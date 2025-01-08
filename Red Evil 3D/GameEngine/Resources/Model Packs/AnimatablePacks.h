#pragma once
#include <string>
#include <glm.hpp>

/// Enum class for Animatable Types
enum class AnimatableType {
    Waterfall,
    FirePit,
    SpinningWheel
};

/// Struct for Animatable Model Attributes
struct AnimatableModelAttributes {
    std::string texturePath;
    std::string modelPath;
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
    case AnimatableType::Waterfall:
        return {
            "../Textures/Animatable/waterfall.png",
            "../Models/Animatable/waterfall.obj",
            "../../Shaders/Animatable Shaders/waterfall_vertex.glsl",
            "../../Shaders/Animatable Shaders/waterfall_fragment.glsl"
        };
    case AnimatableType::FirePit:
        return {
            "../Textures/Animatable/firepit.png",
            "../Models/Animatable/firepit.obj",
            "../../Shaders/Animatable Shaders/firepit_vertex.glsl",
            "../../Shaders/Animatable Shaders/firepit_fragment.glsl"
        };
    case AnimatableType::SpinningWheel:
        return {
            "../Textures/Animatable/wheel.png",
            "../Models/Animatable/wheel.obj",
            "../../Shaders/Animatable Shaders/spinningwheel_vertex.glsl",
            "../../Shaders/Animatable Shaders/spinningwheel_fragment.glsl"
        };
    default:
        return { "", "", "", "" };
    }
}

/// Function to get Animatable Game Attributes (modifies arguments by reference)
inline void getAnimatableGameAttributes(AnimatableType type, float& scale, glm::vec3& offset) {
    switch (type) {
    case AnimatableType::Waterfall:
        scale = 1.5f;
        offset = glm::vec3(0.0f, -2.0f, 0.0f);
        break;
    case AnimatableType::FirePit:
        scale = 1.0f;
        offset = glm::vec3(0.0f, 0.0f, 0.0f);
        break;
    case AnimatableType::SpinningWheel:
        scale = 0.75f;
        offset = glm::vec3(1.0f, 0.0f, 0.0f);
        break;
    default:
        scale = 1.0f;
        offset = glm::vec3(0.0f);
        break;
    }
}
