#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#if USE_GLAD
#include <glad/glad.h>  // OpenGL loader
#endif
#include <GLFW/glfw3.h> // Include glfw3.h after our OpenGL header.

#include <iostream>

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    return -1;
  }

  // Create a windowed GLFW window
  GLFWwindow *window =
      glfwCreateWindow(1280, 720, "Dear ImGui Example", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  // Make the window's OpenGL context current
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync

#if USE_GLAD
  // Initialize OpenGL loader (GLAD in this case)
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cerr << "Failed to initialize OpenGL loader!" << std::endl;
      return -1;
  }
#endif

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  // ImGuiIO& io = ImGui::GetIO();
  // io.ConfigFlags |=
  //     ImGuiConfigFlags_NavEnableKeyboard;           // Enable Keyboard Controls
  // io.ConfigFlags |=
  //     ImGuiConfigFlags_NavEnableGamepad;            // Enable Gamepad Controls
  // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // If using Docking Branch

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    // Poll and handle events
    glfwPollEvents();

    // Start a new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Render Hello, World!
    ImGui::Text("Hello, World!");
#if COMPILE_IMGUI_DEMO
    ImGui::ShowDemoWindow();
#endif
    // Render ImGui
    ImGui::Render();
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f); // Clear color
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap buffers
    glfwSwapBuffers(window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
