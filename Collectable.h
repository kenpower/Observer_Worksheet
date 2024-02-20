#pragma once

#include"Boundary.h"

class Collectable : public Bounded {
public:
    std::string name;
    Pos pos;
    Size size;
    bool used = false;

    Boundary getBounds() { return Boundary::fromCenterSize(pos, size); };
    Collectable(const std::string& n, const Pos& p, const Size& s)
        : name(n), pos(p), size(s) {}

    // Overload the < operator for Collectable
    bool operator<(const Collectable& other) const {
        return name < other.name; // Compare based on id, for example
    }
};
