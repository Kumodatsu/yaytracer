#pragma once
#include "common.hpp"
#include <string>
#include <GLFW/glfw3.h>

namespace yay {

  class Window {
  public:
    Window(const std::string& title, U32 width, U32 height);
    ~Window();

    Window(const Window&)              = delete;
    Window& operator = (const Window&) = delete;
    Window(Window&&)                   = delete;
    Window& operator = (Window&&)      = delete;

    inline U32 width()  const { return m_width;  }
    inline U32 height() const { return m_height; }

    inline GLFWwindow* handle() { return m_handle; }
    inline const GLFWwindow* handle() const { return m_handle; }

    bool is_close_requested() const;
    void poll_events() const;
  private:
    std::string m_title;
    U32 m_width, m_height;
    GLFWwindow* m_handle;
  };

}
