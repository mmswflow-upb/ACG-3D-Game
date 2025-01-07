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
    const float health;
    const float runningSpeed;
    const std::vector<CharacterPack> vulnerableTo;
    const std::string texturePath;
    const std::string modelPath;
};

inline CharacterAttributes getCharacterAttributes(CharacterPack pack) {
    switch (pack) {
    case CharacterPack::Main:
        return { 100.0f, 5.0f, {CharacterPack::Fire_Dyno, CharacterPack::Ice_Dyno, CharacterPack::Earth_Dyno}, "assets/characters/Main.png", "assets/models/Main.obj"};

    case CharacterPack::Ice_Dyno:
        return { 150.0f, 3.5f, {CharacterPack::Main}, "assets/characters/IceDyno.png", "assets/models/IceDyno.obj" };

    case CharacterPack::Fire_Dyno:
        return { 120.0f, 4.0f, {CharacterPack::Main}, "assets/characters/FireDyno.png", "assets/models/FireDyno.obj" };

    case CharacterPack::Earth_Dyno:
        return { 200.0f, 2.5f, {CharacterPack::Main}, "assets/characters/EarthDyno.png", "assets/models/EarthDyno.obj" };

    default:
        return { 0.0f, 0.0f, {}, "", "" };
    }
}
