#pragma once

#include "GL/gl.h"
#include "Object.h"
#include "../Types/Vertex3.h"
#include <cstdint>
#include <cmath>

namespace GLGraphics{
    class ConycalCilinder: public GLGraphics::Object{
        const static std::uint32_t N = 60;
        Form _form;
        Vertex3 _lower_points[N], _upper_points[N];
        const GLdouble _lower_radius, _height, _upper_radius;
    public:
        ConycalCilinder(const GLdouble lower_radius, const GLdouble height, const GLdouble upper_radius) :
                _lower_radius(lower_radius), _height(height), _upper_radius(upper_radius) {
            _form = FILLED;
            InitializeVertex();
        }
        void ChangeFormOnOpposite(){
            _form = (Form)(1 - (std::int32_t)(_form));
        }
        void SetVertex(){
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
        void FilledForm(){
            glBegin(GL_POLYGON);
            glColor3f(1,0,0);
            for(std::uint32_t i = 0; i < N; i++){
                glVertex3d(_lower_points[i].x(),_lower_points[i].y(),_lower_points[i].z());
            }
            glEnd();
            glBegin(GL_POLYGON);
            glColor3f(0,1,0);
            for(std::uint32_t i = 0; i < N; i++){
                glVertex3d(_upper_points[i].x(),_upper_points[i].y(),_upper_points[i].z());
            }
            glEnd();
            glBegin(GL_QUADS);
            glColor3f(0,0,1);
            for(std::uint32_t i = 0; i < N-1; i++){
                glVertex3d(_upper_points[i].x(),_upper_points[i].y(),_upper_points[i].z());
                glVertex3d(_lower_points[i].x(),_lower_points[i].y(),_lower_points[i].z());
                glVertex3d(_lower_points[i+1].x(),_lower_points[i+1].y(),_lower_points[i+1].z());
                glVertex3d(_upper_points[i+1].x(),_upper_points[i+1].y(),_upper_points[i+1].z());
            }
            glVertex3d(_upper_points[N-1].x(),_upper_points[N-1].y(),_upper_points[N-1].z());
            glVertex3d(_lower_points[N-1].x(),_lower_points[N-1].y(),_lower_points[N-1].z());
            glVertex3d(_lower_points[0].x(),_lower_points[0].y(),_lower_points[0].z());
            glVertex3d(_upper_points[0].x(),_upper_points[0].y(),_upper_points[0].z());
            glEnd();
        }
        void SkeletonForm(){
            glBegin(GL_LINE_STRIP);
            glColor3f(1,0,0);
            for(std::uint32_t i = 0; i < N; i++){
                glVertex3d(_lower_points[i].x(),_lower_points[i].y(),_lower_points[i].z());
            }
            glEnd();
            glBegin(GL_LINE_STRIP);
            glColor3f(0,1,0);
            for(std::uint32_t i = 0; i < N; i++){
                glVertex3d(_upper_points[i].x(),_upper_points[i].y(),_upper_points[i].z());
            }
            glEnd();
            glBegin(GL_LINE_STRIP);
            glColor3f(0,0,1);
            for(std::uint32_t i = 0; i < N-1; i++){
                glVertex3d(_upper_points[i].x(),_upper_points[i].y(),_upper_points[i].z());
                glVertex3d(_lower_points[i].x(),_lower_points[i].y(),_lower_points[i].z());
                glVertex3d(_lower_points[i+1].x(),_lower_points[i+1].y(),_lower_points[i+1].z());
                glVertex3d(_upper_points[i+1].x(),_upper_points[i+1].y(),_upper_points[i+1].z());
            }
            glVertex3d(_upper_points[N-1].x(),_upper_points[N-1].y(),_upper_points[N-1].z());
            glVertex3d(_lower_points[N-1].x(),_lower_points[N-1].y(),_lower_points[N-1].z());
            glVertex3d(_lower_points[0].x(),_lower_points[0].y(),_lower_points[0].z());
            glVertex3d(_upper_points[0].x(),_upper_points[0].y(),_upper_points[0].z());
            glEnd();
        }
        void InitializeVertex() noexcept{
            for(std::uint32_t i = 0; i < N; i++){
                const GLdouble x = _lower_radius * cos(2*M_PI*((GLdouble)i/N));
                const GLdouble z = _lower_radius * sin(2*M_PI*((GLdouble)i/N));
                _lower_points[i].Set(x, 0, z);
            }
            for(std::uint32_t i = 0; i < N; i++){
                const GLdouble x = _upper_radius * cos(2*M_PI*((GLdouble)i/N));
                const GLdouble z = _upper_radius * sin(2*M_PI*((GLdouble)i/N));
                _upper_points[i].Set(x, _height, z);
            }
        }
    };
}
