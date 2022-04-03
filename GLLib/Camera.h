#pragma once
#include "GLLib.h"
namespace GLGraphics{
    class Camera{
        GLdouble _projectionMatrix[16];
    public:
        Camera() = default;
        inline void Init() noexcept{
            glLoadIdentity();
            glGetDoublev(GL_PROJECTION_MATRIX,&_projectionMatrix[0]);
        }
        inline void SetMatrix()noexcept{
            glMatrixMode(GL_PROJECTION);
            glLoadMatrixd(_projectionMatrix);
        }
        void ProjectionIdentity(){
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glPushMatrix();
            glGetDoublev(GL_MODELVIEW_MATRIX,&_projectionMatrix[0]);
            glPopMatrix();
            glPopMatrix();
        }
        void ProjectionRotate(const GLdouble angle, const GLdouble x, const GLdouble y, const GLdouble z){
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadMatrixd(_projectionMatrix);
            glRotated(angle, x, y, z);
            glGetDoublev(GL_PROJECTION_MATRIX,&_projectionMatrix[0]);
            glPopMatrix();
        }
        void ProjectionScale(const GLdouble x, const GLdouble y, const GLdouble z){
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadMatrixd(_projectionMatrix);
            glScaled(x, y, z);
            glGetDoublev(GL_PROJECTION_MATRIX,&_projectionMatrix[0]);
            glPopMatrix();
        }
        void ProjectionTranslate(const GLdouble x, const GLdouble y, const GLdouble z){
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadMatrixd(_projectionMatrix);
            glTranslated(x, y, z);
            glGetDoublev(GL_PROJECTION_MATRIX,&_projectionMatrix[0]);
            glPopMatrix();
        }
    };
}