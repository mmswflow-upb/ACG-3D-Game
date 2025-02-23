#pragma once
#include "../imgui/imgui.h"
#include "../../Camera/camera.h"
#include "../../Game/Characters/Main Character/Main_Char.h"

class MenuGUI {
private:
    bool* paused;           // Pointer to paused
    bool isVisible;
    bool* spectateMode;
    bool* showAnimation;
    Camera* camera;         // Pointer to Camera
    Main_Char* mc;          // Pointer to Main Character
    int* screenWidth;       // Pointer to screenWidth
    int* screenHeight;      // Pointer to screenHeight

public:
    MenuGUI(bool* paused, bool* specMode,bool* showAnim, Camera* cam, Main_Char* mainCharacter, int* screenWidth, int* screenHeight)
        : paused(paused), spectateMode(specMode), isVisible(false), showAnimation(showAnim),
        camera(cam), screenWidth(screenWidth), screenHeight(screenHeight), mc(mainCharacter) {
    }

    void toggleVisibility() {
        isVisible = !isVisible;
        *paused = isVisible; // Update the value pointed to by paused
    }

    void setPointers(Main_Char* mainCharacter, Camera* cam) {
        mc = mainCharacter;
        camera = cam;
    }

    void render() {
        if (!isVisible) return;

        // Compute window size and center position
        float menuWidth = (*screenWidth) * 0.3f;
        float menuHeight = (*screenHeight) * 0.4f;
        ImVec2 menuSize(menuWidth, menuHeight);
        ImVec2 centerPos(((*screenWidth) - menuWidth) / 2.0f, ((*screenHeight) - menuHeight) / 2.0f);

        ImGui::SetNextWindowPos(centerPos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(menuSize);

        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        ImGui::Begin("Menu", nullptr, windowFlags);

        // Menu title
        ImGui::Text("Menu Options");

        ImGui::Spacing();
        if (ImGui::Checkbox("Spectate Mode", spectateMode)) {
            if (spectateMode && *spectateMode == false) {
                glm::vec3 characterPos = mc->getPosition();
                glm::vec3 newCameraPos = characterPos;
                newCameraPos.y = 20.5f;
                camera->setCameraPosition(newCameraPos);
            }
        }

		if (ImGui::Checkbox("Show Animations", showAnimation)) {
			if (*showAnimation == false) {
				std::cout << "Animations are now off\n";
            }
            else {
				std::cout << "Animations are now on\n";
            }
		}

        // Close button
        if (ImGui::Button("Close")) {
            toggleVisibility();
        }

        ImGui::End();
    }
};
