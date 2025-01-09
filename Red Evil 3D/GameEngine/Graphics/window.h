#pragma once
#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "GUI/MenuGUI.h"
#include "GUI/InstructionsGUI.h"
#include "../Graphics/imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "../Game/Characters/Main Character/Main_Char.h"
#define MAX_KEYBOARD 512
#define MAX_MOUSE 8

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

class Window
{
	private:
		char* name;
		int width, height;
		GLFWwindow* window;

		bool keys[MAX_KEYBOARD];
		bool mouseButtons[MAX_MOUSE];
		bool paused;
		bool animatingLiquids;
		bool spectateMode;
		double xpos;
		double ypos;
		double lastMenuToggleTime; // Tracks the time of the last menu toggle

		MenuGUI menu;
		InstructionsGUI instructions;

	public:
		Window(char* name, int width, int height);
		~Window();
		GLFWwindow* getWindow();

		void init();
		void update();
		void clear();

		void setKey(int key, bool ok);
		void setMouseButton(int button, bool ok);
		void setMousePos(double xpos, double ypos);
		void getMousePos(double &xpos, double &ypos);
		bool isPressed(int key);
		bool isMousePressed(int button);

		 int getWidth() const;
		 int getHeight() const;

		bool isPaused();
		bool isSpectating();
		bool isAnimatingLiquids();

		void handleEscapeToMenuInput();
		void renderGUI(Camera& camera, Main_Char& mc);
};