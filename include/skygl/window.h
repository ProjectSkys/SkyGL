#pragma once

#include <skygl/common.h>
#include <skygl/types.h>
#include <skygl/error.h>
#include <skygl/gl.h>

#include <functional>
#include <memory>
#include <map>

#include <boost/signals2.hpp>

NS_SKY_GL_BEG

class Key {
public:
    int id;
    int code;
    int action;
    int mode;
public:
    Key(int id, int code, int action, int mode)
        : id(id), code(code), action(action) , mode(mode) {}
    operator int() const {
        return id;
    }
};

class Window {
private:
    template <class Slot>
    using Signal = boost::signals2::signal<Slot>;
public:
    using CreatedSignal = Signal<void()>;

    using MoveSignal = Signal<void(int, int)>;
    using ResizeSignal = Signal<void(int, int)>;
    using CloseSignal = Signal<void()>;
    using RefreshSignal = Signal<void()>;
    using FocusSignal = Signal<void()>;
    using IconifySignal = Signal<void()>;

    using KeyboardSignal = Signal<void(Key)>;

private:
    GLFWwindow* _window;
    UInt _width, _height;
    String _title;
public:
    CreatedSignal created;

    MoveSignal moved;
    ResizeSignal resized;
    CloseSignal on_close;
    RefreshSignal on_refresh;
    FocusSignal focused;
    FocusSignal unfocused;
    IconifySignal iconified;
    IconifySignal restored;
    ResizeSignal bf_resized;

    KeyboardSignal keypressed;
    KeyboardSignal keyrepeated;
    KeyboardSignal keyreleased;

public:
    Window(UInt width = 800, UInt height = 600, KStringRef title = "SkyGL")
        : _width(width)
        , _height(height)
        , _title(title) {}
    UInt getWidth() const {
        return _width;
    }
    void setWidth(UInt width) {
        _width = width;
        glfwSetWindowSize(_window, _width, _height);
    }
    UInt getHeight() const {
        return _height;
    }
    void setHeight(UInt height) {
        _height = height;
        glfwSetWindowSize(_window, _width, _height);
    }
    String getTitle() const {
        return _title;
    }
    void setTitle(KStringRef title) {
        _title = title;
        glfwSetWindowTitle(_window, _title.c_str());
    }
    GLFWwindow* getRawWindow() const {
        return _window;
    }
    void create() {
        _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
        if (_window == nullptr) {
            throw GLException("Window::create", "Failed to create GLFW window");
        }
        current();
        _raw2window[_window] = this;
        glfwSetWindowPosCallback(_window, _pos_callback);
        glfwSetWindowSizeCallback(_window, _size_callback);
        glfwSetWindowCloseCallback(_window, _close_callback);
        glfwSetWindowRefreshCallback(_window, _refresh_callback);
        glfwSetWindowFocusCallback(_window, _focus_callback);
        glfwSetWindowIconifyCallback(_window, _iconify_callback);
        glfwSetFramebufferSizeCallback(_window, _bf_size_callback);
        glfwSetKeyCallback(_window, _key_callback);
        created();
    }
    void current() {
        glfwMakeContextCurrent(_window);
    }
    void close() {
        glfwSetWindowShouldClose(_window, GL_TRUE);
    }
    void destroy() {
        glfwDestroyWindow(_window);
    }
    bool running() {
        return !glfwWindowShouldClose(_window);
    }
    void swapBuffers() {
        glfwSwapBuffers(_window);
    }
    void iconify() {
        glfwIconifyWindow(_window);
    }
    void restore() {
        glfwRestoreWindow(_window);
    }
    void loop(std::function<void()> func) {
        while (running()) {
            func();
            swapBuffers();
        }
        destroy();
    }
    static void resetHints() {
        glfwDefaultWindowHints();
    }
    static void hint(int hint, int value) {
        glfwWindowHint(hint, value);
    }
private:
    static std::map<GLFWwindow*, Window*> _raw2window;
    static void _pos_callback(GLFWwindow* raw, int xpos, int ypos) {
        Window* window = _raw2window[raw];
        window->moved(xpos, ypos);
    }
    static void _size_callback(GLFWwindow* raw, int width, int height) {
        Window* window = _raw2window[raw];
        window->_width = width;
        window->_height = height;
        window->resized(width, height);
    }
    static void _close_callback(GLFWwindow* raw) {
        Window* window = _raw2window[raw];
        window->on_close();
    }
    static void _refresh_callback(GLFWwindow* raw) {
        Window* window = _raw2window[raw];
        window->on_refresh();
    }
    static void _focus_callback(GLFWwindow* raw, int focus) {
        Window* window = _raw2window[raw];
        if (focus == GL_TRUE) {
            window->focused();
        } else {
            window->unfocused();
        }
    }
    static void _iconify_callback(GLFWwindow* raw, int iconify) {
        Window* window = _raw2window[raw];
        if (iconify == GL_TRUE) {
            window->iconified();
        } else {
            window->restored();
        }
    }
    static void _bf_size_callback(GLFWwindow* raw, int width, int height) {
        Window* window = _raw2window[raw];
        window->bf_resized(width, height);
    }
    static void _key_callback(GLFWwindow* raw, int key, int scancode, int action, int mode) {
        Window* window = _raw2window[raw];
        Key k(key, scancode, action, mode);
        switch (action) {
            case GLFW_PRESS:
                window->keypressed(k);
                break;
            case GLFW_RELEASE:
                window->keyreleased(k);
                break;
            case GLFW_REPEAT:
                window->keyrepeated(k);
                break;
            default:
                break;
        }
    }
};

NS_SKY_GL_END
