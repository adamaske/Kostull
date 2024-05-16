#include "Graphics.h"
#include <iostream>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "spdlog/spdlog.h"
#include "Logger.h"

static void glfw_error_callback(int error, const char* description)
{
    spdlog::error( "GLFW Error [" + std::to_string(error) + "] " + std::string(description));
}

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
    glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
    View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    return Projection * View * Model;
}

Graphics::Graphics() {

}

Graphics::~Graphics() {

}

int Graphics::Init(std::string title) {


    auto* sd = &Logger::log_callback_functions;
    std::cout << "GRAPHICS INIT: " << sd << "\n";
    if (glfwInit() != GLFW_TRUE) {
        spdlog::error( "GLFW Init failed.");
        return 0;
    }
  
    glfwSetErrorCallback(glfw_error_callback); // Callback
   
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window with graphics context
    window = glfwCreateWindow(1280, 720, title.c_str(), nullptr, nullptr);
    if (!window) {
        spdlog::error( "Window creation failed.");
        return 0;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        spdlog::error( "GLAD Init failed.");
        return 0;
    }
    bool show_demo_window = true;
    bool show_another_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); //(void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\JetBrainsMono Nerd Font.ttf", 18.0f);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    //Logger Window
    auto lw = std::make_shared<LoggerWindow>();
    AppendGUIWindow(lw);

    return 1;
}

int Graphics::Frame() {
    int result = Render();
    if (result == 0) {
        return 0;
    }

    return 1;
}
int Graphics::Render() {
    if (glfwWindowShouldClose(window)) {
        return 0;
    }

    int result = 0;

    glfwPollEvents();

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (auto gui_window : gui_windows) {
        gui_window->Render();
    }

    auto r = clear_color.x;
    auto g = clear_color.y;
    auto b = clear_color.z;
    auto alpha = clear_color.w;

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(r * alpha, g * alpha, b * alpha, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);

    return 1;
}

int Graphics::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 1;
}

void Graphics::AppendGUIWindow(std::shared_ptr<GUIWindow> gui_window) {
    gui_windows.push_back(gui_window);
}

