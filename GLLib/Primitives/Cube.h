#pragma once
#include "Object.h"
#include "GL/gl.h"
namespace GLGraphics{
    enum Form{
        SKELETON = 0,
        FILLED
    };
    class Cube: public Object{
        Form _form;
    public:
        Cube(){_form = FILLED;}
        void SetForm(const Form form)noexcept{_form = form;}
        void ChangeFormOnOpposite()noexcept{ _form = (Form)(1 - (std::int32_t)(_form));}
        void SetVertex() override {
            switch (_form) {
                case Form::SKELETON:
                    SkeletonForm();
                    break;
                case Form::FILLED:
                    FilledForm();
                    break;
            }
        }

    private:
        void SkeletonForm()noexcept{
            const auto size = 0.4f;
            glBegin(GL_QUADS);
            // левая грань
            glColor3f(0.5f, 0.5f, 0.5f);
            glVertex3f( -size / 2, -size / 2, -size / 2);
            glVertex3f( -size / 2,  size / 2, -size / 2);
            glVertex3f( -size / 2,  size / 2,  size / 2);
            glVertex3f( -size / 2, -size / 2,  size / 2);
            // верхняя грань
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f( -size / 2, size / 2, -size / 2);
            glVertex3f( -size / 2, size / 2,  size / 2);
            glVertex3f(  size / 2, size / 2,  size / 2);
            glVertex3f(  size / 2, size / 2, -size / 2);
            // задняя грань
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f( -size / 2, -size / 2, -size / 2);
            glVertex3f(  size / 2, -size / 2, -size / 2);
            glVertex3f(  size / 2,  size / 2, -size / 2);
            glVertex3f( -size / 2,  size / 2, -size / 2);
            glEnd();
            glBegin(GL_LINES);
            // правая грань
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(  size / 2, -size / 2, -size / 2);
            glVertex3f(  size / 2, -size / 2,  size / 2);
            glVertex3f(  size / 2, -size / 2,  size / 2);
            glVertex3f(  size / 2,  size / 2,  size / 2);
            glVertex3f(  size / 2,  size / 2,  size / 2);
            glVertex3f(  size / 2,  size / 2, -size / 2);
            glEnd();
        }
        void FilledForm()noexcept{
            const auto size = 0.4f;
            glBegin(GL_QUADS);
            // левая грань
            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex3f( -size / 2, -size / 2, -size / 2);
            glVertex3f( -size / 2,  size / 2, -size / 2);
            glVertex3f( -size / 2,  size / 2,  size / 2);
            glVertex3f( -size / 2, -size / 2,  size / 2);
            // правая грань
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(  size / 2, -size / 2, -size / 2);
            glVertex3f(  size / 2, -size / 2,  size / 2);
            glVertex3f(  size / 2,  size / 2,  size / 2);
            glVertex3f(  size / 2,  size / 2, -size / 2);
            // нижняя грань
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f( -size / 2, -size / 2, -size / 2);
            glVertex3f( -size / 2, -size / 2,  size / 2);
            glVertex3f(  size / 2, -size / 2,  size / 2);
            glVertex3f(  size / 2, -size / 2, -size / 2);
            // верхняя грань
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f( -size / 2, size / 2, -size / 2);
            glVertex3f( -size / 2, size / 2,  size / 2);
            glVertex3f(  size / 2, size / 2,  size / 2);
            glVertex3f(  size / 2, size / 2, -size / 2);
            // задняя грань
            glColor3f(1.0f, 0.0f, 1.0f);
            glVertex3f( -size / 2, -size / 2, -size / 2);
            glVertex3f(  size / 2, -size / 2, -size / 2);
            glVertex3f(  size / 2,  size / 2, -size / 2);
            glVertex3f( -size / 2,  size / 2, -size / 2);
            // передняя грань
            glColor3f(0.0f, 1.0f, 1.0f);
            glVertex3f( -size / 2, -size / 2,  size / 2);
            glVertex3f( -size / 2,  size / 2,  size / 2);
            glVertex3f(  size / 2,  size / 2,  size / 2);
            glVertex3f(  size / 2, -size / 2,  size / 2);
            glEnd();
        }
    };
}