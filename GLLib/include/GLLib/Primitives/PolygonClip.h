#pragma once

#include <GL/gl.h>
#include <GLLib/Types/Vector2.h>
#include <GLLib/Primitives/Circle.h>
#include <GLLib/Primitives/Object.h>
#include <vector>
#include <chrono>

namespace GLGraphics {
    class PolygonClip : public Object {
        const static std::uint32_t AreaRadius = 10;
        const static std::uint32_t N = 60;
        constexpr const static GLfloat _kernel[3][3] = {{0,       1.f / 6, 0},
                                                        {1.f / 6, 2.f / 6, 1.f / 6},
                                                        {0,       1.f / 6, 0}};
        std::vector<Vector2ui> _points;
        std::int32_t _product_sign;
        std::vector<Vector2i> _norms;
        std::vector<Vector2ui> _line_to_clip;
        bool _show_areas, _fill_polygon, _convolution_enabled, _clip_line;
        bool _polygon_finished;
    public:
        PolygonClip() {
            _show_areas = false;
            _fill_polygon = false;
            _convolution_enabled = false;
            _polygon_finished = false;
            _clip_line = false;
        }

        void SetVertex() final {
            auto t0 = std::chrono::high_resolution_clock::now();
            for (std::uint32_t i = 0; _points.size() > 1 && i < _points.size() - 1; i++) {
                DrawLineBresenham(_points[i], _points[i + 1]);
                /*
                if(_polygon_finished){
                    DrawLineBresenham(_points[i],_points[i]+_norms[i]);
                }
                */
            }
            if (_clip_line && _line_to_clip.size() > 1 && _polygon_finished) {
                ClipLine(_points, _norms, _line_to_clip);
            }else if (_line_to_clip.size() > 1) {
                for (int i = 0; i < _line_to_clip.size() - 1; i++) {
                    DrawLineBresenham(_line_to_clip[i], _line_to_clip[i + 1]);
                }
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
            //printf("%ld ms\n",std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t0).count());
        }

        void PolygonFinished() {
            if (!is_convex(_points, &_product_sign)) {
                fprintf(stderr, "Polygon is not convex\n");
                Clear();
                return;
            }
            for (std::uint32_t i = 0; i < _points.size() - 1; i++) {
                Vector2i a(_points[i]), b(_points[i + 1]);
                Vector2i vec(b.x() - a.x(), b.y() - a.y());
                _norms.push_back(perpendic(vec) * _product_sign);
            }
            _polygon_finished = true;
        }

        void AddPoint(const Vector2ui &point) {
            if (!_polygon_finished) {
                for (const auto &pos: _points) {
                    if (Euclid_distance(pos, point) < AreaRadius) {
                        _points.push_back(pos);
                        PolygonFinished();
                        return;
                    }
                }
                _points.push_back(point);
            } else if (_line_to_clip.size() < 2) {
                _line_to_clip.push_back(point);
            }
        }

        void Resize(const GLfloat x_scale, const GLfloat y_scale) {
            for (auto &pos: _points) {
                pos.x() = pos.x() * x_scale;
                pos.y() = pos.y() * y_scale;
            }
        }

        inline void Clear() {
            if (_line_to_clip.empty()) {
                _points.clear();
                _norms.clear();
                _polygon_finished = false;
            } else {
                _line_to_clip.clear();
            }
        }

        inline bool &show_areas() noexcept { return _show_areas; }

        inline bool &fill_polygon() noexcept { return _fill_polygon; }

        inline bool &convolution_enabled() noexcept { return _convolution_enabled; }

        inline bool &clip_line() noexcept { return _clip_line; }

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

        static void ClipLine(const std::vector<Vector2ui> &points,
                             const std::vector<Vector2i> &norms,
                             const std::vector<Vector2ui> &line_to_clip,
                             bool is_inner = false) {
            float xn, yn, dx, dy, r;
            float CB_t0, CB_t1;
            float Qx, Qy;
            float Nx, Ny;
            float Pn, Qn;
            bool is_intersect = true;
            CB_t0 = 0;
            CB_t1 = 1;
            xn = line_to_clip[0].x();
            yn = line_to_clip[0].y();
            dx = line_to_clip[1].x() - xn;
            dy = line_to_clip[1].y() - yn;
            for (std::int32_t i = 0; i < points.size() - 1; ++i) {
                Qx = xn - points[i].x();
                Qy = yn - points[i].y();
                Nx = norms[i].x();
                Ny = norms[i].y();
                Pn = dx * Nx + dy * Ny;
                Qn = Qx * Nx + Qy * Ny;
                if (Pn == 0) {
                    if (Qn < 0) { is_intersect = false; break; }
                } else {
                    r = -Qn / Pn;
                    if (Pn < 0) {
                        if (r < CB_t0) { is_intersect = false; break; }
                        if (r < CB_t1) CB_t1 = r;
                    } else {
                        if (r > CB_t1) { is_intersect = false; break; }
                        if (r > CB_t0) CB_t0 = r;
                    }
                }
            }
            Vector2ui intersection_point_first, intersection_point_second;
            if (CB_t0 < CB_t1){
                if (CB_t0 > 0) {
                    intersection_point_first.x() = xn + CB_t0 * dx;
                    intersection_point_first.y() = yn + CB_t0 * dy;
                }
                if (CB_t1 < 1) {
                    intersection_point_second.x() = xn + CB_t1 * dx;
                    intersection_point_second.y() = yn + CB_t1 * dy;
                }
            }
            if(!is_intersect){
                DrawLineBresenham(line_to_clip[0],line_to_clip[1]);
            }else if(is_inner){
                DrawLineBresenham(intersection_point_first,intersection_point_second);
            }else{
                DrawLineBresenham(line_to_clip[0],intersection_point_first);
                DrawLineBresenham(intersection_point_second,line_to_clip[1]);
            }
        }

        static void EdgeFilling(const std::vector<Vector2ui> &points) {
            GLint dims[4] = {0};
            const GLint format = GL_RGB;
            const GLuint format_size = 3;
            glGetIntegerv(GL_VIEWPORT, dims);
            glPixelStorei(GL_PACK_ALIGNMENT, 1);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
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
                Vector2i a(points[i].x(), points[i].y()), b(points[i + 1].x(), points[i + 1].y());
                std::uint32_t max_y = std::max(points[i].y(), points[i + 1].y());
                std::uint32_t min_y = std::min(points[i].y(), points[i + 1].y());
                std::uint32_t max_x = std::max(points[i].x(), points[i + 1].x());
                std::uint32_t min_x = std::min(points[i].x(), points[i + 1].x());
                for (std::uint32_t idy = max_y; idy > min_y; idy--) {
                    std::uint32_t idx = format_size * dims[2] * idy;
                    if (max_y == min_y || max_x == min_x) {
                        idx += format_size * (max_x + 1);
                    } else {
                        idx += format_size *
                               (((GLfloat) (a.x() * b.y() - a.y() * b.x() - (a.x() - b.x()) * (int) idy)) /
                                ((GLfloat) (b.y() - a.y())));
                        while (idx < format_size * dims[2] * (idy + 1) - format_size + 1 && front_pixels[idx] == 1 &&
                               front_pixels[idx + 1] == 1 && front_pixels[idx + 2] == 1)
                            idx += format_size;
                        while (idx < format_size * dims[2] * (idy + 1) - format_size + 1 && front_pixels[idx] == 0 &&
                               front_pixels[idx + 1] == 0 && front_pixels[idx + 2] == 0)
                            idx += format_size;
                    }
                    while (idx < format_size * dims[2] * (idy + 1) - format_size + 1) {
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

        template<size_t N, typename std::enable_if<N % 2 == 1, bool>::type = true>
        static void Convolution(const GLfloat (&kernel)[N][N]) noexcept {
            const GLint format = GL_RGB;
            const GLuint format_size = 3;
            constexpr const std::uint32_t off_x = (N - 1) / 2;
            constexpr const std::uint32_t off_y = off_x;
            const GLfloat *_sc_kernel = ((GLfloat *) &kernel[0]);
            GLfloat point[format_size];
            GLint dims[4] = {0};
            glGetIntegerv(GL_VIEWPORT, dims);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            std::vector<GLfloat> front_framebuffer(dims[2] * dims[3] * format_size, 1);
            std::vector<GLfloat> back_framebuffer(dims[2] * dims[3] * format_size, 1);
            glReadBuffer(GL_BACK);
            glReadPixels(0, 0, dims[2], dims[3], format, GL_FLOAT, front_framebuffer.data());
            for (std::uint32_t j = off_y; j < dims[3] - off_y; j++) {
                for (std::uint32_t i = off_x; i < dims[2] - off_x; i++) {
                    memset(&point[0], 0, sizeof(GLfloat) * 3);
                    for (std::int32_t dy = -static_cast<std::int32_t>(off_y);
                         dy <= static_cast<std::int32_t>(off_y); dy++) {
                        for (std::int32_t dx = -static_cast<std::int32_t>(off_x);
                             dx <= static_cast<std::int32_t>(off_x); dx++) {
                            const std::uint32_t framebuffer_idx = format_size * (dims[2] * (j + dy) + i + dx);
                            const std::uint32_t kernel_idx = N * (dy + off_y) + dx + off_x;
                            point[0] += front_framebuffer[framebuffer_idx] * _sc_kernel[kernel_idx];
                            point[1] += front_framebuffer[framebuffer_idx + 1] * _sc_kernel[kernel_idx];
                            point[2] += front_framebuffer[framebuffer_idx + 2] * _sc_kernel[kernel_idx];
                        }
                    }
                    memcpy(&back_framebuffer[format_size * (dims[2] * j + i)], &point[0], sizeof(GLfloat) * 3);
                }
            }
            glRasterPos2i(0, 0);
            glDrawPixels(dims[2], dims[3], format, GL_FLOAT, &back_framebuffer[0]);
        }

        static void DrawLineBresenham(const Vector2ui &_a, const Vector2ui &_b) noexcept {
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

        static GLdouble VecRotation(const Vector2ui &a, const Vector2ui &b, const Vector2ui &c, const Vector2ui &d) {
            Vector2i _a(a.x(), a.y()), _b(b.x(), b.y()), _c(c.x(), c.y()), _d(d.x(), d.y());
            return (_b.x() - _a.x()) * (_d.y() - _c.y()) - (_b.y() - _a.y()) * (_d.x() - _c.x());
        }

        static bool is_line_initialized(std::pair<Vector2ui, Vector2ui> &line) {
            return line.first.x() != -1 && line.first.y() != -1 && line.second.x() != -1 && line.second.y() != -1;
        }

        static bool is_convex(const std::vector<Vector2ui> &points, std::int32_t *product_sign) {
            if (points.size() < 3) { return false; }
            auto vecRot = PolygonClip::VecRotation(points[0], points[1], points[1], points[2]);
            *product_sign = vecRot > 0 ? 1 : -1;
            int sign;
            std::uint32_t _points_size = points.size();
            for (int i = 1; i < _points_size; i++) {
                vecRot = VecRotation(points[i], points[(i + 1) % _points_size],
                                     points[(i + 1) % _points_size], points[(i + 2) % _points_size]);
                sign = vecRot > 0 ? 1 : -1;
                if (vecRot != 0 && sign != *product_sign) { return false; }
            }
            return true;
        }
    };
}
