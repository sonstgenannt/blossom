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

      static void print_log_(GLuint shader);

      void init_();

    public:
      static auto read_source(const char* path) -> std::string;

      GLuint program_id;

      shader(const char* frag_path, const char* vert_path);

      shader() = default;
  };
}

#endif
