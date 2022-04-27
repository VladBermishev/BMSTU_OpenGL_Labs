#pragma once
#include "GL/gl.h"
namespace GLGraphis{
    class Vertex2{
         GLdouble _x, _y;
    public:
        Vertex2() = default;
        explicit Vertex2(const GLdouble x, const GLdouble y) noexcept: _x(x),_y(y){}
        inline GLdouble  x()const noexcept{return _x;}
        inline GLdouble& x()noexcept{return _x;}
        inline GLdouble  y()const noexcept{return _y;}
        inline GLdouble& y()noexcept{return _y;}
    };
}