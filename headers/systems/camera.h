#ifndef BLOSSOM_SYSTEM_CAMERA_H
#define BLOSSOM_SYSTEM_CAMERA_H

#include "../components/camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include "../components/matrices/transform.h"
#include "../components/view_projection_matrix.h"
#include <entt/entt.hpp>

namespace blossom::system
{
  class camera
  {
    public:
      static void update(entt::registry& registry)
      {
        auto view = registry.view<component::matrix::transform, component::view_projection_matrix, component::camera>();
        for (auto [entity, transform_matrix, vp_matrix, camera] : view.each())
        {
          auto view_projection_matrix = calculate_projection_matrix_(camera);
          view_projection_matrix *= glm::inverse(transform_matrix.data);
          vp_matrix.matrix = view_projection_matrix;
        }
      }

    private:
      static auto calculate_projection_matrix_(const component::camera& camera) -> glm::mat4
      {
        if (camera.type == component::camera::camera_type::PERSPECTIVE)
        {
          return calculate_perspective_projection_matrix_(camera);
        }
        return calculate_orthographic_projection_matrix_(camera);
      }

      static auto calculate_perspective_projection_matrix_(const component::camera& camera) -> glm::mat4
      {
        const float ASPECT = static_cast<float>(camera.width) / static_cast<float>(camera.height);
        return glm::perspective(glm::radians(camera.fov_y), ASPECT, camera.near, camera.far);
      }

      static auto calculate_orthographic_projection_matrix_(const component::camera& camera) -> glm::mat4
      {
        const float HALF_WIDTH = static_cast<float>(camera.width) / 2.0F;
        const float HALF_HEIGHT = static_cast<float>(camera.height) / 2.0F;

        return glm::ortho(
            -HALF_WIDTH, HALF_WIDTH, 
            -HALF_HEIGHT, HALF_HEIGHT,
            camera.near, camera.far
            );
      }
  };
}

#endif 
