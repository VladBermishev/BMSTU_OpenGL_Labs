#pragma once
#include "Object.h"
#include "math.h"
#include "../Types/Vertex3.h"
namespace GLGraphics{
    class Circle: public Object{
        const static std::uint32_t N = 60;
        GLdouble _r;
        GLfloat _col_r, _col_g, _col_b;
    public:
        explicit Circle(const float r = 0.25) noexcept{_r = r; }
        void SetVertex(){
            glBegin(GL_POLYGON);
            glColor3f(_col_r,_col_g,_col_b);
            for(std::uint32_t i = 0; i < N; i++){
                const float phi = 2.0 * M_PI * ((GLdouble)i/N);
                const float x = _r * cosf(phi);
                const float z = _r * sinf(phi);
                glVertex3f(x, 0, z);
            }
            glEnd();
        }
        inline void SetColor(const float r, const float g, const float b) noexcept{_col_r = r; _col_g = g; _col_b = b;}
    };
}