#include "logging.hpp"
#include "rendering/pixel_buffer.hpp"
#include "rendering/renderer.hpp"
#include <iostream>
#include <imgui.h>

int main(int, char**) {
  using namespace yay;

  PixelBuffer buffer(640, 480);
  buffer.clear(colors::Blue);
  Window window("Yaytracer", 640, 480);
  Renderer renderer(window);

  while (!window.is_close_requested()) {
    renderer.begin_frame();
    renderer.render(buffer);
    renderer.end_frame();
    window.poll_events();
  }

  return 0;
}
