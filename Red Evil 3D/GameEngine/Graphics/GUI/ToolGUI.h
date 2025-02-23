#pragma once
#include "../imgui/imgui.h"
#include <glfw3.h>
#include <glew.h>
#include <string>
#include <utility>

class ToolGUI {
private:
    std::pair<std::string, std::string>& equippedTool; // Pointer to tool details
    bool* paused;                                      // Pointer to the game's pause state
    int* screenWidth;
    int* screenHeight;

public:
    // Constructor
    ToolGUI(std::pair<std::string, std::string>& toolDetails, bool* paused, int* screenWidth, int* screenHeight)
        : equippedTool(toolDetails), paused(paused), screenWidth(screenWidth), screenHeight(screenHeight) {
    }

    // Update the equipped tool
    void setEquippedTool(const std::pair<std::string, std::string>& toolInfo) {
        equippedTool = toolInfo;
    }

    // Render the tool GUI
    void render() {
        if (equippedTool.first == "No Tool Equipped" || *paused) return;

        // Set GUI dimensions based on screen size
        float guiWidth = (*screenWidth) * 0.2f;
        float guiHeight = (*screenHeight) * 0.1f;
        ImVec2 guiSize(guiWidth, guiHeight);

        // Position the GUI at the bottom-right corner
        ImVec2 bottomRightPos(
            (*screenWidth) - guiWidth - 20,
            (*screenHeight) - guiHeight - 20
        );

        ImGui::SetNextWindowPos(bottomRightPos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(guiSize);

        // Set window flags
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

        // Begin the GUI window
        ImGui::Begin("Tool Info", nullptr, windowFlags);

        // Display tool details
        ImGui::Text("Current Tool");
        ImGui::Spacing();
        ImGui::Text("%s", equippedTool.first.c_str());
        if (!equippedTool.second.empty()) {
            ImGui::Text("%s", equippedTool.second.c_str());
        }

        ImGui::End();
    }
};
