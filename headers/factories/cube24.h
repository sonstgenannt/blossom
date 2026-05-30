#ifndef BLOSSOM_FACTORY_CUBE24_H
#define BLOSSOM_FACTORY_CUBE24_H

#include <entt/entt.hpp>
#include "../factories/mesh.h"

namespace blossom::factory
{
  inline auto cube24(entt::registry& registry, GLuint shader_program, const glm::vec3& position, const glm::vec3& scale) -> entt::entity
  {
    //     H──────G
    //    /│     /│
    //   E──────F │
    //   │ │    │ │
    //   │ D────┼─C
    //   │/     │/
    //   A──────B
    const std::vector<glm::vec3> CUBE_VERTICES = 
    {
      // Front Face (Z = 0.5f) - Vertices: A, B, F, E
      glm::vec3{-0.5f, -0.5f,  0.5f},
      glm::vec3{ 0.5f, -0.5f,  0.5f},
      glm::vec3{ 0.5f,  0.5f,  0.5f},
      glm::vec3{-0.5f,  0.5f,  0.5f},

      // Back Face (Z = -0.5f) - Vertices: C, D, H, G
      glm::vec3{ 0.5f, -0.5f, -0.5f},
      glm::vec3{-0.5f, -0.5f, -0.5f},
      glm::vec3{-0.5f,  0.5f, -0.5f},
      glm::vec3{ 0.5f,  0.5f, -0.5f},

      // Right Face (X = 0.5f) - Vertices: B, C, G, F
      glm::vec3{ 0.5f, -0.5f,  0.5f},
      glm::vec3{ 0.5f, -0.5f, -0.5f},
      glm::vec3{ 0.5f,  0.5f, -0.5f},
      glm::vec3{ 0.5f,  0.5f,  0.5f},

      // Left Face (X = -0.5f) - Vertices: D, A, E, H
      glm::vec3{-0.5f, -0.5f, -0.5f},
      glm::vec3{-0.5f, -0.5f,  0.5f},
      glm::vec3{-0.5f,  0.5f,  0.5f},
      glm::vec3{-0.5f,  0.5f, -0.5f},

      // Top Face (Y = 0.5f) - Vertices: E, F, G, H
      glm::vec3{-0.5f,  0.5f,  0.5f},
      glm::vec3{ 0.5f,  0.5f,  0.5f},
      glm::vec3{ 0.5f,  0.5f, -0.5f},
      glm::vec3{-0.5f,  0.5f, -0.5f},

      // Bottom Face (Y = -0.5f) - Vertices: D, C, B, A
      glm::vec3{-0.5f, -0.5f, -0.5f},
      glm::vec3{ 0.5f, -0.5f, -0.5f},
      glm::vec3{ 0.5f, -0.5f,  0.5f},
      glm::vec3{-0.5f, -0.5f,  0.5f}
    }; 

    std::vector<glm::vec3> CUBE_NORMALS =
    {
      // Front Face normals
      glm::vec3{ 0.0f,  0.0f,  1.0f}, glm::vec3{ 0.0f,  0.0f,  1.0f},
      glm::vec3{ 0.0f,  0.0f,  1.0f}, glm::vec3{ 0.0f,  0.0f,  1.0f},

      // Back Face normals
      glm::vec3{ 0.0f,  0.0f, -1.0f}, glm::vec3{ 0.0f,  0.0f, -1.0f},
      glm::vec3{ 0.0f,  0.0f, -1.0f}, glm::vec3{ 0.0f,  0.0f, -1.0f},

      // Right Face normals
      glm::vec3{ 1.0f,  0.0f,  0.0f}, glm::vec3{ 1.0f,  0.0f,  0.0f},
      glm::vec3{ 1.0f,  0.0f,  0.0f}, glm::vec3{ 1.0f,  0.0f,  0.0f},

      // Left Face normals
      glm::vec3{-1.0f,  0.0f,  0.0f}, glm::vec3{-1.0f,  0.0f,  0.0f},
      glm::vec3{-1.0f,  0.0f,  0.0f}, glm::vec3{-1.0f,  0.0f,  0.0f},

      // Top Face normals
      glm::vec3{ 0.0f,  1.0f,  0.0f}, glm::vec3{ 0.0f,  1.0f,  0.0f},
      glm::vec3{ 0.0f,  1.0f,  0.0f}, glm::vec3{ 0.0f,  1.0f,  0.0f},

      // Bottom Face normals
      glm::vec3{ 0.0f, -1.0f,  0.0f}, glm::vec3{ 0.0f, -1.0f,  0.0f},
      glm::vec3{ 0.0f, -1.0f,  0.0f}, glm::vec3{ 0.0f, -1.0f,  0.0f}
    };

    std::vector<glm::vec2> CUBE_UV =
    {
      // Front Face (Z = 0.5f)
      glm::vec2{0.0f, 0.0f}, // Bottom-Left (Vertex A)
      glm::vec2{1.0f, 0.0f}, // Bottom-Right (Vertex B)
      glm::vec2{1.0f, 1.0f}, // Top-Right (Vertex F)
      glm::vec2{0.0f, 1.0f}, // Top-Left (Vertex E)

      // Back Face (Z = -0.5f)
      glm::vec2{0.0f, 0.0f}, // Bottom-Left (Vertex C)
      glm::vec2{1.0f, 0.0f}, // Bottom-Right (Vertex D)
      glm::vec2{1.0f, 1.0f}, // Top-Right (Vertex H)
      glm::vec2{0.0f, 1.0f}, // Top-Left (Vertex G)

      // Right Face (X = 0.5f)
      glm::vec2{0.0f, 0.0f}, // Bottom-Left (Vertex B)
      glm::vec2{1.0f, 0.0f}, // Bottom-Right (Vertex C)
      glm::vec2{1.0f, 1.0f}, // Top-Right (Vertex G)
      glm::vec2{0.0f, 1.0f}, // Top-Left (Vertex F)

      // Left Face (X = -0.5f)
      glm::vec2{0.0f, 0.0f}, // Bottom-Left (Vertex D)
      glm::vec2{1.0f, 0.0f}, // Bottom-Right (Vertex A)
      glm::vec2{1.0f, 1.0f}, // Top-Right (Vertex E)
      glm::vec2{0.0f, 1.0f}, // Top-Left (Vertex H)

      // Top Face (Y = 0.5f)
      glm::vec2{0.0f, 0.0f}, // Bottom-Left (Vertex E)
      glm::vec2{1.0f, 0.0f}, // Bottom-Right (Vertex F)
      glm::vec2{1.0f, 1.0f}, // Top-Right (Vertex G)
      glm::vec2{0.0f, 1.0f}, // Top-Left (Vertex H)

      // Bottom Face (Y = -0.5f)
      glm::vec2{0.0f, 0.0f}, // Bottom-Left (Vertex D)
      glm::vec2{1.0f, 0.0f}, // Bottom-Right (Vertex C)
      glm::vec2{1.0f, 1.0f}, // Top-Right (Vertex B)
      glm::vec2{0.0f, 1.0f}  // Top-Left (Vertex A)
    };
    
    const std::vector<GLuint> CUBE_INDICES = 
    {
      0,  1,  2,    2,  3,  0,  // Front
      4,  5,  6,    6,  7,  4,  // Back
      8,  9,  10,   10, 11, 8,  // Right
      12, 13, 14,   14, 15, 12, // Left
      16, 17, 18,   18, 19, 16, // Top
      20, 21, 22,   22, 23, 20  // Bottom
    };

    return mesh(registry)
      .with_position(position)
      .with_scale(scale)
      .with_vertices(CUBE_VERTICES)
      .with_normals(CUBE_NORMALS)
      .with_uv(CUBE_UV)
      .with_indices(CUBE_INDICES)
      .with_shader_program(shader_program)
      .build();
  }
}

#endif
