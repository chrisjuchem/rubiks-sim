#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "SDLGraphicsProgram.h"
#include "Object.h"

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h){
    // Initialization flag
    bool success = true;
    // String to hold any errors that occur.
    std::stringstream errorStream;
    // The window we'll be rendering to
    gWindow = NULL;
    // Render flag

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO)< 0){
        errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
        success = false;
    }
    else{
    //Use OpenGL 3.3 core
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    // We want to request a double buffer for smooth updating.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    //Create window
    gWindow = SDL_CreateWindow( "Lab",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                w,
                                h,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

        // Check if Window did not create.
        if( gWindow == NULL ){
            errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        }

        //Create an OpenGL Graphics Context
        gContext = SDL_GL_CreateContext( gWindow );
        if( gContext == NULL){
            errorStream << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        }

        // Initialize GLAD Library
        if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
            errorStream << "Failed to iniitalize GLAD and OpenGL\n";
            success = false;
        }
    }

    // If initialization did not work, then print out a list of errors in the constructor.
    if(!success){
        errorStream << "Failed to initialize!\n";
        std::string errors=errorStream.str();
        SDL_Log("%s\n",errors.c_str());
    }else{
        SDL_Log("No SDL, GLAD, or OpenGL errors detected during initialization\n\n");
    }

	// SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN); // Uncomment to enable extra debug support!
	getOpenGLVersionInfo();


    // Setup our Renderer
    renderer = new Renderer(w,h);
}


// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram(){
    if(renderer!=nullptr){
        delete renderer;
    }
    
    if(cube!=nullptr) {
        delete cube;
    }

    //Destroy window
    SDL_DestroyWindow( gWindow );
    // Point gWindow to NULL to ensure it points to nothing.
    gWindow = NULL;
    //Quit SDL subsystems
    SDL_Quit();
}


//Loops forever!
void SDLGraphicsProgram::loop(){
    renderer->Render(); //solid bg while loading
    SDL_GL_SwapWindow(getSDLWindow());

    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();

    // Set a default speed for the camera
    float cameraSpeed = 0.05f;

    cube = new Rubik(renderer);

    // While application is running
    while(!quit){
        //Handle events on queue
        while(SDL_PollEvent( &e ) != 0){
            // User posts an event to quit
            // An example is hitting the "x" in the corner of the window.
            if(e.type == SDL_QUIT){
                quit = true;
            }
            switch(e.type){
                // Handle keyboard presses
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                        case SDLK_q:
                            quit = true;
                            break;
                        case SDLK_w:
                            static bool wireframe;
                            wireframe = !wireframe;
                            glPolygonMode( GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL );
                            break;
                        case SDLK_s:
                            renderer->toggleSceneGraph();
                            break;
                        case SDLK_a:
                            cube->Scramble();
                            break;
                        case SDLK_z:
                            delete cube;
                            renderer->setRoot(nullptr);
                            renderer->Render();
                            SDL_GL_SwapWindow(getSDLWindow());
                            cube = new Rubik(renderer);
                            break;

                        case SDLK_e:
                            cube->RotateFace(Face::BACK, e.key.keysym.mod & KMOD_SHIFT);
                            break;
                        case SDLK_r:
                            cube->RotateFace(Face::UP, e.key.keysym.mod & KMOD_SHIFT);
                            break;
                        case SDLK_t:
                            cube->RotateFace(Face::RIGHT, e.key.keysym.mod & KMOD_SHIFT);
                            break;
                        case SDLK_d:
                            cube->RotateFace(Face::LEFT, e.key.keysym.mod & KMOD_SHIFT);
                            break;
                        case SDLK_f:
                            cube->RotateFace(Face::FRONT, e.key.keysym.mod & KMOD_SHIFT);
                            break;
                        case SDLK_c:
                            cube->RotateFace(Face::DOWN, e.key.keysym.mod & KMOD_SHIFT);
                            break;
                        
                        case SDLK_u:
                            cube->RotateCube(Face::LEFT);
                            break;
                        case SDLK_i:
                            cube->RotateCube(Face::BACK);
                            break;
                        case SDLK_h:
                            cube->RotateCube(Face::DOWN);
                            break;
                        case SDLK_k:
                            cube->RotateCube(Face::UP);
                            break;
                        case SDLK_n:
                            cube->RotateCube(Face::FRONT);
                            break;
                        case SDLK_m:
                            cube->RotateCube(Face::RIGHT);
                            break;
                    }
                break;
            }
        } // End SDL_PollEvent loop.

        // Update the cube
        cube->Update();
        // Update our scene through our renderer
        renderer->Update();
        //Update the cube after cubie positions have been updated
        cube->PostUpdate();

        // Render our scene using our selected renderer
        renderer->Render();
        //Update screen of our specified window
        SDL_GL_SwapWindow(getSDLWindow());
        // Delay to slow things down just a bit!
        SDL_Delay(25); 
    }

    //Disable text input
    SDL_StopTextInput();
}


// Get Pointer to Window
SDL_Window* SDLGraphicsProgram::getSDLWindow(){
  return gWindow;
}

// Helper Function to get OpenGL Version Information
void SDLGraphicsProgram::getOpenGLVersionInfo(){
    SDL_Log("(Note: If you have two GPU's, make sure the correct one is selected)");
    SDL_Log("Vendor: %s",(const char*)glGetString(GL_VENDOR));
    SDL_Log("Renderer: %s",(const char*)glGetString(GL_RENDERER));
    SDL_Log("Version: %s",(const char*)glGetString(GL_VERSION));
    SDL_Log("Shading language: %s",(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}
