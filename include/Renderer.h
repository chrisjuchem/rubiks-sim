#ifndef RENDERER_H
#define RENDERER_H

// The glad library helps setup OpenGL extensions.
// This renderer is designed specifically for OpenGL.
#include <glad/glad.h>

#include <vector>

#include "SceneNode.h"
#include "Camera.h"

class Renderer{
public:
	// The constructor	
	// Sets the width and height of the rendererer draws to
	Renderer(unsigned int w, unsigned int h);
	// Destructor
	~Renderer();
	// Update the scene
	void Update();
	// Render the scene
	void Render();
	// Sets the root of our renderer to some node to
	// draw an entire scene graph
	void setRoot(SceneNode* n);

	void toggleSceneGraph();
	// The one camera per Renderer
	Camera* camera;
protected:
	// Root scene node
	SceneNode* root;
    // Store the projection matrix for our camera.
    glm::mat4 projectionMatrix;

private:
	// Screen dimension constants
    int screenHeight;
    int screenWidth;

	bool drawSceneGraph;
};

#endif
