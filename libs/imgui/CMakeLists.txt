cmake_minimum_required(VERSION 3.23.0)

project(
  imgui
  DESCRIPTION "Immediate mode UI library"
  LANGUAGES   CXX
)

add_library(
  imgui STATIC
  "imgui/imconfig.h"
  "imgui/imgui_demo.cpp"
  "imgui/imgui_draw.cpp"
  "imgui/imgui_internal.h"
  "imgui/imgui_tables.cpp"
  "imgui/imgui_widgets.cpp"
  "imgui/imgui.cpp"
  "imgui/imgui.h"
  "imgui/imstb_rectpack.h"
  "imgui/imstb_textedit.h"
  "imgui/imstb_truetype.h"
  "imgui/backends/imgui_impl_glfw.cpp"
  "imgui/backends/imgui_impl_glfw.h"
  "imgui/backends/imgui_impl_opengl3.cpp"
  "imgui/backends/imgui_impl_opengl3.h"
  "imgui/misc/cpp/imgui_stdlib.cpp"
  "imgui/misc/cpp/imgui_stdlib.h"
)

target_include_directories(
  imgui
  PUBLIC "imgui"
)

target_link_libraries(
  imgui
  PRIVATE "glfw"
)
