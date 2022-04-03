#pragma once
#import "Vertex3.h"
namespace GLGraphics{
    class Color{
        const Vertex3 _color;
    public:
        explicit Color(const GLdouble r, const GLdouble g, const GLdouble b):_color(r,g,b){}
    };
}