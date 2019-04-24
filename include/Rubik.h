#ifndef RUBIK_H
#define RUBIK_H

#include "SceneNode.h"
#include "Cubie.h"
#include "Renderer.h"
#include <map>

enum class Face{
  UP,
  DOWN,
  LEFT,
  RIGHT,
  FRONT,
  BACK
};

class Rubik {
  public:
    Rubik(Renderer* r);
    ~Rubik();
    void RotateFace(Face f, bool ccw);
    void RotateCube(Face f);
    void Scramble();
    //progress animations
    void Update();
    void PostUpdate();
  private:
    SceneNode* buildCubie(float x, float y, float z, Face f, bool center);
    SceneNode* getCenter(Face f);
    void turnRandomFace();

    SceneNode* root;
    std::vector<SceneNode*> cubies;
    std::vector<SceneNode*> centers;
    std::map<Face, Transform> centerLocations;

    // Number of frames remaining in the current animation.
    int animFrames{0};
    //The face that is rotating and which direction
    Face rotating;
    bool ccw;
    bool rotCube; // if the whole cube is spinning
    
    int scramble{0};
};

#endif