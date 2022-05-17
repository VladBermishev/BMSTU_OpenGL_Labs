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
        template<typename F>
        explicit Vector3(const Vector3<F>& vec ){_x = vec.x();_y = vec.y();_z = vec.z();}

        Vector3<T>& operator=(const Vector3<T>& vec){_x = vec._x;_y = vec._y; _z = vec._z; return *this;}

        inline T  x()const noexcept{return _x;}
        inline T& x()noexcept{return _x;}
        inline T  y()const noexcept{return _y;}
        inline T& y()noexcept{return _y;}
        inline T  z()const noexcept{return _z;}
        inline T& z()noexcept{return _z;}

        Vector3<T> operator-(const Vector3<T>& vec) const{
            return Vector3<T>(_x-vec.x(),_y-vec.y(),_z-vec.z());
        }
        bool operator<(const Vector3<T>& vec) const{
            return std::tuple(_x,_y,_z) < std::tuple(vec.x(),vec.y(),vec.z());
        }

    };
    typedef Vector3<std::int32_t> Vector3i;
    typedef Vector3<GLfloat> Vector3f;
    typedef Vector3<std::uint32_t> Vector3ui;
}