#pragma once
#include <cstdint>
#include <cstring>

namespace GLGraphics {
    template<std::size_t N, typename T>
    class Mat {
        T _data[N * N];
    public:
        Mat() {
            std::memset(&_data[0], 0, sizeof(_data[0]) * N * N);
            for (std::uint32_t i = 0; i < N; i++) { _data[(N + 1) * i] = 1; }
        }

        Mat(const Mat<N,T> &m) {
            std::memcpy(&_data[0], &m._data[0], sizeof(m._data[0]) * N * N);
        }
        //Undefined behaviour with incorrect indexes
        T* operator[](const std::uint32_t i)noexcept{return &_data[N*i];}
        //Undefined behaviour with incorrect indexes
        const T* operator[](const std::uint32_t i)const noexcept{return &_data[N*i];}
        T* data() noexcept { return &_data[0]; }
        const T* data() const noexcept { return &_data[0]; }

    };
    template<typename T>
    Mat<4,T> Ortho(const T left, const T right, const T bottom, const T top) {
        Mat<4,T> result;
        result[0][0] = static_cast<T>(2) / (right - left);
        result[1][1] = static_cast<T>(2) / (top - bottom);
        result[2][2] = - static_cast<T>(1);
        result[3][0] = - (right + left) / (right - left);
        result[3][1] = - (top + bottom) / (top - bottom);
        return result;
    }
    typedef Mat<4,GLfloat> Mat4;
    typedef Mat<4,GLdouble> Mat4d;
}
