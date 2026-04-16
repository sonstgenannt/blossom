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
      const char* frag_path_;
      const char* vert_path_;

      void init_();

    public:
      static auto read_source(const char* path) -> std::string;

      static void print_log(GLuint shader);

      GLuint program_id;

      shader(const char* frag_path, const char* vert_path);

      shader() = default;
  };
}

#endif
