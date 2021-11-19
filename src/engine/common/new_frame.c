#include <tt.h>

extern SDL_Window *tt_window;

void tt_new_frame()
{
    SDL_GL_SwapWindow(tt_window);
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}