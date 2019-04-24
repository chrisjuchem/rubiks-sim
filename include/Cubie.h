#ifndef CUBIE_H
#define CUBIE_H

#include "Object.h"
#include "glm/vec3.hpp"

class Cubie : public Object {
public:
    Cubie(glm::vec3);
    void init() override;
private:
    glm::vec3 spot;
    void addBlankTex();
};

#endif 
