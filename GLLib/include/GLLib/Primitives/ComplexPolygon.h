#pragma once

#include <GL/gl.h>
#include <GLLib/Types/Vector2.h>
#include <GLLib/Primitives/Circle.h>
#include <GLLib/Primitives/Object.h>
#include <vector>
#include <iostream>
#include <chrono>

namespace GLGraphics {
    class ComplexPolygon : public Object {
        const static std::uint32_t AreaRadius = 10;
        const static std::uint32_t N = 60;
        constexpr const static GLfloat _kernel[3][3]  = {{0,1.f/6,0},{1.f/6,2.f/6,1.f/6},{0,1.f/6,0}};
        std::vector<Vector2ui> _points;
        bool _show_areas, _fill_polygon, _convolution_enabled;
    public:
        ComplexPolygon() {
            _show_areas = false;
            _fill_polygon = false;
            _convolution_enabled = false;
        }

        void SetVertex() final {
            typedef std::chrono::high_resolution_clock Time;
            typedef std::chrono::milliseconds ms;
            typedef std::chrono::duration<float> fsec;
            auto t0 = Time::now();
            for (std::uint32_t i = 0; _points.size() > 1 && i < _points.size() - 1; i++) {
                DrawLineBresenham(_points[i], _points[i + 1]);
            }
            if (_points.size() > 2 && _fill_polygon) {
                EdgeFilling(_points);
            }
            if (_convolution_enabled) {
                Convolution(_kernel);
            }
            if (_show_areas) {
                for (const auto &pos: _points) { DrawCircle(pos); }
            }
            std::cout << std::chrono::duration_cast<ms>(Time::now() - t0).count() << "ms\n";
        }


        inline void AddPoint(const Vector2ui &point) {
            Vector2ui point_to_append = point;
            for (const auto &pos: _points) {
                if (Euclid_distance(pos, point) < AreaRadius) {
                    point_to_append = pos;
                    break;
                }
            }
            _points.push_back(point_to_append);
        }
        inline void Resize(const GLfloat x_scale, const GLfloat y_scale){
            for (auto &pos: _points) {
                pos.x() = pos.x()*x_scale;
                pos.y() = pos.y()*y_scale;
            }
        }
        inline void Clear() {
            _points.clear();
        }

        inline bool &show_areas() noexcept { return _show_areas; }

        inline bool &fill_polygon() noexcept { return _fill_polygon; }

        inline bool &convolution_enabled() noexcept { return _convolution_enabled; }

        static void DrawCircle(const Vector2ui &pos) {
            glBegin(GL_POLYGON);
            glColor3f(1, 0, 0);
            for (std::uint32_t i = 0; i < N; i++) {
                const float phi = 2.0 * M_PI * ((GLdouble) i / N);
                const float x = AreaRadius * cosf(phi);
                const float y = AreaRadius * sinf(phi);
                glVertex2f(pos.x() + x, pos.y() + y);
            }
            glEnd();
        }
        static void EdgeFilling(const std::vector<Vector2ui>& points){
            GLint dims[4] = {0};
            const GLint format = GL_RGB;
            const GLuint format_size = 3;
            glGetIntegerv(GL_VIEWPORT, dims);
            glPixelStorei(GL_PACK_ALIGNMENT,1);
            glPixelStorei(GL_UNPACK_ALIGNMENT,1);
            glReadBuffer(GL_BACK);
            glDrawBuffer(GL_FRONT);
            glBlitFramebuffer(0, 0, dims[2], dims[3], 0, 0, dims[2], dims[3], GL_COLOR_BUFFER_BIT, GL_NEAREST);
            std::vector<GLfloat> front_pixels(format_size * dims[2] * dims[3], 1);
            std::vector<GLfloat> back_pixels(format_size * dims[2] * dims[3], 1);
            glReadBuffer(GL_FRONT);
            glReadPixels(0, 0, dims[2], dims[3], format, GL_FLOAT, front_pixels.data());
            glReadBuffer(GL_BACK);
            glReadPixels(0, 0, dims[2], dims[3], format, GL_FLOAT, back_pixels.data());
            for (std::uint32_t i = 0; i < points.size() - 1; i++) {
                Vector2i a(points[i].x(), points[i].y()), b(points[i + 1].x(), points[i+1].y());
                std::uint32_t max_y = std::max(points[i].y(), points[i + 1].y());
                std::uint32_t min_y = std::min(points[i].y(), points[i + 1].y());
                std::uint32_t max_x = std::max(points[i].x(), points[i + 1].x());
                std::uint32_t min_x = std::min(points[i].x(), points[i + 1].x());
                for (std::uint32_t idy = max_y; idy > min_y; idy--) {
                    std::uint32_t idx = format_size *dims[2]*idy;
                    if (max_y == min_y || max_x == min_x) {
                        idx += format_size * (max_x + 1);
                    } else {
                        idx += format_size *
                              (((GLfloat) (a.x() * b.y() - a.y() * b.x() - (a.x() - b.x()) * (int) idy)) /
                               ((GLfloat) (b.y() - a.y())));
                        while (idx < format_size *dims[2]*(idy+1) - format_size + 1 && front_pixels[idx] == 1 &&
                               front_pixels[idx + 1] == 1 && front_pixels[idx + 2] == 1)
                            idx += format_size;
                        while (idx < format_size *dims[2]*(idy+1) - format_size + 1 && front_pixels[idx] == 0 &&
                               front_pixels[idx + 1] == 0 && front_pixels[idx + 2] == 0)
                            idx += format_size;
                    }
                    while (idx < format_size *dims[2]*(idy+1) - format_size + 1) {
                        if (!(front_pixels[idx] == 0 && front_pixels[idx + 1] == 0 && front_pixels[idx + 2] == 0)) {
                            back_pixels[idx] = 1 - back_pixels[idx];
                            back_pixels[idx + 1] = back_pixels[idx];
                            back_pixels[idx + 2] = back_pixels[idx];
                        }
                        idx += format_size;
                    }
                }
            }
            glDrawBuffer(GL_BACK);
            glRasterPos2i(0, 0);
            glDrawPixels(dims[2], dims[3], format, GL_FLOAT, back_pixels.data());
        }

        template<size_t N, typename std::enable_if<N%2==1,bool>::type = true>
        static void Convolution(const GLfloat (&kernel)[N][N]) noexcept{
            const GLint format = GL_RGB;
            const GLuint format_size = 3;
            constexpr const std::uint32_t off_x = (N-1)/2;
            constexpr const std::uint32_t off_y = off_x;
            const GLfloat* _sc_kernel = ((GLfloat*)&kernel[0]);
            GLfloat point[format_size];
            GLint dims[4] = {0};
            glGetIntegerv(GL_VIEWPORT, dims);
            glPixelStorei(GL_UNPACK_ALIGNMENT,1);
            std::vector<GLfloat> front_framebuffer(dims[2] * dims[3] * format_size, 1);
            std::vector<GLfloat> back_framebuffer(dims[2] * dims[3] * format_size, 1);
            glReadBuffer(GL_BACK);
            glReadPixels(0,0,dims[2],dims[3],format,GL_FLOAT,front_framebuffer.data());
            for(std::uint32_t j = off_y; j < dims[3]-off_y; j++){
                for(std::uint32_t i = off_x; i < dims[2]-off_x; i++){
                    memset(&point[0],0,sizeof(GLfloat)*3);
                    for(std::int32_t dy = -static_cast<std::int32_t>(off_y); dy <= static_cast<std::int32_t>(off_y); dy++){
                        for(std::int32_t dx = -static_cast<std::int32_t>(off_x); dx <= static_cast<std::int32_t>(off_x); dx++){
                            const std::uint32_t framebuffer_idx = format_size*(dims[2]*(j+dy)+i+dx);
                            const std::uint32_t kernel_idx = N*(dy+off_y)+dx+off_x;
                            point[0] += front_framebuffer[framebuffer_idx] * _sc_kernel[kernel_idx];
                            point[1] += front_framebuffer[framebuffer_idx+1] * _sc_kernel[kernel_idx];
                            point[2] += front_framebuffer[framebuffer_idx+2] * _sc_kernel[kernel_idx];
                        }
                    }
                    memcpy(&back_framebuffer[format_size*(dims[2]*j+i)],&point[0],sizeof(GLfloat)*3);
                }
            }
            glRasterPos2i(0, 0);
            glDrawPixels(dims[2],dims[3],format,GL_FLOAT,&back_framebuffer[0]);
        }

        static void DrawLineBresenham(const Vector2ui &_a, const Vector2ui &_b) noexcept{
            glBegin(GL_POINTS);
            glColor3f(0, 0, 0);
            Vector2i a(_a.x(), _a.y()), b(_b.x(), _b.y());
            std::int32_t dx = (b.x() - a.x() >= 0 ? 1 : -1);
            std::int32_t dy = (b.y() - a.y() >= 0 ? 1 : -1);
            std::int32_t lengthX = abs(b.x() - a.x());
            std::int32_t lengthY = abs(b.y() - a.y());
            std::int32_t length = lengthX > lengthY ? lengthX : lengthY;
            if (length == 0) {
                glVertex2i(a.x(), a.y());
            }
            std::int32_t x = a.x();
            std::int32_t y = a.y();
            if (lengthY <= lengthX) {
                std::int32_t d = -lengthX;
                length++;
                while (length--) {
                    glVertex2i(x, y);
                    x += dx;
                    d += 2 * lengthY;
                    if (d > 0) {
                        d -= 2 * lengthX;
                        y += dy;
                    }
                }
            } else {
                std::int32_t d = -lengthY;
                length++;
                while (length--) {
                    glVertex2i(x, y);
                    y += dy;
                    d += 2 * lengthX;
                    if (d > 0) {
                        d -= 2 * lengthY;
                        x += dx;
                    }
                }
            }
            glEnd();
        }
    };
}
