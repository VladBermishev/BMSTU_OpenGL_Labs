#include "../GLLib/include/GLLib/GLLib.h"
template<typename WinInitParams>
class Lab1Window : public GLGraphics::Window<WinInitParams> {
    GLGraphics::Circle _circle;
public:
    explicit Lab1Window(const WinInitParams& params) : GLGraphics::Window<WinInitParams>(params) {
        InitializeComponents();
    }

    explicit Lab1Window(WinInitParams&& params) : GLGraphics::Window<WinInitParams>(params) {
        InitializeComponents();
    }

    inline static void KeyCallback(GLFWwindow *window, const int key, const int scancode, const int action, const int mods) {
        auto *m_window = (Lab1Window *) (glfwGetWindowUserPointer(window));
        if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) { m_window->_circle.SetColor(1, 1, 0); }
        if (key == GLFW_KEY_W && action == GLFW_PRESS) { m_window->_circle.ModelViewTranslate(0.f, 0.05f,0.f); }
        if (key == GLFW_KEY_W && action == GLFW_RELEASE) { m_window->_circle.ModelViewTranslate(0.f, -0.05f,0); }
        if (key == GLFW_KEY_A && action == GLFW_PRESS) { m_window->_circle.ModelViewTranslate(-0.05f, 0.0f,0); }
        if (key == GLFW_KEY_A && action == GLFW_RELEASE) { m_window->_circle.ModelViewTranslate(0.05f, 0.0f,0); }
        if (key == GLFW_KEY_S && action == GLFW_PRESS) { m_window->_circle.ModelViewTranslate(0.f, -0.05f,0); }
        if (key == GLFW_KEY_S && action == GLFW_RELEASE) { m_window->_circle.ModelViewTranslate(0.f, 0.05f,0); }
        if (key == GLFW_KEY_D && action == GLFW_PRESS) { m_window->_circle.ModelViewTranslate(0.05f, 0.f,0); }
        if (key == GLFW_KEY_D && action == GLFW_RELEASE) { m_window->_circle.ModelViewTranslate(-0.05f, 0.f,0); }
    }

protected:
    void InitializeComponents() {
        _circle.SetColor(1,0,0);
        this->AddObject(_circle);
        this->AddKeyCallback(Lab1Window::KeyCallback);
    }
};
class Lab1WindowInitParams : public GLGraphics::WindowInitParams {
public:
    Lab1WindowInitParams() = default;

    Lab1WindowInitParams(const std::string &title, const GLGraphics::Vector2ui &size) : GLGraphics::WindowInitParams(
            title, size) {}

    void GLinit() const noexcept {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            //LOG SMTH
            exit(-1);
        }
        glEnable(GL_DEPTH_TEST);
        glClearColor(1, 1, 1, 1);
    }
};


int main(int argc, char** argv){
    Lab1Window window(Lab1WindowInitParams("Circle",GLGraphics::Vector2ui(1000,1000)));
    window.Run();
    return EXIT_SUCCESS;
}
