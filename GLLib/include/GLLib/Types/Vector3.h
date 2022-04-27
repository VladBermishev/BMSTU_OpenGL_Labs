#pragma once
#include <type_traits>
#include <cstdint>
#include <GL/gl.h>
namespace GLGraphics{
    template<typename T=float>
    class Vector3{
         T _x, _y, _z;
    public:
        Vector3(){
            static_assert(std::is_arithmetic_v<T>, "Arithmetic required.");
        }
        explicit Vector3(const T x, const T y, const T z) noexcept: _x(x),_y(y),_z(z){
            static_assert(std::is_arithmetic_v<T>, "Arithmetic required.");
        }
        inline T  x()const noexcept{return _x;}
        inline T& x()noexcept{return _x;}
        inline T  y()const noexcept{return _y;}
        inline T& y()noexcept{return _y;}
        inline T  z()const noexcept{return _z;}
        inline T& z()noexcept{return _z;}
    };
    typedef Vector3<std::int32_t> Vector3i;
    typedef Vector3<GLfloat> Vector3f;
    typedef Vector3<std::uint32_t> Vector3ui;
}