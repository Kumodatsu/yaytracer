#include "logging.hpp"
#include "rendering/pixel_buffer.hpp"
#include "rendering/renderer.hpp"
#include <iostream>
#include <imgui.h>

#include "math/math.hpp"
#include "math/vector.hpp"

#include "graphics/ray.hpp"
#include "graphics/camera.hpp"

int main(int, char**) {
  using namespace yay;

  static constexpr U32
    width  = 960,
    height = 540;
  
  PixelBuffer buffer(width, height);
  buffer.clear(colors::Blue);
  Window window("Yaytracer", width, height);
  Renderer renderer(window);

  Camera camera(width, height, 1.0f, Vector(0.0f, 0.0f, 0.0f));
  const auto rays = camera.rays();
  for (UIndex v = 0; v < height; ++v) {
    for (UIndex u = 0; u < width; ++u) {
      const auto direction = rays[u + width * v].direction;
      const auto a = 0.5f * direction.y + 1.0f;
      const auto color = blend(a, colors::White, Color(0.5f, 0.7f, 1.0f));
      buffer.at(u, v) = color;
    }
  }

  while (!window.is_close_requested()) {
    renderer.begin_frame();
    renderer.render(buffer);
    renderer.end_frame();
    window.poll_events();
  }

  return 0;
}
