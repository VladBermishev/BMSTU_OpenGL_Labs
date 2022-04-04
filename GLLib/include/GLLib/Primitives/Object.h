#pragma once
#include "GL/gl.h"
#include "string.h"
namespace GLGraphics{
    class Object{
        GLdouble _modelViewMatrix[16];

    public:
        Object(){
            glGetDoublev(GL_MODELVIEW_MATRIX,&_modelViewMatrix[0]);
        }
        void Draw(){
            glPushMatrix();
            glMatrixMode(GL_MODELVIEW);
            glLoadMatrixd(_modelViewMatrix);
            SetVertex();
            glPopMatrix();
        }
        virtual void SetVertex() = 0;
        void ModelViewIdentity(){
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glPushMatrix();
            glGetDoublev(GL_MODELVIEW_MATRIX,&_modelViewMatrix[0]);
            glPopMatrix();
            glPopMatrix();
        }
        void ModelViewTranslate(const GLdouble x, const GLdouble y, const GLdouble z){
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadMatrixd(_modelViewMatrix);
            glTranslated(x,y,z);
            glGetDoublev(GL_MODELVIEW_MATRIX,&_modelViewMatrix[0]);
            glPopMatrix();
        }
        void SetModelViewRotate(const GLdouble angle, const GLdouble x, const GLdouble y, const GLdouble z){
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glRotated(angle,x,y,z);
            glPushMatrix();
            glGetDoublev(GL_MODELVIEW_MATRIX,&_modelViewMatrix[0]);
            glPopMatrix();
            glPopMatrix();
        }
        void ModelViewRotate(const GLdouble angle, const GLdouble x, const GLdouble y, const GLdouble z){
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadMatrixd(_modelViewMatrix);
            glRotated(angle,x,y,z);
            glGetDoublev(GL_MODELVIEW_MATRIX,&_modelViewMatrix[0]);
            glPopMatrix();
        }
        void ModelViewScale(const GLdouble x, const GLdouble y, const GLdouble z){
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadMatrixd(_modelViewMatrix);
            glScaled(x,y,z);
            glGetDoublev(GL_MODELVIEW_MATRIX,&_modelViewMatrix[0]);
            glPopMatrix();
        }
    };
}