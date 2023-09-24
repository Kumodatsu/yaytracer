cmake_minimum_required(VERSION 3.23.0)

project(
  glad
  DESCRIPTION "OpenGL loader"
  LANGUAGES   C
)

add_library(
  glad STATIC
  "glad/src/glad.c"
)

target_include_directories(
  glad
  PUBLIC "glad/include"
)
