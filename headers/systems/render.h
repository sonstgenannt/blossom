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
        glm::mat4 view_projection_matrix(1.0F);

        auto active_camera_view = registry.view<component::tag::active_camera>();
        bool active_camera_exists = !active_camera_view.empty();

        if (active_camera_exists)
        {
          auto active_camera_entity = active_camera_view.front();

          if (auto* matrix_projection = registry.try_get<component::matrix::projection>(active_camera_entity))
          {
            view_projection_matrix = matrix_projection->data;

            if (auto* matrix_view = registry.try_get<component::matrix::view>(active_camera_entity))
            {
              view_projection_matrix *= matrix_view->data;
            }
            else
            {
              std::cout << "WARNING (blossom::system::render): Active camera doesn't have component::matrix::projection." << "\n";
            }
          }
          else
          {
            std::cout << "WARNING (blossom::system::render): Active camera doesn't have component::matrix::view." << "\n";
          }
        }
        else
        {
          std::cout << "WARNING (blossom::system::render): No active camera detected. Drawing without a camera." << "\n";
        }

        auto mesh_view = registry.view<component::matrix::transform, component::mesh>();
        for ( auto [entity, transform_matrix, mesh] : mesh_view.each() )
        {
          const auto MVP_MATRIX = view_projection_matrix * transform_matrix.data;
          draw_(mesh, MVP_MATRIX);
        }
      }

    private:
      static void draw_(const component::mesh& mesh, const glm::mat4& mvp_matrix)
      {
        glUseProgram(mesh.shader_program);
        glUniformMatrix4fv(
            mesh.uniform_location_mvp, 
            1, 
            GL_FALSE, 
            glm::value_ptr(mvp_matrix) );

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
