#ifndef BLOSSOM_SYSTEM_RENDER_H
#define BLOSSOM_SYSTEM_RENDER_H

#include <iostream>

#include "../components/tags/active_camera.h"
#include "../components/matrices/transform.h"
#include "../components/matrices/view.h"
#include "../components/matrices/projection.h"
#include "../components/mesh.h"

#include <entt/entt.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace blossom::system
{
  class render
  {
    public:
      static void update(entt::registry& registry)
      {
        std::array<glm::mat4, 3> mvp_matrices;

        auto active_camera_view = registry.view<component::tag::active_camera>();
        bool active_camera_exists = !active_camera_view.empty();

        if (active_camera_exists)
        {
          auto active_camera_entity = active_camera_view.front();

          if (auto* matrix_projection = registry.try_get<component::matrix::projection>(active_camera_entity))
          {
            mvp_matrices[0] = matrix_projection->data;
          }
          else
          {
            std::cout << "WARNING (blossom::system::render): Active camera doesn't have component::matrix::view." << "\n";
          }

          if (auto* matrix_view = registry.try_get<component::matrix::view>(active_camera_entity))
          {
            mvp_matrices[1] = matrix_view->data;
          }
          else
          {
            std::cout << "WARNING (blossom::system::render): Active camera doesn't have component::matrix::projection." << "\n";
          }
        }
        else
        {
          std::cout << "WARNING (blossom::system::render): No active camera detected. Drawing without a camera." << "\n";
        }

        auto mesh_view = registry.view<component::matrix::transform, component::mesh>();
        for ( auto [entity, matrix_transform, mesh] : mesh_view.each() )
        {
          mvp_matrices[2] = matrix_transform.data;
          draw_(mesh, mvp_matrices);
        }
      }

    private:
      static void draw_(const component::mesh& mesh, const std::array<glm::mat4, 3>& mvp_matrix)
      {
        glUseProgram(mesh.shader_program);
        glUniformMatrix4fv(
            mesh.uniform_location_projection, 
            1, 
            GL_FALSE, 
            glm::value_ptr(mvp_matrix[0])
        ); 
        glUniformMatrix4fv(
          mesh.uniform_location_view,
          1,
          GL_FALSE,
          glm::value_ptr(mvp_matrix[1])
        );
        glUniformMatrix4fv(
          mesh.uniform_location_model,
          1,
          GL_FALSE,
          glm::value_ptr(mvp_matrix[2])
        );

        glBindVertexArray(mesh.vao);
        glPolygonMode(GL_FRONT_AND_BACK, mesh.polygon_mode);

        if ( !(mesh.index_count == 0) ) 
        { 
          glDrawElements(
              mesh.primitive_type, 
              mesh.index_count,
              GL_UNSIGNED_INT, 
              nullptr
              ); 
        }
        else 
        { 
          glDrawArrays(
              mesh.primitive_type, 
              0, 
              mesh.vertex_count
              ); 
        }
      }
  };
}

#endif 
