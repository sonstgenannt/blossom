#ifndef BLOSSOM_COMPONENT_MESH_H
#define BLOSSOM_COMPONENT_MESH_H

#include <glad/gl.h>

namespace blossom::component
{
  struct mesh
  {
    GLuint shader_program = 0;

    GLsizei vertex_count = 0;
    GLsizei index_count = 0;

    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;

    GLenum polygon_mode = GL_FILL;
    GLenum primitive_type = GL_TRIANGLES;

    GLint uniform_location_model = 0;
  };
}

#endif 
