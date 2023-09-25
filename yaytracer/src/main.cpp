#include <iostream>
extern "C" {
  #include <lua.h>
  #include <lauxlib.h>
  #include <lualib.h>
}
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "logging.hpp"

int main(int, char**) {
  {
    lua_State* lua = luaL_newstate();
    lua_close(lua);
  }

  const int glfw_succeeded = glfwInit();
  if (glfw_succeeded == 0) {
    YAY_LOG(Fatal) << "Failed to initialize GLFW.";
  }
  YAY_LOG(Info) << "Initialized GLFW.";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* window =
    glfwCreateWindow(640, 480, "Yaytracer", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    YAY_LOG(Fatal) << "Failed to create window.";
  }
  YAY_LOG(Info) << "Created window.";
  glfwMakeContextCurrent(window);
  const int glad_succeeded =
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
  if (glad_succeeded == 0) {
    glfwTerminate();
    YAY_LOG(Fatal) << "Failed to initialize Glad.";
  }
  YAY_LOG(Info) << "Initialized Glad.";

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();
  YAY_LOG(Info) << "Initialized Dear ImGui.";

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
