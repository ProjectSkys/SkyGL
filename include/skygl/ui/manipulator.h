#pragma once

#include <skygl/basic/common.h>
#include <skygl/basic/utils.h>
#include <skygl/ui/key.h>

NS_SKY_GL_BEG

class KeyManipulator {
private:
    std::map<int, bool> _pressed;
public:
    bool operator[](int code) {
        return _pressed[code];
    }
    void onKeyPressed(Key key) {
        _pressed[key] = true;
    }
    void onKeyReleased(Key key) {
        _pressed[key] = false;
    }
};

class MouseManipulator {
private:
    double _posX = -1, _posY = -1;
    double _lastX = -1, _lastY = -1;
    double _scrollX = 0, _scrollY = 0;
public:
    double getPosX() {
        return _posX;
    }
    double getPosY() {
        return _posY;
    }
    double getDeltaX() {
        if (_lastX == _posX) return 0;
        if (_lastX == -1)_lastX = _posX;
        double deltaX = _posX - _lastX;
        _lastX = _posX;
        return deltaX;
    }
    double getDeltaY() {
        if (_lastY == _posY) return 0;
        if (_lastY == -1)_lastY = _posY;
        double DeltaY = _posY - _lastY;
        _lastY = _posY;
        return DeltaY;
    }
    double getScrollX() {
        double ret = _scrollX;
        _scrollX = 0;
        return ret;
    }
    double getScrollY() {
        double ret = _scrollY;
        _scrollY = 0;
        return ret;
    }
    void onMouseMoved(double xpos, double ypos) {
        _posX = xpos;
        _posY = ypos;
    }
    void onMouseScrolled(double xoff, double yoff) {
        _scrollX = xoff;
        _scrollY = yoff;
    }
};

NS_SKY_GL_END
