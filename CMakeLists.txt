cmake_minimum_required(VERSION 3.23.0)

project(
  yaytracer
  VERSION     0.1.0
  DESCRIPTION "Yay! A simple raytracer in C++ made for fun."
  LANGUAGES   CXX
)

add_subdirectory("libs/lua")
add_subdirectory("libs/glad")
add_subdirectory("libs/glfw")
add_subdirectory("libs/imgui")
add_subdirectory("yaytracer")
