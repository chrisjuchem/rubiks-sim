#include "Renderer.h"

// Sets the height and width of our renderer
Renderer::Renderer(unsigned int w, unsigned int h){
    screenWidth = w;
    screenHeight = h;

    camera = new Camera();
    root = nullptr;
}

// Sets the height and width of our renderer
Renderer::~Renderer(){
    delete camera;
}

void Renderer::Update(){
    // Here we apply the projection matrix which creates perspective.
    // The first argument is 'field of view'
    // Then perspective
    // Then the near and far clipping plane.
    
    projectionMatrix = glm::perspective(45.0f,((float)screenWidth)/((float)screenHeight),0.1f,20.0f);
    

    // Perform the update
    if(root!=nullptr){
        root->Update(projectionMatrix, camera);
    }
}

// Initialize clear color
// Setup our OpenGL State machine
// Then render the scene
void Renderer::Render(){

    // What we are doing, is telling opengl to create a depth(or Z-buffer) 
    // for us that is stored every frame.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D); 
    // This is the background of the screen.
    glViewport(0, 0, screenWidth, screenHeight);
    glClearColor( 0.2f, 0.2f, 0.2f, 1.f );
    // Clear color buffer and Depth Buffer
    // Remember that the 'depth buffer' is our
    // z-buffer that figures out how far away items are every frame
    // and we have to do this every frame!
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    // Now we render our objects from our scenegraph
    if(root!=nullptr){
        root->Draw();
    }
}

// Determines what the root is of the renderer, so the
// scene can be drawn.
void Renderer::setRoot(SceneNode* n){
    root = n;
    drawSceneGraph = false;
}

void Renderer::toggleSceneGraph() {
    drawSceneGraph = !drawSceneGraph;
    root->SetGraphColor(0,drawSceneGraph);
}

