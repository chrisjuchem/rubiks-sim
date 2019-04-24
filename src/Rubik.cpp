#include "Rubik.h"

int ANIM_FRAMES = 8;
float QUARTER_TURN = 1.57079632679f; //radians
int SCRAMBLE_TURNS = 25;

Rubik::Rubik(Renderer* r) {
    root = new SceneNode(nullptr);

    SceneNode* whiteCenter = buildCubie(0.0f, 1.0f, 0.0f, Face::UP, true);
    for (float x = -1.0f; x <= 1.0f; x+=1.0f) {
    for (float z = -1.0f; z <= 1.0f; z+=1.0f) {
        if (x == 0.0f && z == 0.0f) {continue;}
        whiteCenter->AddChild(buildCubie(x, 1.0f, z, Face::UP, false));
    }}
    root->AddChild(whiteCenter);
    
    SceneNode* orangeCenter = buildCubie(0.0f, 0.0f, -1.0f, Face::BACK, true);
    for (float x = -1.0f; x <= 1.0f; x+=1.0f) {
    for (float y = -1.0f; y <= 0.0f; y+=1.0f) {
        if (x == 0.0f && y == 0.0f) {continue;}
        orangeCenter->AddChild(buildCubie(x, y, -1.0f, Face::BACK, false));
    }}
    root->AddChild(orangeCenter);
    
    SceneNode* greenCenter = buildCubie(-1.0f, 0.0f, 0.0f, Face::LEFT, true);
    for (float y = -1.0f; y <= 0.0f; y+=1.0f) {
    for (float z =  0.0f; z <= 1.0f; z+=1.0f) {
        if (y == 0.0f && z == 0.0f) {continue;}
        greenCenter->AddChild(buildCubie(-1.0, y, z, Face::LEFT, false));
    }}
    root->AddChild(greenCenter);
    
    SceneNode* blueCenter = buildCubie(1.0f, 0.0f, 0.0f, Face::RIGHT, true);
    for (float y = -1.0f; y <= 0.0f; y+=1.0f) {
    for (float z =  0.0f; z <= 1.0f; z+=1.0f) {
        if (y == 0.0f && z == 0.0f) {continue;}
        blueCenter->AddChild(buildCubie(1.0f, y, z, Face::RIGHT, false));
    }}
    root->AddChild(blueCenter);
    
    SceneNode* yellowCenter = buildCubie(0.0f, -1.0f, 0.0f, Face::DOWN, true);
    yellowCenter->AddChild(buildCubie(0.0f, -1.0f, 1.0f, Face::DOWN, false));
    root->AddChild(yellowCenter);
    
    SceneNode* redCenter = buildCubie(0.0f, 0.0f, 1.0f, Face::FRONT, true);
    root->AddChild(redCenter);
    
    root->getLocalTransform().loadIdentity();
    root->getLocalTransform().translate(0.0f,2.1f,0.0f);  
    root->getLocalTransform().rotate(0.785398f, 0.0f, 1.0f, 0.0f);
    root->getLocalTransform().rotate(0.5f, 1.0f, 0.0f, 1.0f);
    root->getLocalTransform().scale(SceneNode::WORLDSCALE, SceneNode::WORLDSCALE, SceneNode::WORLDSCALE);

    r->setRoot(root);
    r->Update();

    centerLocations.insert({Face::UP, whiteCenter->getWorldTransform()});
    centerLocations.insert({Face::LEFT, greenCenter->getWorldTransform()});
    centerLocations.insert({Face::RIGHT, blueCenter->getWorldTransform()});
    centerLocations.insert({Face::DOWN, yellowCenter->getWorldTransform()});
    centerLocations.insert({Face::FRONT, redCenter->getWorldTransform()});
    centerLocations.insert({Face::BACK, orangeCenter->getWorldTransform()});
}

Rubik::~Rubik() {
    
}

SceneNode* Rubik::buildCubie(float x, float y, float z, Face f, bool center) {
    Cubie* c = new Cubie(glm::vec3(x, y, z));
    c->init();
    if (!center) {
        switch (f){
            case Face::UP:
            case Face::DOWN:
                y = 0.0f;
                break;
            case Face::LEFT:
            case Face::RIGHT:
                x = 0.0f;
                break;
            case Face::BACK:
            case Face::FRONT:
                z = 0.0f;
                break;
        }
    }
    SceneNode* sn = new SceneNode(c);
    sn->getLocalTransform().loadIdentity();
    sn->getLocalTransform().translate(2*x, 2*y, 2*z);
    cubies.push_back(sn);
    if (center) {
        centers.push_back(sn);
    }
    return sn;
}

SceneNode* Rubik::getCenter(Face f) {
    for (SceneNode* c : centers){
        if (c->dist(centerLocations.at(f)) < 0.01){
            return c;
        }
    }
    return nullptr;
}

// assume ccw (right hand rule)
void Rubik::RotateCube(Face f) {
    if (animFrames > 0) {return;}

    rotating = f;
    rotCube = true;
    animFrames = ANIM_FRAMES;
}

void Rubik::RotateFace(Face f, bool rotCcw) {
    if (animFrames > 0) {return;}

    SceneNode* center = getCenter(f);

    for (auto it = cubies.begin(); it != cubies.end(); it++) {
        if (center->dist((*it)->getWorldTransform()) < 2.85f * SceneNode::WORLDSCALE) { // 2sqrt2 + ~0.3
            bool matchCenter = false;
            for (SceneNode* const& c : centers) {
                if(c == *it) {
                    matchCenter = true;
                }
            }
            if (!matchCenter) {
                (*it)->setParent(center);
            }
        }

    }

   rotating = f;
   ccw = rotCcw;
   rotCube = false;
   animFrames = ANIM_FRAMES;
}

void Rubik::turnRandomFace() {
    Face f = (Face)(rand()%6);
    bool dir = f==rotating ? ccw : rand()%2;
	RotateFace(f, dir);
}

void Rubik::Scramble() {
    if (animFrames > 0) {return;}
    scramble = SCRAMBLE_TURNS;
    turnRandomFace();
}

void Rubik::Update() {
    if (animFrames > 0) {
        SceneNode* c = getCenter(rotating);

        if (rotCube) {
            glm::vec4 axis = (glm::inverse(root->getWorldTransform().getInternalMatrix()) *
                c->getWorldTransform().getInternalMatrix()) * glm::vec4(0.0f,0.0f,0.0f,1.0f); 
            root->getLocalTransform().rotate(QUARTER_TURN/ANIM_FRAMES,
                        axis.x, axis.y, axis.z);
        } else {
            glm::vec4 axis = c->getLocalTransform().getInternalMatrix() * glm::vec4(0.0f,0.0f,0.0f,1.0f);
            c->getLocalTransform().rotate((ccw?1:-1)*QUARTER_TURN/ANIM_FRAMES,
                    axis.x, axis.y, axis.z);
        }
        animFrames--;
    }
}

void Rubik::PostUpdate() {
    if (animFrames == 0 && scramble > 0) {
        turnRandomFace();
        scramble--;
    }
}
