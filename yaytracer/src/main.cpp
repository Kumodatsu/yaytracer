#include "logging.hpp"
#include "rendering/pixel_buffer.hpp"
#include "rendering/renderer.hpp"
#include <iostream>
#include <imgui.h>

#include "math/math.hpp"
#include "math/vector.hpp"

#include "graphics/ray.hpp"
#include "graphics/camera.hpp"
#include "graphics/sphere.hpp"

int main(int, char**) {
  using namespace yay;

  static constexpr U32
    width  = 960,
    height = 540;
  
  PixelBuffer buffer(width, height);
  buffer.clear(colors::Blue);
  Window window("Yaytracer", width, height);
  Renderer renderer(window);

  Subscriber on_key_pressed(window.on_key_pressed, [](const Window&, Key key) {
    std::cout << key << " pressed" << std::endl;
  });
  Subscriber on_key_released(window.on_key_released, [](const Window&, Key key) {
    std::cout << key << " released" << std::endl;
  });

  Sphere sphere(Vector(0.0f, 0.0f, -1.0f), 0.5f);

  Camera camera(width, height, 0.5f, Vector(0.0f, 0.0f, 0.0f));
  const auto rays = camera.rays();
  for (UIndex v = 0; v < height; ++v) {
    for (UIndex u = 0; u < width; ++u) {
      Color color;
      const auto& ray = rays[u + width * v];
      const auto intersection = sphere.intersect(ray);
      if (intersection.has_value()) {
        // color = intersection->color;
        const Vector& normal = intersection->normal;
        color = 0.5f * Color(normal.x + 1.0f, normal.y + 1.0f, normal.z + 1.0f);
      } else {
        const auto a = 0.5f * ray.direction.y + 1.0f;
        color = blend(a, colors::White, Color(0.5f, 0.7f, 1.0f));
      }
      buffer.at(u, v) = color;
    }
  }

  while (!window.is_close_requested()) {
    renderer.begin_frame();
    renderer.render(buffer);
    if (window.is_key_down(Key::Space)) {
      YAY_LOG(Info) << "SPACE!";
    }
    renderer.end_frame();
    window.poll_events();
  }

  return 0;
}
