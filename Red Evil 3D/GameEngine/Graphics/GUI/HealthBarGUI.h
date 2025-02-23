#pragma once
#include "../imgui/imgui.h"
#include <string>
#include "../../Game/Characters/Friends/Friend.h"
#include "../../Game/Characters/Main Character/Main_Char.h"

class HealthBarGUI {
private:
    Main_Char* mc;                // Pointer to the main character
    float marioMaxHealth;
    Friend* laylasaurus;          // Pointer to the friend character
    float laylasaurusMaxHealth;
    bool isVisible;               // Visibility state of the health bars
    float widthRatio;             // Width as a percentage of the screen width
    float heightRatio;            // Height as a percentage of the screen height
    int* screenWidth;             // Pointer to screenWidth
    int* screenHeight;            // Pointer to screenHeight

public:
    // Constructor
    HealthBarGUI(
        float marioMaxHealth,
        Main_Char* mainCharacter,
        float laylasaurusMaxHealth,
        Friend* friendCharacter,
        int* screenWidth,
        int* screenHeight,
        float widthRatio = 0.3f,
        float heightRatio = 0.05f
    ) : mc(mainCharacter),
        marioMaxHealth(marioMaxHealth),
        laylasaurus(friendCharacter),
        laylasaurusMaxHealth(laylasaurusMaxHealth),
        isVisible(true),
        widthRatio(widthRatio),
        heightRatio(heightRatio),
        screenWidth(screenWidth),
        screenHeight(screenHeight) {
    }

    // Set visibility of the health bars
    void setVisibility(bool visible) {
        isVisible = visible;
    }

    // Update character pointers
    void setCharacterPointers(Main_Char* newMainCharacter, Friend* newFriendCharacter) {
        mc = newMainCharacter;
        laylasaurus = newFriendCharacter;
    }

    // Render both health bars
    void render() {
        if (!isVisible) return;

        // Calculate size based on screen dimensions
        ImVec2 barSize((*screenWidth) * widthRatio, (*screenHeight) * heightRatio);

        // Health data for Mario
        float marioHealthFraction = mc->getHealth() / marioMaxHealth;
        std::string marioOverlayText = "Mario: " + std::to_string(static_cast<int>(mc->getHealth())) + " / " + std::to_string(static_cast<int>(marioMaxHealth));

        // Health data for Laylasaurus
        float laylasaurusHealthFraction = laylasaurus->getHealth() / laylasaurusMaxHealth;
        std::string laylasaurusOverlayText = "Laylasaurus: " + std::to_string(static_cast<int>(laylasaurus->getHealth())) + " / " + std::to_string(static_cast<int>(laylasaurusMaxHealth));

        // Position for the top-left corner
        ImVec2 position(10.0f, 10.0f);

        // Render both health bars
        renderHealthBars(barSize, marioHealthFraction, marioOverlayText, laylasaurusHealthFraction, laylasaurusOverlayText, position);
    }

private:
    void renderHealthBars(const ImVec2& barSize,
        float healthFraction1, const std::string& overlayText1,
        float healthFraction2, const std::string& overlayText2,
        const ImVec2& position) {
        // Calculate total height for the window
        float totalHeight = (barSize.y * 2) + 80.0f; // 2 bars, labels, and spacing
        float totalWidth = barSize.x + 20.0f;

        // Set window position and size
        ImGui::SetNextWindowPos(position);
        ImGui::SetNextWindowSize(ImVec2(totalWidth, totalHeight));

        // Add scrollbars if content exceeds window size
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoScrollbar;

        ImGui::Begin("HealthBars", nullptr, flags);

        // Render Mario's health bar
        ImGui::Text(overlayText1.c_str());
        ImGui::ProgressBar(healthFraction1, barSize);

        // Add spacing
        ImGui::Dummy(ImVec2(0.0f, 10.0f));

        // Render Laylasaurus's health bar
        ImGui::Text(overlayText2.c_str());
        ImGui::ProgressBar(healthFraction2, barSize);

        ImGui::End();
    }

};
