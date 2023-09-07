#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>

int main(int argc, char *argv[])
{
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        spdlog::error("SDL2 failed to initialize: {}", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // Prepare OpenGL
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    auto window = SDL_CreateWindow("Learn OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   640, 480, SDL_WINDOW_OPENGL);
    if (!window)
    {
        spdlog::error("SDL2 window failed to create: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    auto context = SDL_GL_CreateContext(window);
    if (!context)
    {
        spdlog::error("SDL2 failed to get gl context: {}", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_GL_MakeCurrent(window, context);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        spdlog::error("GLAD failed to initialize");
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    glViewport(0, 0, 640, 480);

    // Set Vsync
    if (SDL_GL_SetSwapInterval(-1) == -1)
        SDL_GL_SetSwapInterval(1);

    bool isRunning = true;
    while (isRunning)
    {
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                case SDL_KEYDOWN:
                    if (ev.key.keysym.sym == SDLK_ESCAPE)
                        isRunning = false;
                    break;
            }
        }

        glClearColor(.8f, .8f, 0, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }


    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}