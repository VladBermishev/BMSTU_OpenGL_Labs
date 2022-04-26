#include <cstdlib>
#include "GLLib/GLLib.h"
template<typename WinInitParams>
class Lab3Window : public GLGraphics::Window<WinInitParams> {
    GLGraphics::Label _label1;
public:
    explicit Lab3Window(const WinInitParams &params) : GLGraphics::Window<WinInitParams>(params){
        InitializeComponents();
    }

    explicit Lab3Window(WinInitParams &&params) : GLGraphics::Window<WinInitParams>(params) {
        InitializeComponents();
    }

    inline static void
    KeyCallback(GLFWwindow *window, const int key, const int scancode, const int action, const int mods) {
        auto *m_window = (Lab3Window *) (glfwGetWindowUserPointer(window));
        if (key == GLFW_KEY_A) {
        }
        if (key == GLFW_KEY_D) {
        }
        if (key == GLFW_KEY_W) {
        }
        if (key == GLFW_KEY_S) {
        }
        if (key == GLFW_KEY_X && action == GLFW_PRESS) {
        }
        if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS) {
        }
        if (key == GLFW_KEY_MINUS && action == GLFW_PRESS) {
        }
        if (key == GLFW_KEY_Z && action == GLFW_PRESS){}
    }

protected:
    void InitializeComponents() {
        _label1.text() = "HELLO WORLD!";
        _label1.scale() = 1;
        _label1.pos() = GLGraphics::Vector2f(0,0);
        _label1.color() = GLGraphics::Vector3f(0.5, 0.8f, 0.2f);
        this->AddObject(_label1);
        this->AddKeyCallback(Lab3Window::KeyCallback);
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
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glClearColor(1, 1, 1, 1);
        GLGraphics::__textRenderer.Init(getSize());
    }
};

int main() {
    Lab4WindowInitParams initialParams("ConycalCilinder", GLGraphics::Vector2ui(1000, 1000));
    Lab3Window window(initialParams);
    window.Run();
    return EXIT_SUCCESS;
}
//заполнения многоугольника по ребрам, постфильтрация с взвешенным усреднением области 3x3, целочисленный алгоритм Брезенхема