#pragma once
#include <string>
#include <vector>

enum class CharacterPack {
    Main,
    Ice_Dyno,
    Fire_Dyno,
    Earth_Dyno
};

struct CharacterAttributes {
    float health;
    float runningSpeed;
    std::vector<CharacterPack> vulnerableTo;
    std::string texturePath;
    std::string modelPath;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
};

inline CharacterAttributes getCharacterAttributes(CharacterPack pack) {
    switch (pack) {
    case CharacterPack::Main:
        return { 100.0f, 5.0f, {CharacterPack::Fire_Dyno, CharacterPack::Ice_Dyno, CharacterPack::Earth_Dyno},
                 "", "../Models/Characters/main_char/main_char.obj",
                 "", "" };

    case CharacterPack::Ice_Dyno:
        return { 150.0f, 3.5f, {CharacterPack::Main},
                 "", "../Models/Characters/ice_dyno/ice_dyno.obj",
                 "", "" };

    default:
        return { 0.0f, 0.0f, {}, "", "", "", "" };
    }
}
