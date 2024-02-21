#pragma once

#include "Boundary.h"
class Player : public Bounded {
    Pos pos{ 0,0 };
    Size size{ 1,1 };
    float speed = 1.5;
    Boundary areaToStayInside;

public:
    Boundary getBounds() { return Boundary::fromCenterSize(pos, size); }

    Player() {}
    Player(Boundary b, Pos p, Size s) :areaToStayInside(b), pos(p), size(s) {}

    void move(Size dir) {
        Pos newPos = { pos.x + dir.x * speed, pos.y + dir.y * speed };
        if (areaToStayInside.contains(newPos)) {
            pos = newPos;
        }
    }

    Pos getPos() { return pos; }

    float radius() { return (size.x) / 2.0f; }


};




