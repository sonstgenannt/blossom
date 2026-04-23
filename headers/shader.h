#ifndef BLOSSOM_SHADER_H
#define BLOSSOM_SHADER_H

#include <stdexcept>
#include <string>
#include <glad/gl.h>
#include <gtest/gtest_prod.h>

namespace blossom 
{
  struct shader_info
  {
    std::string vertex_shader_path;
    std::string fragment_shader_path;
  };

  class shader 
  {
    enum class shader_type : uint8_t
    {
      VERTEX,
      FRAGMENT
    };

    private:
      static void print_log_(GLuint shader);

      template<shader_type ST>
      static auto compile_shader_(const std::string& shader_source) -> GLuint
      {
        const char* ss_ptr = shader_source.c_str();

        GLuint shader = 0;
        GLint shader_compilation_status = 0;

        if constexpr (ST == shader_type::VERTEX)
        {
          shader = glCreateShader(GL_VERTEX_SHADER);
          glShaderSource(shader, 1, &ss_ptr, nullptr);
          glCompileShader(shader);

          GLint shader_compilation_status = 0;
          glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compilation_status);

          if ( shader_compilation_status == GL_FALSE ) 
          {
            print_log_(shader);
            throw std::runtime_error("ERROR: Vertex shader compilation failed!");
          }
          return shader;
        }

        if constexpr (ST == shader_type::FRAGMENT)
        {
          shader = glCreateShader(GL_FRAGMENT_SHADER);
          glShaderSource(shader, 1, &ss_ptr, nullptr);
          glCompileShader(shader);

          GLint shader_compilation_status = 0;
          glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compilation_status);

          if ( shader_compilation_status == GL_FALSE ) 
          {
            print_log_(shader);
            throw std::runtime_error("ERROR: Vertex shader compilation failed!");
          }
          return shader;
        }
      }

    public:
      static auto read_source(const std::string& path) -> std::string;
      static auto compile(const shader_info& info) -> GLuint;
  };
}

#endif
