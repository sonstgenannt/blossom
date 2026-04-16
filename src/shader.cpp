#include "../headers/shader.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <vector>

using blossom::shader;

auto shader::read_source(const char* path) -> std::string
{
  std::string file_content;
  std::ifstream file(path, std::ios::in);
  std::string line;

  while ( std::getline(file, line) ) 
  {
    file_content.append(line + '\n');
  }

  if ( !file.is_open() ) 
  {
    throw std::runtime_error("The file" + std::string(path) + "doesn't exist.");
  }
  file.close();
  return file_content;
}

void shader::print_log_(GLuint shader)
{
  if ( glfwGetCurrentContext() == nullptr )
  {
    throw std::runtime_error("ERROR: Cannot print shader log. There is no current OpenGL context.");
  }

  if ( glIsShader(shader) == GL_FALSE )
  {
    throw std::runtime_error("ERROR: Unable to print the shader log of an invalid shader object.");
  }

  GLsizei max_length = 0;

  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

  if ( max_length > 0 ) 
  {
    std::vector<GLchar> info_log(max_length);
    GLsizei length = 0;

    glGetShaderInfoLog(shader, max_length, &length, info_log.data());

    const std::string INFO_LOG_STR(info_log.begin(), info_log.begin() + length);
    std::cout << "Shader Log: " << INFO_LOG_STR << "\n";
  }
}

auto shader::compile(const std::string& frag_path, const std::string& vertex_path) -> GLuint
{
  if ( glfwGetCurrentContext() == nullptr )
  {
    throw std::runtime_error("ERROR: Cannot initialise shader (there is no current OpenGL context.) Ensure that a GL context is active before shader initialisation.");
  }

  std::string vertex_shader_source_string = read_source(vertex_path.c_str());
  std::string fragment_shader_source_string = read_source(frag_path.c_str());

  const char* vertex_shader_source = vertex_shader_source_string.c_str();
  const char* fragment_shader_source = fragment_shader_source_string.c_str();

  const GLuint VERTEX_SHADER = glCreateShader(GL_VERTEX_SHADER);
  const GLuint FRAGMENT_SHADER = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(VERTEX_SHADER, 1, &vertex_shader_source, nullptr);
  glCompileShader(VERTEX_SHADER);
  
  GLint vertex_shader_compilation_status;
  glGetShaderiv(VERTEX_SHADER, GL_COMPILE_STATUS, &vertex_shader_compilation_status);

  if ( vertex_shader_compilation_status == GL_FALSE ) 
  {
    std::cout << "WARNING: Vertex shader compilation failed." << "\n";
    print_log_(VERTEX_SHADER);
  }

  glShaderSource(FRAGMENT_SHADER, 1, &fragment_shader_source, nullptr);
  glCompileShader(FRAGMENT_SHADER);

  GLint fragment_shader_compilation_status;
  glGetShaderiv(FRAGMENT_SHADER, GL_COMPILE_STATUS, &fragment_shader_compilation_status);

  if ( fragment_shader_compilation_status == GL_FALSE ) 
  {
    std::cout << "WARNING: Fragment shader compilation failed." << "\n";
    print_log_(FRAGMENT_SHADER);
  }

  GLuint shader_program = glCreateProgram();

  glAttachShader(shader_program, VERTEX_SHADER);
  glAttachShader(shader_program, FRAGMENT_SHADER);
  glLinkProgram(shader_program);

  glDeleteShader(VERTEX_SHADER);
  glDeleteShader(FRAGMENT_SHADER);

  return shader_program;
}
