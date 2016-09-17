#pragma once

#include <skygl/basic/common.h>
#include <skygl/basic/utils.h>
#include <skygl/ui/key.h>

#include <map>

NS_SKY_GL_BEG

class KeyManipulator {
public:
    std::map<int, bool> pressed;
    std::map<int, bool> toggled;
    std::map<int, int> count;
    int last;
public:
    bool operator[](int code) {
        return pressed[code];
    }
    void onKeyPressed(Key key) {
        pressed[key] = true;
        toggled[key] = !toggled[key];
    }
    void onKeyReleased(Key key) {
        pressed[key] = false;
        count[key]++;
        last = key;
    }
};

class MouseManipulator {
private:
    double _posX = -1, _posY = -1;
    double _lastX = -1, _lastY = -1;
    double _scrollX = -1, _scrollY = -1;
    double _lastSX = -1, _lastSY = -1;
public:
    double getPosX() {
        return _posX;
    }
    double getPosY() {
        return _posY;
    }
    double getDeltaX() {
        if (_lastX == _posX) return 0;
        if (_lastX == -1) _lastX = _posX;
        double deltaX = _posX - _lastX;
        _lastX = _posX;
        return deltaX;
    }
    double getDeltaY() {
        if (_lastY == _posY) return 0;
        if (_lastY == -1) _lastY = _posY;
        double DeltaY = _posY - _lastY;
        _lastY = _posY;
        return DeltaY;
    }
    double getScrollX() {
        if (_lastSX == _scrollX) return 0;
        if (_lastSX == -1) _lastSX = _scrollX;
        double deltaX = _scrollX - _lastSX;
        _lastSX = _scrollX;
        return deltaX;
    }
    double getScrollY() {
        if (_lastSY == _scrollY) return 0;
        if (_lastSY == -1) _lastSY = _scrollY;
        double deltaY = _scrollY - _lastSY;
        _lastSY = _scrollY;
        return deltaY;
    }
    void onMouseMoved(double xpos, double ypos) {
        _posX = xpos;
        _posY = ypos;
    }
    void onMouseScrolled(double xoff, double yoff) {
        _scrollX += xoff;
        _scrollY += yoff;
    }
};

NS_SKY_GL_END
