#ifndef SDLGRAPHICSPROGRAM_H
#define SDLGRAPHICSPROGRAM_H

// ==================== Libraries ==================
// The #define statement should be passed in
// when compiling using the -D argument.
#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // Mac
    #include <SDL.h>
#endif



#include "Renderer.h"
#include "Rubik.h"

class SDLGraphicsProgram{
public:

    // Constructor
    SDLGraphicsProgram(int w, int h);
    // Desctructor
    ~SDLGraphicsProgram();
    // loop that runs forever
    void loop();
    // Get Pointer to Window
    SDL_Window* getSDLWindow();
    // Helper Function to Query OpenGL information.
    void getOpenGLVersionInfo();

private:
    // The window we'll be rendering to
    SDL_Window* gWindow ;
    // OpenGL context
    SDL_GLContext gContext;
	// The Renderer responsible for drawing objects
	// in OpenGL (Or whatever Renderer you choose!)
	Renderer* renderer;
    Rubik* cube;
};

#endif
