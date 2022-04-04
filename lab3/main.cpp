#include <cstdlib>
#include "GLLib/GLLib.h"
template<typename WinInitParams>
class Lab3Window : public GLGraphics::Window<WinInitParams> {
    constexpr const static GLdouble theta = 35.26, phi = 45;
    constexpr const static GLdouble speed = 5, scaling_speed = 0.1;
    GLdouble _cilinder_x_angle, _cilinder_y_angle, _cilinder_scale;
    GLGraphics::ConycalCilinder _cilinder, _static_cilinder;
public:
    explicit Lab3Window(const WinInitParams &params) : GLGraphics::Window<WinInitParams>(params),
                                                       _cilinder(0.25, 0.4, 0.1), _static_cilinder(0.25, 0.4, 0.1) {
        InitializeComponents();
    }

    explicit Lab3Window(WinInitParams &&params) : GLGraphics::Window<WinInitParams>(params) {
        InitializeComponents();
    }

    inline static void
    KeyCallback(GLFWwindow *window, const int key, const int scancode, const int action, const int mods) {
        auto *m_window = (Lab3Window *) (glfwGetWindowUserPointer(window));
        if (key == GLFW_KEY_A) {
            m_window->_cilinder.ModelViewRotate(speed, 0, 1, 0);
            m_window->_cilinder_y_angle += speed;
        }
        if (key == GLFW_KEY_D) {
            m_window->_cilinder.ModelViewRotate(-speed, 0, 1, 0);
            m_window->_cilinder_y_angle -= speed;
        }
        if (key == GLFW_KEY_W) {
            m_window->_cilinder.ModelViewRotate(speed, 1, 0, 0);
            m_window->_cilinder_x_angle += speed;
        }
        if (key == GLFW_KEY_S) {
            m_window->_cilinder.ModelViewRotate(-speed, 1, 0, 0);
            m_window->_cilinder_x_angle -= speed;
        }
        if (key == GLFW_KEY_X && action == GLFW_PRESS) {
            m_window->_cilinder.ChangeFormOnOpposite();
            m_window->_static_cilinder.ChangeFormOnOpposite();
        }
        if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS) {
            m_window->_cilinder_scale = 1 + scaling_speed;
            m_window->_cilinder.ModelViewScale(m_window->_cilinder_scale, m_window->_cilinder_scale, m_window->_cilinder_scale);
        }
        if (key == GLFW_KEY_MINUS && action == GLFW_PRESS) {
            m_window->_cilinder_scale = 1 - scaling_speed;
            m_window->_cilinder.ModelViewScale(m_window->_cilinder_scale, m_window->_cilinder_scale, m_window->_cilinder_scale);
        }
        if (key == GLFW_KEY_Z && action == GLFW_PRESS){m_window->relax_cilinder_pos();}
    }

    void relax_cilinder_pos() {
        _cilinder.ModelViewIdentity();
    }

protected:
    void InitializeComponents() {
        _cilinder_x_angle = 0;
        _cilinder_y_angle = 0;
        _cilinder_scale = 1;
        this->_cam.ProjectionRotate(-theta, 1, 0, 0);
        this->_cam.ProjectionRotate(phi, 0, 1, 0);
        _static_cilinder.ModelViewTranslate(0.5, 0.90, 0.65);
        _static_cilinder.ModelViewScale(0.5, 0.5, 0.5);
        this->AddObject(_cilinder);
        this->AddObject(_static_cilinder);
        this->AddKeyCallback(Lab3Window::KeyCallback);
    }
};

class Lab2WindowInitParams : public GLGraphics::WindowInitParams {
public:
    Lab2WindowInitParams() = default;

    Lab2WindowInitParams(const std::string &title, const GLGraphics::Vector2i &size) : GLGraphics::WindowInitParams(
            title, size) {}

    void GLinit() const noexcept {
        glEnable(GL_DEPTH_TEST);
        glClearColor(1, 1, 1, 1);
    }
};

int main() {
    Lab2WindowInitParams initialParams("ConycalCilinder", GLGraphics::Vector2i(1000, 1000));
    Lab3Window window(initialParams);
    window.Run();
    return EXIT_SUCCESS;
}