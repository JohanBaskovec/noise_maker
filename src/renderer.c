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

    /*
    renderer.window_size.x = 1000;
    renderer.window_size.y = 1000;
*/
    window = SDL_CreateWindow(
            "SDL2 test"
            , 0
            , 0
            , 1920
            , 1080
            , SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP
    );
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GetWindowSize(window, &renderer.window_size.x, &renderer.window_size.y);
    logging_trace("%d %d", renderer.window_size.x, renderer.window_size.y);
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
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    logging_trace("Renderer initialized.\n");

    return RENDERER_INIT_ERROR_NONE;
}

void
draw_box(struct box *box)
{
    glBegin(GL_POLYGON);
    glVertex2d(box->left, box->bottom);
    glVertex2d(box->right, box->bottom);
    glVertex2d(box->right, box->top);
    glVertex2d(box->left, box->top);
    glEnd();
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



    glBegin(GL_LINES);
    glColor3f(.3, 0, 0);
    // sound drawing separator
    glVertex2d(0, PLAY_SPACE_HEIGHT);
    glVertex2d(renderer.window_size.x, PLAY_SPACE_HEIGHT);
    glEnd();

    draw_box(&program.sound_drawing_canvas[0].box);
    draw_box(&program.sound_drawing_canvas[1].box);

    glBegin(GL_POINTS);
    glColor3f(0.0, 1.0, 1.0);

    for (int i = 0; i < 2; ++i)
    {
        struct instrument instrument = audio.instruments[i];
        struct box canvas = program.sound_drawing_canvas[i].box;
        for (int x = 0; x < DRAW_SPACE_WIDTH; ++x)
        {
            int y = instrument.sound_shape[x];
            glVertex2d(x + canvas.left, y + canvas.bottom);
        }
    }

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