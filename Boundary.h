#pragma once

#include<algorithm>
#include"pos.h"
class Boundary {
    float left=0, right=0, top=0, bottom=0;
    bool overlap(float aStart, float aEnd, float bStart, float bEnd) const {
        return std::max(aStart, bStart) <= std::min(aEnd, bEnd);
    }
public:
    Boundary() {}
    Boundary(float l, float r, float t, float b) :left(l), right(r), top(t), bottom(b) {}

    bool contains(Pos p);

    bool intersects(const Boundary& other) const {
        bool a = overlap(left, right, other.left, other.right) && overlap(top, bottom, other.top, other.bottom);
        return a;
    }
    static Boundary fromCenterSize(Pos centre, Size size) {
        return Boundary{ centre.x - size.x / 2, centre.x + size.x / 2 ,centre.y - size.y / 2 ,centre.y + size.y / 2 };
    }
};

bool Boundary::contains(Pos p) {
    if (p.x > left and p.x < right and p.y > top and p.y < bottom)
        return true;
    return false;
}

class Bounded {
public:
    virtual Boundary getBounds() = 0;
};
