#pragma once
#include <type_traits>
namespace GLGraphics{
    template<typename T=float>
    class Vector2{
        T _x, _y;
    public:
        Vector2() noexcept: _x(0), _y(0){
            static_assert(std::is_arithmetic_v<T>, "Arithmetic required.");
        }
        explicit Vector2(const T x, const T y) noexcept: _x(x),_y(y){
            static_assert(std::is_arithmetic_v<T>, "Arithmetic required.");
        }
        inline T  x()const noexcept{return _x;}
        inline T& x()noexcept{return _x;}
        inline T  y()const noexcept{return _y;}
        inline T& y()noexcept{return _y;}
    };
    typedef Vector2<std::int32_t> Vector2i;
    typedef Vector2<GLfloat> Vector2f;
    typedef Vector2<std::uint32_t> Vector2ui;
}