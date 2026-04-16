#ifndef BLOSSOM_SHADER_H
#define BLOSSOM_SHADER_H

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
    private:
      static void print_log_(GLuint shader);

    public:
      static auto read_source(const std::string& path) -> std::string;
      static auto compile(const shader_info& info) -> GLuint;
  };
}

#endif
