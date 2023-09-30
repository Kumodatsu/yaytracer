#include "rendering/window.hpp"
#include "logging.hpp"

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

}
