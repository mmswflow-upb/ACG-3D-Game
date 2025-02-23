#include "window.h"

Window::Window(
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
    Camera* cam
) : name(name),
width(width),
height(height),
spectateMode(specMode),
animating(animat),
paused(paus),
mc(mc),
camera(cam),
menu(paused, spectateMode,animat, cam, mc, width, height),
healthbar(100.0f, mc, 100.0f, friendCharacter, width, height),
taskGUI(taskTitleAndDescription, paused, width, height),
toolGUI(heldItemNameAndAmount, paused, width, height),
invGUI(inventoryItemsAndAmounts, width, height) {

    
    lastMenuToggleTime = 0.0;

    init();

    // Initialize input states
    for (int i = 0; i < MAX_KEYBOARD; i++) keys[i] = false;
    for (int i = 0; i < MAX_MOUSE; i++) mouseButtons[i] = false;
}

Window::~Window() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

void Window::init() {
    if (!glfwInit()) {
        std::cout << "Error initializing glfw!" << std::endl;
    }
    else {
        std::cout << "Successfully initialized glfw!" << std::endl;
    }

    window = glfwCreateWindow(*width, *height, name, NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create a GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Callbacks for user input
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error initializing glew!" << std::endl;
    }
    else {
        std::cout << "Successfully initialized glew!" << std::endl;
    }

    std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
    glEnable(GL_BLEND);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Initialize ImGui backend for GLFW and OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Window::update() {
    glfwPollEvents();
    glfwGetFramebufferSize(window, width, height);
    glViewport(0, 0, *width, *height);
    handleUIKeyBinds();

    if (*paused) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    glfwSwapBuffers(window);
}

void Window::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLFWwindow* Window::getWindow() {
    return window;
}

int Window::getWidth() const {
    return *width;
}

int Window::getHeight() const {
    return *height;
}

void Window::setKey(int key, bool ok) {
    keys[key] = ok;
}

void Window::setMouseButton(int button, bool ok) {
    mouseButtons[button] = ok;
}

void Window::setMousePos(double xpos, double ypos) {
    this->xpos = xpos;
    this->ypos = ypos;
}

void Window::getMousePos(double& xpos, double& ypos) {
    xpos = this->xpos;
    ypos = this->ypos;
}

bool Window::isPressed(int key) {
    return keys[key];
}

bool Window::isMousePressed(int button) {
    return mouseButtons[button];
}

void Window::setPointers(Main_Char* newMainCharacter, Friend* newFriendCharacter, Camera* cam) {
    healthbar.setCharacterPointers(newMainCharacter, newFriendCharacter);
    menu.setPointers(newMainCharacter, cam);
    mc = newMainCharacter;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Window* wind = (Window*)glfwGetWindowUserPointer(window);

    if (action != GLFW_RELEASE)
        wind->setKey(key, true);
    else
        wind->setKey(key, false);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    Window* wind = (Window*)glfwGetWindowUserPointer(window);

    if (action != GLFW_RELEASE)
        wind->setMouseButton(button, true);
    else
        wind->setMouseButton(button, false);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    Window* wind = (Window*)glfwGetWindowUserPointer(window);
    wind->setMousePos(xpos, ypos);
}

void Window::renderGUI() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    menu.render();
    healthbar.render();
    taskGUI.render();
    invGUI.render();
    toolGUI.render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Window::handleUIKeyBinds() {
    double currentTime = glfwGetTime();

    if (isPressed(GLFW_KEY_ESCAPE) && (currentTime - lastMenuToggleTime >= 1.0)) {
        lastMenuToggleTime = currentTime;
        menu.toggleVisibility();
    }

    if (!(*paused)) {
        healthbar.setVisibility(true);

        if (isPressed(GLFW_KEY_E)) {
            invGUI.setVisibility(true);
        }
        else {
            invGUI.setVisibility(false);
        }
    }
    else {
        healthbar.setVisibility(false);
        invGUI.setVisibility(false);
    }
}
