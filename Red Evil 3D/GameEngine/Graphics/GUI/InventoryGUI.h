#pragma once
#include "../imgui/imgui.h"
#include <map>
#include <string>

class InventoryGUI {
private:
    std::map<std::string, std::string>& inventoryItemsAndAmounts; // Pointer to inventory data
    bool isVisible;                                               // Tracks if the inventory is being displayed
    int* screenWidth;
    int* screenHeight;

public:
    // Constructor
    InventoryGUI(std::map<std::string, std::string>& inventory, int* screenWidth, int* screenHeight)
        : inventoryItemsAndAmounts(inventory), isVisible(false), screenWidth(screenWidth), screenHeight(screenHeight) {
    }

    // Set visibility
    void setVisibility(bool visibility) {
        isVisible = visibility;
    }

    // Render the inventory GUI
    void render() {
        if (!isVisible) return;

        // Compute position and size
        ImVec2 windowSize((*screenWidth) * 0.4f, (*screenHeight) * 0.5f); // 40% width, 50% height
        ImVec2 windowPos((*screenWidth) * 0.3f, (*screenHeight) * 0.25f); // Centered position

        // Set position and size
        ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(windowSize);

        // Begin inventory window
        ImGui::Begin("Inventory", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

        // Render inventory items
        for (const auto& item : inventoryItemsAndAmounts) {
            ImGui::BulletText("%s: %s", item.first.c_str(), item.second.c_str());
        }

        ImGui::End();
    }
};
