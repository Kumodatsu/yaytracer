#include "rendering/window.hpp"
#include "logging.hpp"
#include "arcana.hpp"

namespace yay {

  Window::Window(const std::string& title, U32 width, U32 height)
    : m_title(title)
    , m_width(width)
    , m_height(height)
    , m_handle(nullptr)
  {
    if (!glfwInit()) {
      YAY_LOG(Fatal) << "Failed to initialize GLFW.";
    }
    YAY_LOG(Info) << "Initialized GLFW.";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    m_handle = glfwCreateWindow(m_width, m_height, m_title.c_str(),
      nullptr, nullptr);
    if (!m_handle) {
      glfwTerminate();
      YAY_LOG(Fatal) << "Failed to create window.";
    }
    YAY_LOG(Info) << "Created window.";
    glfwMakeContextCurrent(m_handle);
    glfwSetWindowUserPointer(m_handle, this);
    glfwSetKeyCallback(m_handle,
      [](GLFWwindow* handle, int keycode, int, int action, int) {
        Window* window =
          reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
        const Key key = static_cast<Key>(keycode);
        switch (action) {
          case GLFW_PRESS:
            window->on_key_pressed(*window, key);
            break;
          case GLFW_RELEASE:
            window->on_key_released(*window, key);
            break;
        }
      }
    );
  }

  Window::~Window() {
    glfwTerminate();
    YAY_LOG(Info) << "Terminated GLFW.";
  }

  bool Window::is_close_requested() const {
    return glfwWindowShouldClose(m_handle);
  }

  void Window::poll_events() const {
    glfwPollEvents();
  }

  bool Window::is_key_down(Key key) const {
    return glfwGetKey(m_handle, underlying_cast(key)) == GLFW_PRESS;
  }

}
