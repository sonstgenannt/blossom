#ifndef BLOSSOM_SHADER_H
#define BLOSSOM_SHADER_H

#include <string>
#include <glad/gl.h>
#include <gtest/gtest_prod.h>

namespace blossom 
{
  class shader 
  {
    private:
      static void print_log_(GLuint shader);

    public:
      static auto read_source(const char* path) -> std::string;
      static auto compile(const std::string& frag_path, const std::string& vert_path) -> GLuint;
  };
}

#endif
