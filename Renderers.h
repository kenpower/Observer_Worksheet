#pragma once
#include <SFML/Graphics.hpp>

#include<map>
#include"pos.h"
using namespace std;

class CollectableRenderer {

    map<string, sf::Color> colorMap = {
        {"extra life", sf::Color::Green},
        {"health", sf::Color::Magenta},
        {"coin", sf::Color(255, 215, 0)},
        {"ammo", sf::Color::Red},
        {"key", sf::Color::Yellow},
        {"powerup", sf::Color::Cyan},
        {"weapon", sf::Color::Blue}
    };
    sf::Font font;
    Size size = { 20, 20 };

public:
    CollectableRenderer() {
        string fontfile = "C:\\Windows\\Fonts\\arial.ttf";
        if (!font.loadFromFile(fontfile.c_str())) {
            throw new exception((string("font file not found") + fontfile).c_str());
        }
    }

    void draw(sf::RenderTarget& window, string name, Pos pos) {
		sf::RectangleShape rectangle(sf::Vector2f((float)size.x, (float)size.y));
        rectangle.setFillColor(colorMap[name]);
        rectangle.setPosition(pos.x - size.x / 2, pos.y - size.y / 2);
        sf::Text text(name.c_str(), font, size.x / 2);
        text.setPosition(pos.x - text.getLocalBounds().width / 2, pos.y + size.y / 2);
        window.draw(rectangle);
        window.draw(text);

    }
};

class PlayerRenderer {
public:
    void draw(sf::RenderTarget& window, Pos p, float radius) {
        sf::CircleShape circle(radius);
        circle.setFillColor(sf::Color::White);
        circle.setOutlineThickness(5);
        circle.setOutlineColor(sf::Color::Green);
        circle.setPosition(p.x - radius, p.y - radius); // Set position on the window
        window.draw(circle);
    }
};

