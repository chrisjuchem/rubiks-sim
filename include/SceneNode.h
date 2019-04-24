#ifndef SCENENODE_H
#define SCENENODE_H

#include <vector>

#include "Object.h"
#include "Transform.h"
#include "Camera.h"
#include "Shader.h"

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

class SceneNode{
public:
    // A SceneNode is created by taking
    // a pointer to an object.
    SceneNode(Object* ob);
    // Our destructor takes care of destroying
    // all of the children within the node.
    // Now we do not have to manage deleting
    // each individual object.
    ~SceneNode();
    // Adds a child node to our current node.
    void AddChild(SceneNode* n);
    // Set or reset colors for the scenegraph view
    void SetGraphColor(int depth, bool showGraph);
    // Draws the current SceneNode
    void Draw();
    // Updates the current SceneNode
    void Update(glm::mat4 projectionMatrix, Camera* camera);
    // Returns the local transformation transform
    // Remember that local is local to an object, where it's center is the origin.
    Transform& getLocalTransform();
    // Returns a SceneNode's world transform
    Transform& getWorldTransform();
    // For now we have one shader per object.
    Shader myShader;
    // Change this nodes position in the graph
    void setParent(SceneNode* newParent);
    // get the distance from another world transform
    float dist(Transform& other);
    constexpr static float WORLDSCALE = 0.4f;
protected:
    // Parent
    SceneNode* parent;
private:
    // Children holds all a pointer to all of the descendents
    // of a particular SceneNode. A pointer is used because
    // we do not want to hold or make actual copies.
    std::vector<SceneNode*> children;
    // The object stored in the scene graph
    Object* object;
    // Each SceneNode nodes locals transform.
    Transform localTransform;
    // We additionally can store the world transform
    Transform worldTransform;
    // Graph color passed to the shader, black ignored
    glm::vec3 graphColor{0.0f, 0.0f, 0.0f};
};

#endif
