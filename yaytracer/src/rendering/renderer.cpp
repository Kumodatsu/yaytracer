#include "rendering/renderer.hpp"
#include "logging.hpp"
#include <array>
#include <vector>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

static const char* vertex_shader_source =
  "#version 450\n"
  "layout(location = 0) in  vec2 in_position;\n"
  "layout(location = 0) out vec2 out_position;\n"
  "void main() {\n"
  "  gl_Position  = vec4(in_position, 0.0, 1.0);\n"
  "  out_position = in_position;\n"
  "}\n";

static const char* fragment_shader_source =
  "#version 450\n"
  "uniform sampler2D u_texture;\n"
  "layout(location = 0) in  vec2 in_position;\n"
  "layout(location = 0) out vec4 out_color;\n"
  "void main() {\n"
  "  vec2 flipped_texture_coords =\n"
  "    0.5 * (in_position + vec2(1.0, 1.0));\n"
  "  vec2 texture_coords = vec2(\n"
  "    flipped_texture_coords.x,\n"
  "    1.0 - flipped_texture_coords.y\n"
  "  );\n"
  "  out_color = texture(u_texture, texture_coords);\n"
  "}\n";

static constexpr std::array<float, 2 * 6> vertex_data {{
  -1.0f, -1.0f, 1.0f, -1.0f,  1.0f, 1.0f,
  -1.0f, -1.0f, 1.0f,  1.0f, -1.0f, 1.0f,
}};

static void APIENTRY gl_debug_callback(
  GLenum        source,
  GLenum        type,
  GLuint        id,
  GLenum        severity,
  GLsizei       length,
  const GLchar* message,
  const void*   param
) {
  if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
    return;
  }
  YAY_LOG(Warning) << "OpenGL: " << message;
}

namespace yay {

  Renderer::Renderer(Window& window)
    : m_window(window)
    , m_vbo_id(0)
    , m_vao_id(0)
    , m_shader_program_id(0)
    , m_texture(nullptr)
  {
    const int glad_succeeded =
      gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    if (glad_succeeded == 0) {
      glfwTerminate();
      YAY_LOG(Fatal) << "Failed to initialize Glad.";
    }
    YAY_LOG(Info) << "Initialized Glad.";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui_ImplGlfw_InitForOpenGL(m_window.handle(), true);
    ImGui_ImplOpenGL3_Init();
    YAY_LOG(Info) << "Initialized Dear ImGui.";

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(gl_debug_callback, this);

    glCreateBuffers(1, &m_vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
    glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float),
      vertex_data.data(), GL_STATIC_DRAW);
    glCreateVertexArrays(1, &m_vao_id);
    glBindVertexArray(m_vao_id);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    const GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_id, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader_id);
    const GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_id, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader_id);
    m_shader_program_id = glCreateProgram();
    glAttachShader(m_shader_program_id, vertex_shader_id);
    glAttachShader(m_shader_program_id, fragment_shader_id);
    glLinkProgram(m_shader_program_id);
    glDetachShader(m_shader_program_id, fragment_shader_id);
    glDetachShader(m_shader_program_id, vertex_shader_id);
    glDeleteShader(fragment_shader_id);
    glDeleteShader(vertex_shader_id);
    GLint status;
    glGetProgramiv(m_shader_program_id, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
      GLint length;
      glGetProgramiv(m_shader_program_id, GL_INFO_LOG_LENGTH, &length);
      std::vector<GLchar> log;
      log.resize(length);
      glGetProgramInfoLog(m_shader_program_id, length, nullptr, log.data());
      YAY_LOG(Fatal) << "Shader program failed to compile: " << log.data();
    }
    m_texture.reset(new Texture);
  }

  Renderer::~Renderer() {
    m_texture.reset();
    glDeleteProgram(m_shader_program_id);
    glDeleteVertexArrays(1, &m_vao_id);
    glDeleteBuffers(1, &m_vbo_id);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }

  void Renderer::begin_frame() {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(m_shader_program_id);
    glBindVertexArray(m_vao_id);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
  }

  void Renderer::render(const PixelBuffer& pixels) {
    m_texture->bind();
    m_texture->buffer(pixels);
    const GLint loc = glGetUniformLocation(m_shader_program_id, "u_texture");
    glUniform1i(loc, 0);
    glDrawArrays(GL_TRIANGLES, 0, vertex_data.size());
  }

  void Renderer::end_frame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwSwapBuffers(m_window.handle());
  }
  
}
