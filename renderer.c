#include "renderer.h"
#include "logging.h"
#include "program.h"
#include <SDL2/SDL.h>
#include <GL/gl.h>

SDL_Window *window;
SDL_GLContext gl_context;
struct renderer renderer;

/**
 * Initializes the renderer.
 * @return RENDERER_INIT_ERROR_NONE if no error happened.
 */
enum RENDERER_INIT_ERROR
renderer_init()
{
    logging_trace("Initializing renderer...");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        logging_trace(
                "Couldn't initialize SDL: %s"
                , SDL_GetError());
        return RENDERER_INIT_ERROR_FAILED_SDL_INIT_VIDEO;
    }
    else
    {
        logging_trace("SDL initialized.\n");
    }

    renderer.window_size.x = 1000;
    renderer.window_size.y = 1000;

    window = SDL_CreateWindow(
            "SDL2 test"
            , 0
            , 0
            , renderer.window_size.x
            , renderer.window_size.y
            , SDL_WINDOW_OPENGL
    );
    if (window == 0)
    {
        logging_trace(
                "Couldn't create window: %s"
                , SDL_GetError());
        return RENDERER_INIT_ERROR_FAILED_SDL_CREATEWINDOW;
    }
    else
    {
        logging_trace("Window created.\n");
    }

    gl_context = SDL_GL_CreateContext(window);
    if (gl_context == NULL)
    {
        logging_trace(
                "Couldn't initialize gl context: %s"
                , SDL_GetError());
        return RENDERER_INIT_ERROR_FAILED_SDL_GL_CREATECONTEXT;
    }
    else
    {
        logging_trace("OpenGL context initialized.\n");
    }


    SDL_GetWindowSize(window, &renderer.window_size.x, &renderer.window_size.y);

    glLoadIdentity();
    glOrtho(0.0, renderer.window_size.x, 0.0, renderer.window_size.y, 0, 1);
    glClearColor(0, 0, 0, 1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    logging_trace("Renderer initialized.\n");

    return RENDERER_INIT_ERROR_NONE;
}

enum RENDERER_RENDERING_ERROR
renderer_render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    int cursor_size = 10;

    glBegin(GL_LINES);
    glColor3f(1.0, 0, 0);
    glVertex2d(program.pointers[0].x, program.pointers[0].y);
    glVertex2d(program.pointers[1].x, program.pointers[1].y);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0);
    glVertex2d(program.pointers[0].x - cursor_size, program.pointers[0].y - cursor_size);
    glVertex2d(program.pointers[0].x + cursor_size, program.pointers[0].y - cursor_size);
    glVertex2d(program.pointers[0].x + cursor_size, program.pointers[0].y + cursor_size);
    glVertex2d(program.pointers[0].x - cursor_size, program.pointers[0].y + cursor_size);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0, 0, 1.0);
    glVertex2d(program.pointers[1].x - cursor_size, program.pointers[1].y - cursor_size);
    glVertex2d(program.pointers[1].x + cursor_size, program.pointers[1].y - cursor_size);
    glVertex2d(program.pointers[1].x + cursor_size, program.pointers[1].y + cursor_size);
    glVertex2d(program.pointers[1].x - cursor_size, program.pointers[1].y + cursor_size);
    glEnd();
    
    SDL_GL_SwapWindow(window);

    return RENDERER_RENDERING_ERROR_NONE;
}


void
renderer_destroy()
{
    logging_trace("Destroying window...");
    SDL_DestroyWindow(window);
    logging_trace("Window destroyed...");
    logging_trace("Deleting OpenGL context...");
    SDL_GL_DeleteContext(gl_context);
    logging_trace("OpenGL context quit.");
    logging_trace("Quitting SDL...");
    SDL_Quit();
    logging_trace("Quit SDL.");
}