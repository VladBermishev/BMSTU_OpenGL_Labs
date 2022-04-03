#pragma once
#include "Primitives/Object.h"
#include "WindowInitParams.h"
#include "Camera.h"
#include "GL/gl.h"
#include "GLFW/glfw3.h"
#include <vector>
#include <unordered_map>
#include <functional>
namespace GLGraphics{
    template<typename WinInitParams>
    class Window{
        GLFWwindow* _window;
        std::vector<Object*> _objects_pull;
    public:
        explicit Window(const WinInitParams& params){
            InitializeWindow(params);
        }
        explicit Window(WinInitParams&& params){
            InitializeWindow(params);
        }
        void Run(){
            while(!glfwWindowShouldClose(_window)){
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                for(const auto& obj: _objects_pull){
                    _cam.SetMatrix();
                    obj->Draw();
                    glFlush();
                }
                glfwSwapBuffers(_window);
                glfwPollEvents();
            }
        }
        ~Window(){
            glfwDestroyWindow(_window);
            glfwTerminate();
        }
    protected:
        GLGraphics::Camera _cam;
        void AddObject(Object& obj){ _objects_pull.push_back(&obj); }
        void AddKeyCallback(void (*f)(GLFWwindow*,int,int,int,int)){glfwSetKeyCallback(_window,f);}
    private:
        void InitializeComponents(){}
        void InitializeWindow(const WinInitParams& params){
            if(!glfwInit()){ exit(EXIT_FAILURE); }
            _window = glfwCreateWindow(params.getSize().x(), params.getSize().y(), params.getTitle().c_str(), NULL, NULL);
            if (!_window){
                glfwTerminate();
                exit(EXIT_FAILURE);
            }
            glfwSetWindowUserPointer(_window,this);
            glfwMakeContextCurrent(_window);
            params.GLinit();
            _cam.Init();
        }
        void InitializeWindow(WinInitParams&& params){
            if(!glfwInit()){ exit(EXIT_FAILURE); }
            _window = glfwCreateWindow(params.getSize().x(), params.getSize().y(), params.getTitle().c_str(), NULL, NULL);
            if (!_window){
                glfwTerminate();
                exit(EXIT_FAILURE);
            }
            glfwSetWindowUserPointer(_window,this);
            glfwMakeContextCurrent(_window);
            glLoadIdentity();
            params.GLinit();
        }

    };
}