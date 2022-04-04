#pragma once
#include <type_traits>
namespace GLGraphics{
    template<typename T=float>
    class Vector3{
         const T _x, _y, _z;
    public:
        Vector3(){
            static_assert(std::is_arithmetic_v<T>, "Arithmetic required.");
        }
        explicit Vector3(const T x, const T y, const T z) noexcept: _x(x),_y(y),_z(z){
            static_assert(std::is_arithmetic_v<T>, "Arithmetic required.");
        }
        inline T x()const noexcept{return _x;}
        inline T y()const noexcept{return _y;}
        inline T z()const noexcept{return _z;}
    };
}