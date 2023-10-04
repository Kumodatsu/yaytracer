cmake_minimum_required(VERSION 3.23.0)

project(
  yaytracer
  VERSION     0.1.0
  DESCRIPTION "Yay! A simple raytracer in C++ made for fun."
  LANGUAGES   CXX
)

add_executable(
  yaytracer
  "src/main.cpp"
  "src/app.cpp"
  "src/logging.cpp"
  "src/rendering/pixel_buffer.cpp"
  "src/rendering/texture.cpp"
  "src/rendering/renderer.cpp"
  "src/rendering/window.cpp"
  "src/graphics/camera.cpp"
  "src/input/key.cpp"
)

set_target_properties(
  yaytracer
  PROPERTIES CXX_STANDARD 20
)

if(MSVC)
  target_compile_options(yaytracer PRIVATE "/W4")
else()
  target_compile_options(yaytracer PRIVATE "-Wall")
endif()

target_compile_definitions(
  yaytracer
  PRIVATE "GLFW_INCLUDE_NONE"
)

target_include_directories(
  yaytracer
  PRIVATE "src"
  PRIVATE "${CMAKE_SOURCE_DIR}/lua/lua"
  PRIVATE "${CMAKE_SOURCE_DIR}/glad/glad/include"
  PRIVATE "${CMAKE_SOURCE_DIR}/glfw/glfw/include"
  PRIVATE "${CMAKE_SOURCE_DIR}/imgui/imgui"
)

target_link_libraries(
  yaytracer
  PRIVATE "lua"
  PRIVATE "glad"
  PRIVATE "glfw"
  PRIVATE "imgui"
)
