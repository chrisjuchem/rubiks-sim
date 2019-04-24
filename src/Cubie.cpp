#include "Cubie.h"
#include  <iostream>

Cubie::Cubie(glm::vec3 vec) : spot(vec) {
  LoadTexture("cubie.ppm");
}

void Cubie::addBlankTex() {
  geometry.addTexture(0.75f, 0.75f);
  geometry.addTexture(1.00f, 0.75f);
  geometry.addTexture(0.75f, 1.00f);
  geometry.addTexture(1.00f, 1.00f);
}

void Cubie::init() {
  geometry.addVertex(-1.0f, 1.0f,-1.0f);//1
  geometry.addVertex( 1.0f, 1.0f,-1.0f);//2
  geometry.addVertex(-1.0f, 1.0f, 1.0f);//3
  geometry.addVertex( 1.0f, 1.0f, 1.0f);//4
  if (spot.y == 1.0f) {
    geometry.addTexture(0.25f, 0.00f);
    geometry.addTexture(0.50f, 0.00f);
    geometry.addTexture(0.25f, 0.25f);
    geometry.addTexture(0.50f, 0.25f);
  } else {
    addBlankTex();
  }

  geometry.addVertex(-1.0f, 1.0f, 1.0f);//5
  geometry.addVertex( 1.0f, 1.0f, 1.0f);//6
  geometry.addVertex(-1.0f,-1.0f, 1.0f);//7
  geometry.addVertex( 1.0f,-1.0f, 1.0f);//8
  if (spot.z ==  1.0f) {
    geometry.addTexture(0.25f, 0.25f);
    geometry.addTexture(0.50f, 0.25f);
    geometry.addTexture(0.25f, 0.50f);
    geometry.addTexture(0.50f, 0.50f);
  } else {
    addBlankTex();
  }

  geometry.addVertex(-1.0f,-1.0f, 1.0f);//9
  geometry.addVertex( 1.0f,-1.0f, 1.0f);//10
  geometry.addVertex(-1.0f,-1.0f,-1.0f);//11
  geometry.addVertex( 1.0f,-1.0f,-1.0f);//12
  if (spot.y == -1.0f) {
    geometry.addTexture(0.25f, 0.50f);
    geometry.addTexture(0.50f, 0.50f);
    geometry.addTexture(0.25f, 0.75f);
    geometry.addTexture(0.50f, 0.75f);
  } else {
    addBlankTex();
  }

  geometry.addVertex(-1.0f,-1.0f,-1.0f);//13
  geometry.addVertex( 1.0f,-1.0f,-1.0f);//14
  geometry.addVertex(-1.0f, 1.0f,-1.0f);//15
  geometry.addVertex( 1.0f, 1.0f,-1.0f);//16
  if (spot.z == -1.0f) {
    geometry.addTexture(0.25f, 0.75f);
    geometry.addTexture(0.50f, 0.75f);
    geometry.addTexture(0.25f, 1.0f);
    geometry.addTexture(0.50f, 1.0f);
  } else {
    addBlankTex();
  }

  geometry.addVertex( 1.0f, 1.0f,-1.0f);//17
  geometry.addVertex( 1.0f,-1.0f,-1.0f);//18
  geometry.addVertex( 1.0f, 1.0f, 1.0f);//19
  geometry.addVertex( 1.0f,-1.0f, 1.0f);//20
  if (spot.x ==  1.0f) {
    geometry.addTexture(0.50f, 0.00f);
    geometry.addTexture(0.75f, 0.00f);
    geometry.addTexture(0.50f, 0.25f);
    geometry.addTexture(0.75f, 0.25f);
  } else {
    addBlankTex();
  }

  geometry.addVertex(-1.0f,-1.0f,-1.0f);//21
  geometry.addVertex(-1.0f, 1.0f,-1.0f);//22
  geometry.addVertex(-1.0f,-1.0f, 1.0f);//23
  geometry.addVertex(-1.0f, 1.0f, 1.0f);//24
  if (spot.x ==  -1.0f) {
    geometry.addTexture(0.00f, 0.00f);
    geometry.addTexture(0.25f, 0.00f);
    geometry.addTexture(0.00f, 0.25f);
    geometry.addTexture(0.25f, 0.25f);
  } else {
    addBlankTex();
  }


  for (int n = 0; n < 24; n+=4) {
    geometry.makeTriangle(n,n+1,n+2);
    geometry.makeTriangle(n+1,n+3,n+2);
  }

  geometry.gen();

  // Create a buffer and set the stride of information
  myBuffer.CreateBufferNormalMapLayout(
      14, geometry.getSize(), geometry.getIndicesSize(), geometry.getData(),
      geometry.getIndicesData());
}