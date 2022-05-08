#include <cstdlib>
#include <iostream>
#include "GLLib/GLLib.h"
template<typename WinInitParams>
class Lab4Window : public GLGraphics::Window<WinInitParams> {
    GLGraphics::ComplexPolygon _cp;
public:
    explicit Lab4Window(const WinInitParams &params) : GLGraphics::Window<WinInitParams>(params){
        InitializeComponents();
    }

    explicit Lab4Window(WinInitParams &&params) : GLGraphics::Window<WinInitParams>(params) {
        InitializeComponents();
    }

    inline static void
    KeyCallback(GLFWwindow *window, const int key, const int scancode, const int action, const int mods) {
        auto *m_window = (Lab4Window*) (glfwGetWindowUserPointer(window));
        if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
            m_window->_cp.show_areas() = !m_window->_cp.show_areas();
        }
        if (key == GLFW_KEY_X && action == GLFW_PRESS) {
            m_window->_cp.fill_polygon() = !m_window->_cp.fill_polygon();
        }
        if (key == GLFW_KEY_C && action == GLFW_PRESS) {
            m_window->_cp.convolution_enabled() = !m_window->_cp.convolution_enabled();
        }
    }
    inline static void
    MouseCallback(GLFWwindow *window, const int button, const int action, const int mods){
        auto *m_window = (Lab4Window*) (glfwGetWindowUserPointer(window));
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
            GLGraphics::Vector2<GLdouble> pos;
            glfwGetCursorPos(window,&pos.x(),&pos.y());
            pos.y() = m_window->_window_size.y() - static_cast<std::uint32_t>(pos.y());
            m_window->_cp.AddPoint(GLGraphics::Vector2ui(static_cast<std::uint32_t>(pos.x()),
                                                         static_cast<std::uint32_t>(pos.y())));
            printf("%f %f\n",pos.x(),pos.y());
        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
            m_window->_cp.Clear();
        }
    }
    inline static void ResizeCallback(GLFWwindow* window, const int width, const int height){
        auto* m_window = (Lab4Window*)(glfwGetWindowUserPointer(window));
        m_window->_cam.ProjectionOrtho(0,width,0,height);
        const GLfloat x_scale = width/static_cast<GLfloat>(m_window->_window_size.x());
        const GLfloat y_scale = height/static_cast<GLfloat>(m_window->_window_size.y());
        m_window->_cp.Resize(x_scale,y_scale);
        glViewport(0, 0, width, height);
        m_window->_window_size = GLGraphics::Vector2ui(width,height);
    }

protected:
    void InitializeComponents() {
        this->_cam.ProjectionOrtho(0,this->_win_init_params.getSize().x(),
                                   0,this->_win_init_params.getSize().y());
        this->AddObject(_cp);
        this->AddKeyCallback(Lab4Window::KeyCallback);
        this->AddMouseCallback(Lab4Window::MouseCallback);
        this->AddWindowResizeCallback(Lab4Window::ResizeCallback);
    }
};

class Lab4WindowInitParams : public GLGraphics::WindowInitParams {
public:
    Lab4WindowInitParams() = default;

    Lab4WindowInitParams(const std::string &title, const GLGraphics::Vector2ui &size) : GLGraphics::WindowInitParams(
            title, size) {}

    void GLinit() const noexcept {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            //LOG SMTH
            exit(-1);
        }
        glEnable(GL_CULL_FACE);
        glClearColor(1, 1, 1, 1);
    }
};

int main() {
    Lab4WindowInitParams initialParams("ConycalCilinder", GLGraphics::Vector2ui(1000, 1000));
    Lab4Window window(initialParams);
    window.Run();
    return EXIT_SUCCESS;
}
//заполнения многоугольника по ребрам, постфильтрация с взвешенным усреднением области 3x3, целочисленный алгоритм Брезенхема