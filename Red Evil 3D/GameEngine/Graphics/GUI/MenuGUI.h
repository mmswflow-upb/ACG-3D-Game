#pragma once
#include "../imgui/imgui.h"
#include <glfw3.h>
#include <glew.h>
#include "../../Camera/camera.h"
#include "../../Game/Characters/Main Character/Main_Char.h"
class MenuGUI {
private:
    bool isVisible; // Tracks whether the menu is currently visible
    bool spectateMode; // Tracks the state of "Spectate Mode"
    bool showLiquidAnimation; // Tracks the state of "Show Liquid Animation"


public:
    MenuGUI() : isVisible(false), spectateMode(false), showLiquidAnimation(false) {}

    void toggleVisibility() {
        isVisible = !isVisible;
    }

    bool isMenuVisible() const {
        return isVisible;
    }

    void MenuGUI::render(bool& paused, bool& spectating, bool& animatingLiquids,GLFWwindow* window, Camera& camera, Main_Char& mc) {
        if (!isVisible) return;

        // Get the window size
        int screenWidth, screenHeight;
        glfwGetWindowSize(window, &screenWidth, &screenHeight);

        // Set the menu size as percentages of the screen size
        float menuWidth = screenWidth * 0.3f;  // 30% of screen width
        float menuHeight = screenHeight * 0.4f; // 40% of screen height
        ImVec2 menuSize(menuWidth, menuHeight);

        // Calculate the center position
        ImVec2 centerPos(
            (screenWidth - menuWidth) / 2.0f,
            (screenHeight - menuHeight) / 2.0f
        );

        ImGui::SetNextWindowPos(centerPos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(menuSize);

        // Disable the minimize arrow using ImGuiWindowFlags_NoCollapse
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse;

        // Begin the menu window with the specified flags
        ImGui::Begin("Menu", nullptr, windowFlags);

        // Centered Title
        ImVec2 windowSize = ImGui::GetWindowSize();
        float textWidth = ImGui::CalcTextSize("Menu Options").x;
        ImGui::SetCursorPosX((windowSize.x - textWidth) / 2.0f);
        ImGui::Text("Menu Options");

        // Add some spacing
        ImGui::Spacing();
        ImGui::Spacing();

        // Centered Checkbox: Spectate Mode
        float buttonWidth = menuWidth * 0.6f; // Buttons are 60% of menu width
        ImGui::SetCursorPosX((menuSize.x - buttonWidth) / 2.0f);
        if (ImGui::Checkbox("Spectate Mode", &spectateMode)) {
            spectating = !spectating;
            if (!spectating) {
                // Set camera position to character's position with an offset
                glm::vec3 characterPos = mc.getPosition();
                glm::vec3 newCameraPos = characterPos + glm::vec3(0.0f, 1.0f, 0.0f); // Adjust the Y offset as needed
                camera.setCameraPosition(newCameraPos);
                
            }
        }

        // Add some spacing
        ImGui::Spacing();

        // Centered Checkbox: Show Liquid Animation
        ImGui::SetCursorPosX((menuSize.x - buttonWidth) / 2.0f);
        if (ImGui::Checkbox("Show Liquid Animation", &showLiquidAnimation)) {
            animatingLiquids = !animatingLiquids;
        }

        // Add some spacing before moving to the bottom
        ImGui::Spacing();

        // Position Close Button Near the Bottom
        float closeButtonWidth = menuWidth * 0.4f; // Close button is 40% of menu width
        float bottomPadding = menuHeight * 0.1f;  // Padding from the bottom of the menu
        ImGui::SetCursorPosY(menuSize.y - bottomPadding - ImGui::GetFrameHeight());
        ImGui::SetCursorPosX((menuSize.x - closeButtonWidth) / 2.0f);
        if (ImGui::Button("Close", ImVec2(closeButtonWidth, 0.0f))) {
            isVisible = false;
            paused = false; // Unpause the game when the menu is closed
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Lock the mouse
        }

        ImGui::End();
    }
};
