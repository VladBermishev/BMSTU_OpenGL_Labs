#pragma once
#include <iostream>
#include <vector>
#include "GLFW/glfw3.h"
#include "GL/gl.h"
#include <GL/glut.h>
#include "math.h"
#include "GLLib.h"



Circle c(0,0,0.1);

void display() {
    glClearColor(0.2,0.3,0.3,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    c.Update();
    c.Draw();
    glPopMatrix();
    glFlush();
}
namespace GLGraphics{


    class KeyCallbackEngine{

    };



}
