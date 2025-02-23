#pragma once
#include "../imgui/imgui.h"
#include <utility>

class TasksGUI {
private:
    bool* paused; // Pointer to track whether the game is paused
    std::pair<std::string, std::string>& taskTitleAndDescription;
    int* screenWidth;
    int* screenHeight;

public:
    // Constructor
    TasksGUI(std::pair<std::string, std::string>& taskTitleAndDesc, bool* paused, int* screenWidth, int* screenHeight)
        : paused(paused), taskTitleAndDescription(taskTitleAndDesc), screenWidth(screenWidth), screenHeight(screenHeight) {
    }

    // Render the Tasks GUI
    void render() {
        if (*paused) return; // Do not display if the game is paused

        // Compute relative position and size
        ImVec2 windowSize = ImVec2((*screenWidth) * 0.3f, (*screenHeight) * 0.2f); // 30% width, 20% height
        ImVec2 windowPos = ImVec2((*screenWidth) * 0.02f, (*screenHeight) * 0.78f); // Bottom-left corner with 2% padding

        // Set position and size for the window
        ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);

        // Begin a non-movable, non-resizable window with no title bar
        ImGui::Begin("Tasks Box", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

        // Display task title and description
        ImGui::TextWrapped(taskTitleAndDescription.first.c_str());
        ImGui::BulletText(taskTitleAndDescription.second.c_str());

        ImGui::End();
    }
};
