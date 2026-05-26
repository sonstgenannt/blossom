#ifndef BLOSSOM_FACTORY_MESH_H
#define BLOSSOM_FACTORY_MESH_H

#include <entt/entt.hpp>
#include "../components/transform.h"
#include "../components/matrices/transform.h"
#include "../components/mesh.h"

namespace blossom::factory
{
  class mesh
  {
    public:
      explicit mesh(entt::registry& registry)
        : registry_(registry)
      {
        entity_    = registry_.create();
        registry_.emplace<component::mesh>(entity_);
        registry_.emplace<component::transform>(entity_);
        registry_.emplace<component::matrix::transform>(entity_);
      }

      auto with_position(const glm::vec3& position) -> mesh&
      {
        registry_.get<component::transform>(entity_).position = position;
        return *this;
      }

      auto with_scale(const glm::vec3& scale) -> mesh&
      {
        registry_.get<component::transform>(entity_).scale = scale;
        return *this;
      }

      auto with_vertices(std::vector<glm::vec3> vertices) -> mesh&
      {
        points_ = std::move(vertices);
        return *this;
      }

      auto with_uv(std::vector<glm::vec2> uv) -> mesh&
      {
        uv_ = std::move(uv);
        return *this;
      }

      auto with_normals(std::vector<glm::vec3> normals) -> mesh&
      {
        normals_ = std::move(normals);
        return *this;
      }

      auto with_indices(std::vector<GLuint> indices) -> mesh&
      {
        indices_ = std::move(indices);
        return *this;
      }

      auto with_shader_program(const GLuint shader_program) -> mesh&
      {
        registry_.get<component::mesh>(entity_).shader_program = shader_program;
        return *this;
      }

      auto with_primitive_type(const GLenum primitive_type) -> mesh&
      {
        registry_.get<component::mesh>(entity_).primitive_type = primitive_type;
        return *this;
      }

      auto with_polygon_mode(const GLenum polygon_mode) -> mesh&
      {
        registry_.get<component::mesh>(entity_).polygon_mode = polygon_mode;
        return *this;
      }

      auto clean_up() -> entt::entity
      {
        vertices_.clear(); indices_.clear();
        vertices_.shrink_to_fit(); indices_.shrink_to_fit();

        return entity_;
      }

      auto build() -> entt::entity
      {
        auto& mesh = registry_.get<component::mesh>(entity_);

        if (uv_.empty())
        {
          uv_.assign(points_.size(), glm::vec2());
        }

        if (normals_.empty())
        {
          normals_ = points_;
        }

        for (size_t i = 0; i < points_.size(); i++)
        {
          vertices_.push_back(points_[i].x);
          vertices_.push_back(points_[i].y);
          vertices_.push_back(points_[i].z);
          vertices_.push_back(normals_.at(i).x);
          vertices_.push_back(normals_.at(i).y);
          vertices_.push_back(normals_.at(i).z);
          vertices_.push_back(uv_.at(i).x);
          vertices_.push_back(uv_.at(i).y);
        }

        mesh.vertex_count = static_cast<GLsizei>(vertices_.size());
        mesh.index_count = static_cast<GLsizei>(indices_.size());

        init_uniform_locations_();
        init_buffers_();

        return entity_;
      }

    private:
      entt::registry&        registry_;
      entt::entity           entity_;

      std::vector<glm::vec3> points_;
      std::vector<glm::vec2> uv_;
      std::vector<glm::vec3> normals_;

      std::vector<float> vertices_;
      std::vector<GLuint> indices_;

      void init_uniform_locations_()
      {
        auto& mesh = registry_.get<component::mesh>(entity_);
        mesh.uniform_location_model = glGetUniformLocation(mesh.shader_program, "model");
      }

      void init_buffers_()
      {
        auto& mesh = registry_.get<component::mesh>(entity_);

        glCreateVertexArrays(1, &mesh.vao);

        glCreateBuffers(1, &mesh.vbo);
        glNamedBufferStorage(
            mesh.vbo, 
            static_cast<GLsizeiptr>( vertices_.size() * sizeof(float) ), 
            vertices_.data(), 
            0
        );

        if (indices_.size() > 0)
        {
          glCreateBuffers(1, &mesh.ebo);
          glNamedBufferStorage(
              mesh.ebo, 
              static_cast<GLsizeiptr>( indices_.size() * sizeof(GLuint) ), 
              indices_.data(), 
              0
          );
        }

        // Vertex size
        const GLsizei stride = sizeof(glm::vec3) + sizeof(glm::vec3) + sizeof(glm::vec2);

        glVertexArrayElementBuffer(mesh.vao, mesh.ebo);
        glVertexArrayVertexBuffer(mesh.vao, 0, mesh.vbo, 0, stride);

        glEnableVertexArrayAttrib(mesh.vao, 0);
        glVertexArrayAttribFormat(
          mesh.vao, 
          0, 
          3, 
          GL_FLOAT, 
          GL_FALSE, 
          0
        );
        glVertexArrayAttribBinding(mesh.vao, 0, 0);

        glEnableVertexArrayAttrib(mesh.vao, 1);
        glVertexArrayAttribFormat(
          mesh.vao,
          1,
          3,
          GL_FLOAT,
          GL_FALSE,
          static_cast<GLint>(sizeof(glm::vec3))
        );
        glVertexArrayAttribBinding(mesh.vao, 1, 0);

        glEnableVertexArrayAttrib(mesh.vao, 2);
        glVertexArrayAttribFormat(
          mesh.vao,
          2,
          2,
          GL_FLOAT,
          GL_FALSE,
          static_cast<GLint>(sizeof(glm::vec3))
        );
        glVertexArrayAttribBinding(mesh.vao, 2, 0);
      }
  };
}

#endif
