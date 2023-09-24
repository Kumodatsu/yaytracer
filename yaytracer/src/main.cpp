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

int main(int, char**) {
  {
    lua_State* lua = luaL_newstate();
    lua_close(lua);
  }

  const int glfw_succeeded = glfwInit();
  if (glfw_succeeded == 0) {
    std::cout << "Failed to initialize GLFW." << std::endl;
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* window =
    glfwCreateWindow(640, 480, "Yaytracer", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    std::cout << "Failed to create window." << std::endl;
    return -1;
  }
  glfwMakeContextCurrent(window);
  const int glad_succeeded =
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
  if (glad_succeeded == 0) {
    std::cout << "Failed to initialize Glad." << std::endl;
    return -1;
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();

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
