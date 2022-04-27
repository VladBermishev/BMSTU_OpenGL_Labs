#pragma once
#include <type_traits>
#include <cstdint>
#include <GL/gl.h>
namespace GLGraphics{
    template<typename T=float>
    class Vector4{
        T _x, _y, _z, _w;
    public:
        Vector4(){
            static_assert(std::is_arithmetic_v<T>, "Arithmetic required.");
        }
        explicit Vector4(const T x, const T y, const T z, const T w) noexcept: _x(x),_y(y),_z(z),_w(w){
            static_assert(std::is_arithmetic_v<T>, "Arithmetic required.");
        }
        inline T  x()const noexcept{return _x;}
        inline T& x()noexcept{return _x;}
        inline T  y()const noexcept{return _y;}
        inline T& y()noexcept{return _y;}
        inline T  z()const noexcept{return _z;}
        inline T& z()noexcept{return _z;}
        inline T  w()const noexcept{return _w;}
        inline T& w()noexcept{return _w;}
    };
    typedef Vector4<std::int32_t> Vector4i;
    typedef Vector4<GLfloat> Vector4f;
    typedef Vector4<std::uint32_t> Vector4ui;
}