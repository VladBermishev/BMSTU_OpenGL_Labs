#pragma once

#include "ConycalCilinder.h"
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GLGraphics{
    class ConycalCilinderGLM{
        const static std::uint32_t N = 60;
        Form _form;
        Vector3f _lower_points[N], _upper_points[N];
        const GLdouble _lower_radius, _height, _upper_radius;
    public:
        ConycalCilinderGLM(const GLdouble lower_radius, const GLdouble height, const GLdouble upper_radius) :
                _lower_radius(lower_radius), _height(height), _upper_radius(upper_radius) {
            _form = FILLED;
            InitializeVertex();
        }
        std::vector<GLfloat> getVAO() const{
            std::vector<GLfloat> res;
            res.reserve(10000);
            std::map<Vector3f,std::vector<Vector3f>> tr_normals;
            std::map<Vector3f,Vector3f> normals;
            Vector3f vec;
            for(std::uint32_t i = 0; i < N; i++){
                vec = getTriangleNormVec(_lower_points[i],_upper_points[i],_upper_points[(i+1)%N]);
                tr_normals[_lower_points[i]].push_back(vec);
                tr_normals[_upper_points[i]].push_back(vec);
                tr_normals[_upper_points[(i+1)%N]].push_back(vec);

                vec = getTriangleNormVec(_lower_points[i],_upper_points[(i+1)%N], _lower_points[(i+1)%N]);
                tr_normals[_lower_points[i]].push_back(vec);
                tr_normals[_lower_points[(i+1)%N]].push_back(vec);
                tr_normals[_upper_points[(i+1)%N]].push_back(vec);
            }
            for( auto& [key, value]: tr_normals){
                auto norm = glm::vec3(0);
                for(const auto& elem : value){
                    norm += glm::vec3(elem.x(),elem.y(),elem.z());
                }
                norm = glm::normalize(norm);
                normals[key] = Vector3f(norm.x,norm.y,norm.z);
            }
            for(std::uint32_t i = 0; i < N; i++){
                AddPointToVec(res,normals,_lower_points[i],Vector2f(0,0));
                AddPointToVec(res,normals,_upper_points[(i+1)%N],Vector2f((GLfloat)(i+1)/N,1));
                AddPointToVec(res,normals,_upper_points[i],Vector2f(0,1));
                AddPointToVec(res,normals,_lower_points[i],Vector2f(0,0));
                AddPointToVec(res,normals,_lower_points[(i+1)%N],Vector2f((GLfloat)(i+1)/N,0));
                AddPointToVec(res,normals,_upper_points[(i+1)%N],Vector2f((GLfloat)(i+1)/N,1));
            }
            for(std::uint32_t i = 0; i < N; i++){
                AddPointToVec(res,Vector3f(0,-1,0),Vector3f(0,0,0), Vector2f(0.5,0.5));
                AddPointToVec(res,Vector3f(0,-1,0),_lower_points[i], getTexCoords(_lower_points[i],_lower_radius));
                AddPointToVec(res,Vector3f(0,-1,0),_lower_points[(i+1)%N], getTexCoords(_lower_points[(i+1)%N],_lower_radius));
            }

            for(std::uint32_t i = 0; i < N; i++){
                AddPointToVec(res,Vector3f(0,1,0),Vector3f(0,_height,0), Vector2f(0.5,0.5));
                AddPointToVec(res,Vector3f(0,1,0),_upper_points[i], getTexCoords(_upper_points[i],_upper_radius));
                AddPointToVec(res,Vector3f(0,1,0),_upper_points[(i+1)%N], getTexCoords(_upper_points[(i+1)%N],_upper_radius));
            }
            return res;
        }
    private:
        void InitializeVertex() noexcept{
            for(std::uint32_t i = 0; i < N; i++){
                const GLdouble x = _lower_radius * cos(2*M_PI*((GLdouble)i/N));
                const GLdouble z = _lower_radius * sin(2*M_PI*((GLdouble)i/N));
                _lower_points[i] = Vector3f(x, 0, z);
            }
            for(std::uint32_t i = 0; i < N; i++){
                const GLdouble x = _upper_radius * cos(2*M_PI*((GLdouble)i/N));
                const GLdouble z = _upper_radius * sin(2*M_PI*((GLdouble)i/N));
                _upper_points[i] = Vector3f(x, _height, z);
            }
        }
        static Vector3f getTriangleNormVec(const Vector3f& a, const Vector3f& b, const Vector3f& c){
            auto vec = b-a;
            auto _a = glm::vec3(vec.x(),vec.y(),vec.z());
            vec = c-a;
            auto _b = glm::vec3(vec.x(),vec.y(),vec.z());
            auto norm = glm::normalize(glm::cross(_a,_b));
            return Vector3f(norm.x,norm.y,norm.z);
        }
        static void AddPointToVec(std::vector<GLfloat>& res, const Vector3f& normal,
                                  const Vector3f& point,const Vector2f& TexCoords){
            res.push_back(point.x());res.push_back(point.y());res.push_back(point.z());
            res.push_back(normal.x());res.push_back(normal.y());res.push_back(normal.z());
            res.push_back(TexCoords.x());res.push_back(TexCoords.y());
        }
        static void AddPointToVec(std::vector<GLfloat>& res, std::map<Vector3f,Vector3f>& normals,
                           const Vector3f& point,const Vector2f& TexCoords){
            AddPointToVec(res,normals[point],point,TexCoords);
        }
        static Vector2f getTexCoords(const Vector3f& point, const GLdouble radius){
            return Vector2f(point.x()/(2*radius)+0.5,point.z()/(2*radius)+0.5);
        }
    };
}