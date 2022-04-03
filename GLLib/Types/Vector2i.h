#pragma once
#include <cstdint>
namespace GLGraphics{
    class Vector2i{
        std::int32_t _x, _y;
    public:
        Vector2i() = default;
        explicit Vector2i(const std::int32_t x, const std::int32_t y) noexcept: _x(x),_y(y){}
        inline std::int32_t x()const noexcept{return _x;}
        inline std::int32_t y()const noexcept{return _y;}
    };
}