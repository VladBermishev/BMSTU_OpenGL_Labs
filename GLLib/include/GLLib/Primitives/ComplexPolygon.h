#pragma once
#include <GL/gl.h>
#include <GLLib/Types/Vector2.h>
#include <GLLib/Primitives/Circle.h>
#include <GLLib/Primitives/Object.h>
#include <vector>

namespace GLGraphics{
    class ComplexPolygon: public Object{
        const static std::uint32_t AreaRadius = 10;
        const static std::uint32_t N = 60;
        std::vector<Vector2ui> _points;
        bool _show_areas, _fill_polygon;
    public:
        ComplexPolygon(){_show_areas = false; _fill_polygon = false;}
        void SetVertex() final{
            for(std::uint32_t i = 0; _points.size() > 1 && i < _points.size()-1; i++){
                DrawLineBresenham(_points[i],_points[i+1]);
            }
            if(_show_areas){
                for(const auto& pos: _points){ DrawCircle(pos);}
            }
            if(_fill_polygon){

            }
        }


        inline void AddPoint(const Vector2ui& point){
            Vector2ui point_to_append = point;
            for(const auto& pos: _points){
                if(Euclid_distance(pos,point) < AreaRadius){
                    point_to_append = pos;
                    break;
                }
            }
            _points.push_back(point_to_append);
        }
        inline void Clear(){
            _points.clear();
        }
        inline bool& show_areas()noexcept{return _show_areas;}
        inline bool& fill_polygon()noexcept{return _fill_polygon;}
        static void DrawCircle(const Vector2ui& pos){
            glBegin(GL_POLYGON);
            glColor3f(1,0,0);
            for(std::uint32_t i = 0; i < N; i++){
                const float phi = 2.0 * M_PI * ((GLdouble)i/N);
                const float x = AreaRadius * cosf(phi);
                const float y = AreaRadius * sinf(phi);
                glVertex2f(pos.x()+x, pos.y()+y);
            }
            glEnd();
        }
        static void DrawLineBresenham(const Vector2ui& _a, const Vector2ui& _b){
            glBegin(GL_POINTS);
            glColor3f(0,0,0);
            Vector2i a(_a.x(),_a.y()), b(_b.x(),_b.y());
            std::int32_t dx = (b.x() - a.x() >= 0 ? 1 : -1);
            std::int32_t dy = (b.y() - a.y() >= 0 ? 1 : -1);
            std::int32_t lengthX = abs(b.x() - a.x());
            std::int32_t lengthY = abs(b.y() - a.y());
            std::int32_t length = lengthX > lengthY?lengthX:lengthY;
            if (length == 0){glVertex2i(a.x(), a.y());}
            std::int32_t x = a.x();
            std::int32_t y = a.y();
            if (lengthY <= lengthX){
                std::int32_t d = -lengthX;
                length++;
                while(length--){
                    glVertex2i(x,y);
                    x += dx;
                    d += 2 * lengthY;
                    if (d > 0) {
                        d -= 2 * lengthX;
                        y += dy;
                    }
                }
            }else{
                std::int32_t d = -lengthY;
                length++;
                while(length--){
                    glVertex2i(x,y);
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
