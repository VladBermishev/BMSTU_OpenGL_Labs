#pragma once
#include <type_traits>
namespace GLGraphics{
    template<typename T=float>
    class Vector2{
        const T _x, _y;
    public:
        explicit Vector2(const T x = 0, const T y = 0) noexcept: _x(x),_y(y){
            static_assert(std::is_arithmetic_v<T>, "Arithmetic required.");
        }
        inline T x()const noexcept{return _x;}
        inline T y()const noexcept{return _y;}
    };
}