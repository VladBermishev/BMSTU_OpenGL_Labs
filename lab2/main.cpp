#include "stdlib.h"
#include "../GLLib/include/GLLib/GLLib.h"
template<typename WinInitParams>
class Lab2Window: public GLGraphics::Window<WinInitParams>{
    constexpr const static GLdouble theta = 35.26, phi = 45;
    constexpr const static GLdouble speed = 5, scaling_speed = 0.1;
    GLGraphics::Cube _cube,_static_cube;
    GLdouble _cube_x_angle, _cube_y_angle, _cube_scale;
    std::uint32_t last_key = 0;
public:
    explicit Lab2Window(const WinInitParams& params) : GLGraphics::Window<WinInitParams>(params) {
        InitializeComponents();
    }

    explicit Lab2Window(WinInitParams&& params) : GLGraphics::Window<WinInitParams>(params) {
        InitializeComponents();
    }
    inline static void KeyCallback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods) {
        auto *m_window = (Lab2Window*) (glfwGetWindowUserPointer(window));
        if(key == GLFW_KEY_A){
            if(m_window->last_key != 0 && m_window->last_key != GLFW_KEY_A && m_window->last_key != GLFW_KEY_D){
                m_window->relax_cube_pos();
            }
            m_window->_cube.ModelViewRotate(speed,0,1,0);
            m_window->_cube_y_angle += speed;
        }
        if(key == GLFW_KEY_D){
            if(m_window->last_key != 0 && m_window->last_key != GLFW_KEY_A && m_window->last_key != GLFW_KEY_D){
                m_window->relax_cube_pos();
            }
            m_window->_cube.ModelViewRotate(-speed,0,1,0);
            m_window->_cube_y_angle -= speed;
        }
        if(key == GLFW_KEY_W){
            if(m_window->last_key != 0 && m_window->last_key != GLFW_KEY_S && m_window->last_key != GLFW_KEY_W){
                m_window->relax_cube_pos();
            }
            m_window->_cube.ModelViewRotate(speed,1,0,0);
            m_window->_cube_x_angle += speed;
        }
        if(key == GLFW_KEY_S){
            if(m_window->last_key != 0 && m_window->last_key != GLFW_KEY_S && m_window->last_key != GLFW_KEY_W){
                m_window->relax_cube_pos();
            }
            m_window->_cube.ModelViewRotate(-speed,1,0,0);
            m_window->_cube_x_angle -= speed;
        }
        if(key == GLFW_KEY_X && action == GLFW_PRESS){
            m_window->_cube.ChangeFormOnOpposite();
            m_window->_static_cube.ChangeFormOnOpposite();
        }
        if(key == GLFW_KEY_EQUAL && action == GLFW_PRESS){
            m_window->_cube_scale = 1 + scaling_speed;
            m_window->_cube.ModelViewScale(m_window->_cube_scale,m_window->_cube_scale,m_window->_cube_scale);
        }
        if(key == GLFW_KEY_MINUS && action == GLFW_PRESS){
            m_window->_cube_scale = 1 - scaling_speed;
            m_window->_cube.ModelViewScale(m_window->_cube_scale,m_window->_cube_scale,m_window->_cube_scale);
        }
        m_window->last_key = key;
    }
    void relax_cube_pos(){
        _cube.ModelViewIdentity();
    }
protected:
    void InitializeComponents() {
        _cube_x_angle = 0;_cube_y_angle = 0;
        _cube_scale = 1;
        this->_cam.ProjectionRotate(-theta,1,0,0);
        this->_cam.ProjectionRotate(phi,0,1,0);
        _static_cube.ModelViewTranslate(0.5,0.90,0.65);
        _static_cube.ModelViewScale(0.5,0.5,0.5);
        this->AddObject(_cube);
        this->AddObject(_static_cube);
        this->AddKeyCallback(Lab2Window::KeyCallback);
    }
};
class Lab2WindowInitParams: public GLGraphics::WindowInitParams{
public:
    Lab2WindowInitParams() = default;
    Lab2WindowInitParams(const std::string& title, const GLGraphics::Vector2i& size): GLGraphics::WindowInitParams(title,size){}
    void GLinit() const noexcept{
        glEnable(GL_DEPTH_TEST);
        glClearColor(1,1,1,1);
    }
};

int main(){
    Lab2WindowInitParams initialParams("Circle",GLGraphics::Vector2i(1000,1000));
    Lab2Window window(initialParams);
    window.Run();
    return EXIT_SUCCESS;
}