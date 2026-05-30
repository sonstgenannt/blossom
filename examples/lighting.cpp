#include "../headers/window.h"
#include "../headers/shader.h"
#include "../headers/systems/render.h"
#include "../headers/systems/transform.h"
#include "../headers/systems/camera.h"
#include "../headers/factories/camera.h"
#include "../headers/factories/cube24.h"
#include "../headers/factories/sphere.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const char* window_title = "Blossom Lighting Example";

auto main() -> int
{
    blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, window_title);

    glClearColor(0.1, 0.1, 0.1, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    entt::registry registry;

    constexpr glm::vec3 CAMERA_POSITION = { 0.0F, 3.0F, 3.0F };
    constexpr glm::vec3 CAMERA_ROTATION = {-45.0F, 0.0F,  0.0F};

    constexpr float CAMERA_FOV_Y = 90.0F;

    blossom::factory::camera{registry}
      .with_width (WINDOW_WIDTH)
      .with_height(WINDOW_HEIGHT)
      .with_fov_y (CAMERA_FOV_Y)
      .with_position(CAMERA_POSITION)
      .with_rotation(CAMERA_ROTATION)
      .with_type(blossom::component::camera::camera_type::PERSPECTIVE)
      .make_active();

    const blossom::shader_info LIT_INFO
    {
      .vertex_shader_path   = "shaders/lit.vert",
      .fragment_shader_path = "shaders/lit.frag"
    };
    const GLuint LIT_PROGRAM = blossom::shader::compile(LIT_INFO);

    const blossom::shader_info LIGHT_INFO
    {
      .vertex_shader_path   = "shaders/default.vert",
      .fragment_shader_path = "shaders/color.frag"
    };
    const GLuint LIGHT_PROGRAM = blossom::shader::compile(LIGHT_INFO);

    glUseProgram(LIT_PROGRAM);
    const GLint ul_objectColor = glGetUniformLocation(LIT_PROGRAM, "objectColor");
    glUniform3f(ul_objectColor, 1.0f, 0.5f, 0.31f);
    const GLint ul_lightColor = glGetUniformLocation(LIT_PROGRAM, "lightColor");
    glUniform3f(ul_lightColor, 1.0f, 1.0f, 1.0f);

    glm::vec3 lightPos(1.2f, 1.0, 2.0f);

    const GLint ul_lightPos = glGetUniformLocation(LIT_PROGRAM, "lightPos");
    glUniform3f(ul_lightPos, lightPos.x, lightPos.y, lightPos.z);

    blossom::factory::cube24(
        registry,
        LIGHT_PROGRAM,
        lightPos,
        {0.2f, 0.2f, 0.2f}
    );

    blossom::factory::cube24(
        registry,
        LIT_PROGRAM,
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    );

    blossom::system::transform::update(registry);
    blossom::system::camera::update(registry);

    auto active_camera_entity = (registry.view<blossom::component::tag::active_camera>()).front();
    auto& camera_transform = registry.get<blossom::component::transform>(active_camera_entity);

    while (glfwWindowShouldClose(window.window_ptr) == 0) 
    {

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      blossom::system::render::update(registry);
      glfwSwapBuffers(window.window_ptr); 
      glfwPollEvents();
    }
    window.destroy();
}
