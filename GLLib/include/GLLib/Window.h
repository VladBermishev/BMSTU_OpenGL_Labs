#pragma once
#include "GL/gl.h"
#include "GLFW/glfw3.h"
#include <vector>
#include "Primitives/Object.h"
#include "WindowInitParams.h"
#include "Camera.h"
#include "Utils/Timer.h"
#include "Utils/TextRenderer.h"

namespace GLGraphics{
    template<typename WinInitParams>
    class Window{
        GLFWwindow* _window;
        std::vector<Object*> _objects_pull;
    public:
        explicit Window(const WinInitParams& params):_win_init_params(params){
            InitializeWindow();
        }
        explicit Window(WinInitParams&& params):_win_init_params(params){
            InitializeWindow();
        }
        void Run(){
            while(!glfwWindowShouldClose(_window)){
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                for(const auto& obj: _objects_pull){
                    _cam.SetMatrix();
                    obj->Draw();
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
        WinInitParams _win_init_params;
        Vector2ui _window_size;
        void AddObject(Object& obj){ _objects_pull.push_back(&obj); }
        void AddKeyCallback(void (*f)(GLFWwindow*,int,int,int,int)){glfwSetKeyCallback(_window,f);}
        void AddMouseCallback(void (*f)(GLFWwindow*,int,int,int)){glfwSetMouseButtonCallback(_window,f);}
        void AddWindowResizeCallback(void (*f)(GLFWwindow*,int,int)){ glfwSetWindowSizeCallback(_window,f);}
    private:
        void InitializeComponents(){}
        void InitializeWindow(){
            if(!glfwInit()){ exit(EXIT_FAILURE); }
            //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
            glfwWindowHint( GLFW_DOUBLEBUFFER,GL_TRUE );
            _window = glfwCreateWindow(_win_init_params.getSize().x(),
                                       _win_init_params.getSize().y(),
                                       _win_init_params.getTitle().c_str(),
                                       NULL, NULL);

            if (!_window){
                glfwTerminate();
                exit(EXIT_FAILURE);
            }
            glfwSetWindowUserPointer(_window,this);
            glfwMakeContextCurrent(_window);
            glfwSwapInterval(0);
            _window_size = _win_init_params.getSize();
            _win_init_params.GLinit();
            _cam.Init();
        }

    };
}