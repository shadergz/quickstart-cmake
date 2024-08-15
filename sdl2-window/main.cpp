#include <iostream>
#include <cstdint>
#include <GLES2/gl2.h>

#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES 1
#include <SDL2/SDL_opengl.h>
#include <glm/glm.hpp>

using i32 = std::int32_t;
using u32 = std::uint32_t;
i32 main() {
    constexpr i32 windowFlags{SDL_WINDOW_OPENGL};
    const auto window{SDL_CreateWindow("SDL2 Window", 0, 0, 1024, 768, windowFlags)};

    if (const auto glContext{SDL_GL_CreateContext(window)}; !window || !glContext)
        return EXIT_FAILURE;

    bool isRunning{true};

    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    constexpr glm::f32 vertices[]{
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f   // top left
   };
    constexpr GLuint indices[]{
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    while (isRunning) {
        SDL_Event eventPoll;
        while (SDL_PollEvent(&eventPoll)) {
            if (eventPoll.key.keysym.sym == SDLK_ESCAPE)
                isRunning = {};
            if (eventPoll.type == SDL_QUIT)
                isRunning = {};
        }
        if (!isRunning)
            continue;
        glViewport(0, 0, 1024, 768);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, std::size(indices), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        SDL_GL_SwapWindow(window);
    }

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
