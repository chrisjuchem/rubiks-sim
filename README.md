# Rubik's Cube Simulator

Scramble and solve Rubik's cubes!

### Controls:
* General
  * `q` - quit
  * `w` - toggle wireframe mode
  * `s` - toggle "scenegraph" view
  * `a` - scramble cube
  * `z` - reset cube
* Turning faces
  * `d` - turn near left face (L)
  * `f` - turn near right face (F)
  * `r` - turn top face (U)
  * `e` - turn back left face (B)
  * `t` - turn back right face (R)
  * `c` - turn bottom face (D)
  * `SHIFT + *` - turn \* face in reverse (')
* Rotating cube
  * `i` - turn L face up
  * `n` - turn L face down
  * `u` - turn F face up
  * `m` - turn F face down
  * `h` - turn cube left
  * `k` - turn cube right

## Build Instructions

Requires SDL2 to be installed.

Run `python build.py` or `make` (which runs `build.py` for you)

## Overview

This was my final project for my Computer Graphics course at Northeastern University.
I used OpenGL and SDL to develop an application that allows the user to scramble and 
solve Rubik's cubes shown on screen.

The key to this project was the Dynamic Scene Graph that I developed. It allowed me to
rotate all the cubies on a single face with a single rotation, then rewrite the scene 
graph so that some of the same cubies could then rotate around a different axis with 
the rest of that face. See the video below for visuals and more details.

The majority of the code for the project was written over the course of the semester
for various labs and assignments, then compiled together and tweaked for this project.

## Youtube video

[https://youtu.be/0NQQdmv8GSM](https://youtu.be/0NQQdmv8GSM)
