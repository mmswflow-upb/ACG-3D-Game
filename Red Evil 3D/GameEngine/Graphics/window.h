#pragma once
#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "GUI/MenuGUI.h"
#include "GUI/HealthBarGUI.h"
#include "GUI/TasksGUI.h"
#include "GUI/ToolGUI.h"
#include "GUI/InventoryGUI.h"

#include "../Graphics/imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "../Game/Trackers/GameTracker.h"
#define MAX_KEYBOARD 512
#define MAX_MOUSE 8

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

class Window {
private:
    char* name;
    int* width;               // Pointer to width
    int* height;              // Pointer to height
    GLFWwindow* window;

    bool keys[MAX_KEYBOARD];
    bool mouseButtons[MAX_MOUSE];
    bool* paused;             // Pointer to paused
    bool* animating;   // Pointer to animatingLiquids
    bool* spectateMode;       // Pointer to spectateMode
    double xpos;
    double ypos;
    double lastMenuToggleTime; // Tracks the time of the last menu toggle

    Main_Char* mc;
    Camera* camera;

    MenuGUI menu;
    HealthBarGUI healthbar;
    TasksGUI taskGUI;
    ToolGUI toolGUI;
    InventoryGUI invGUI;

public:
    Window(
        char* name,
        int* width,
        int* height,
        bool* specMode,
        bool* animat,
        bool* paus,
        std::pair<std::string, std::string>& taskTitleAndDescription,
        std::map<std::string, std::string>& inventoryItemsAndAmounts,
        std::pair<std::string, std::string>& heldItemNameAndAmount,
        Main_Char* mc,
        Friend* friendCharacter,
        Camera* camera
    );
    ~Window();
    GLFWwindow* getWindow();

    void init();
    void update();
    void clear();

    void setKey(int key, bool ok);
    void setMouseButton(int button, bool ok);
    void setMousePos(double xpos, double ypos);
    void getMousePos(double& xpos, double& ypos);
    bool isPressed(int key);
    bool isMousePressed(int button);

    int getWidth() const;
    int getHeight() const;

    void renderGUI();
    void setPointers(Main_Char* newMainCharacter, Friend* newFriendCharacter, Camera* cam);
    void handleUIKeyBinds();
};
