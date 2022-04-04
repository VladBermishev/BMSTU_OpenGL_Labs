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

int main(int argc, char** argv){
    GLGraphics::WindowInitParams initialParams("Circle",GLGraphics::Vector2i(1000,1000));
    Lab1Window window(initialParams);
    window.Run();
    return EXIT_SUCCESS;
}
