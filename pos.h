#pragma once
struct Pos {
    float x, y;
    
    Pos(float x, float y) :x(x), y(y) {}
    Pos(int x, int y) :x((float)x), y((float)y) {} // just to stop conversion warnings

};

struct Size {
    int x, y;
};

typedef Pos Vel;