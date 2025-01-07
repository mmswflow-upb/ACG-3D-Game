#pragma once
#include "../imgui/imgui.h"
#include <string>

class HealthBar {
private:
    float currentHealth; // Current health
    float maxHealth;     // Maximum health
    bool isVisible;      // Visibility state of the health bar

    float widthRatio;    // Width as a percentage of the screen width
    float heightRatio;   // Height as a percentage of the screen height

public:
    // Constructor
    HealthBar(float maxHealth, float widthRatio = 0.3f, float heightRatio = 0.05f)
        : maxHealth(maxHealth), currentHealth(maxHealth), isVisible(true),
        widthRatio(widthRatio), heightRatio(heightRatio) {
    }

    // Setters
    void setHealth(float health) {
        currentHealth = health;
        if (currentHealth < 0) currentHealth = 0;
        if (currentHealth > maxHealth) currentHealth = maxHealth;
    }

    void setMaxHealth(float health) {
        maxHealth = health;
        if (currentHealth > maxHealth) currentHealth = maxHealth;
    }

    void setVisible(bool visible) {
        isVisible = visible;
    }

    // Getters
    float getHealth() const { return currentHealth; }
    float getMaxHealth() const { return maxHealth; }
    bool getVisible() const { return isVisible; }

    // Render the health bar at the top-left using relative sizes
    void render(int screenWidth, int screenHeight) {
        if (!isVisible) return;

        // Calculate health percentage
        float healthFraction = currentHealth / maxHealth;

        // Convert health to a string for overlay
        std::string overlayText = std::to_string(static_cast<int>(currentHealth)) + " / " + std::to_string(static_cast<int>(maxHealth));

        // Calculate size based on screen dimensions
        ImVec2 barSize(screenWidth * widthRatio, screenHeight * heightRatio);

        // Position the health bar at the top-left
        ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f)); // Small padding from top-left corner
        ImGui::SetNextWindowSize(barSize);

        // Render a window without title bar, resize, or collapse options
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse;
        ImGui::Begin("HealthBar", nullptr, flags);

        // Render the health bar inside the window
        ImGui::ProgressBar(healthFraction, ImVec2(-1.0f, 0.0f), overlayText.c_str()); // -1.0f for full width

        ImGui::End();
    }
};
