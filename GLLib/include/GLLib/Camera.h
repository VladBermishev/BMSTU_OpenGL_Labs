#pragma once
#include "GLLib.h"
namespace GLGraphics{
    class Camera{
        Mat<4,GLdouble> _projectionMatrix;
    public:
        Camera() = default;
        inline void Init() noexcept{}
        inline void SetMatrix()noexcept{
            glMatrixMode(GL_PROJECTION);
            glLoadMatrixd(_projectionMatrix.data());
        }
        void ProjectionIdentity(){
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glPushMatrix();
            glGetDoublev(GL_MODELVIEW_MATRIX,_projectionMatrix.data());
            glPopMatrix();
            glPopMatrix();
        }
        void ProjectionRotate(const GLdouble angle, const GLdouble x, const GLdouble y, const GLdouble z){
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadMatrixd(_projectionMatrix.data());
            glRotated(angle, x, y, z);
            glGetDoublev(GL_PROJECTION_MATRIX,_projectionMatrix.data());
            glPopMatrix();
        }
        void ProjectionScale(const GLdouble x, const GLdouble y, const GLdouble z){
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadMatrixd(_projectionMatrix.data());
            glScaled(x, y, z);
            glGetDoublev(GL_PROJECTION_MATRIX,_projectionMatrix.data());
            glPopMatrix();
        }
        void ProjectionTranslate(const GLdouble x, const GLdouble y, const GLdouble z){
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadMatrixd(_projectionMatrix.data());
            glTranslated(x, y, z);
            glGetDoublev(GL_PROJECTION_MATRIX,_projectionMatrix.data());
            glPopMatrix();
        }
    };
}