#pragma once
#include "GL/gl.h"
namespace GLGraphics{
    class Vertex3{
        GLdouble _x, _y, _z;
    public:
        Vertex3() = default;
        explicit Vertex3(const GLdouble x, const GLdouble y, const GLdouble z) noexcept: _x(x),_y(y),_z(z){}
        inline void Set(const GLdouble x, const GLdouble y, const GLdouble z) noexcept{_x=x;_y=y;_z=z;}
        inline GLdouble x()const noexcept{return _x;}
        inline GLdouble& x() noexcept{return _x;}
        inline GLdouble y()const noexcept{return _y;}
        inline GLdouble& y()noexcept{return _y;}
        inline GLdouble z()const noexcept{return _z;}
        inline GLdouble& z() noexcept{return _z;}
    };
}