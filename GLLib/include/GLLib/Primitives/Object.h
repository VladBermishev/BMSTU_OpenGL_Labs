#pragma once
#include "GL/gl.h"
#include <cstring>
namespace GLGraphics{
    class Object{
        Mat4d _modelViewMatrix;
    public:
        Object(){
            glGetDoublev(GL_MODELVIEW_MATRIX,_modelViewMatrix.data());
        }
        void Draw(){
            glPushMatrix();
            glMatrixMode(GL_MODELVIEW);
            glLoadMatrixd(_modelViewMatrix.data());
            SetVertex();
            glPopMatrix();
        }
        virtual void SetVertex() = 0;
        void ModelViewIdentity(){
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glPushMatrix();
            glGetDoublev(GL_MODELVIEW_MATRIX,_modelViewMatrix.data());
            glPopMatrix();
            glPopMatrix();
        }
        void ModelViewTranslate(const GLdouble x, const GLdouble y, const GLdouble z){
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadMatrixd(_modelViewMatrix.data());
            glTranslated(x,y,z);
            glGetDoublev(GL_MODELVIEW_MATRIX,_modelViewMatrix.data());
            glPopMatrix();
        }
        void SetModelViewRotate(const GLdouble angle, const GLdouble x, const GLdouble y, const GLdouble z){
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glRotated(angle,x,y,z);
            glPushMatrix();
            glGetDoublev(GL_MODELVIEW_MATRIX,_modelViewMatrix.data());
            glPopMatrix();
            glPopMatrix();
        }
        void ModelViewRotate(const GLdouble angle, const GLdouble x, const GLdouble y, const GLdouble z){
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadMatrixd(_modelViewMatrix.data());
            glRotated(angle,x,y,z);
            glGetDoublev(GL_MODELVIEW_MATRIX,_modelViewMatrix.data());
            glPopMatrix();
        }
        void ModelViewScale(const GLdouble x, const GLdouble y, const GLdouble z){
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadMatrixd(_modelViewMatrix.data());
            glScaled(x,y,z);
            glGetDoublev(GL_MODELVIEW_MATRIX,_modelViewMatrix.data());
            glPopMatrix();
        }
    };
}