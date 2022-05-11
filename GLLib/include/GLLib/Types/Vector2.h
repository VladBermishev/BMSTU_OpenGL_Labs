#pragma once
#include <type_traits>
#include <cstdint>
#include <cmath>
#include <GL/gl.h>
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

        template<typename F>
        explicit Vector2(const Vector2<F>& vec ){_x = vec.x();_y = vec.y();}

        inline T  x()const noexcept{return _x;}
        inline T& x()noexcept{return _x;}
        inline T  y()const noexcept{return _y;}
        inline T& y()noexcept{return _y;}

        Vector2<T> operator*(const T value) const{return Vector2<T>(_x*value,_y*value);}

        template<typename F>
        Vector2<T> operator+(const Vector2<F>& vec){return Vector2<T>(_x+vec.x(),_y+vec.y());}
    };
    template<typename T>
    inline T Euclid_distance(const Vector2<T>& a, const Vector2<T>& b){
        return sqrt((a.x()-b.x())*(a.x()-b.x())+(a.y()-b.y())*(a.y()-b.y()));
    }
    typedef Vector2<std::int32_t> Vector2i;
    typedef Vector2<GLfloat> Vector2f;
    typedef Vector2<GLdouble> Vector2d;
    typedef Vector2<std::uint32_t> Vector2ui;
    template<typename T=float>
    Vector2<T> norm(const Vector2<T>& vec){
        auto len = Euclid_distance(Vector2<T>(0,0),vec);
        return Vector2<T>(-vec.y()/len,vec.x()/len);
    }
    template<typename T=float>
    Vector2<T> perpendic(const Vector2<T>& vec){
        return Vector2<T>(-vec.y(),vec.x());
    }
}