#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
//#pragma comment(lib,"thor-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
//#pragma comment(lib,"thor.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
//#pragma comment(lib,"libyaml-cppmdd") 

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include"pos.h"
#include"Boundary.h"
#include"Collectable.h"
#include"Renderers.h"
#include"Player.h"

using namespace std;

class Inventory {
    std::map<Collectable, int> items;

public:
    void add(Collectable c) {

        if (c.name == "coin") return;

        auto it = items.find(c);

        if (it != items.end()) {
            it->second++; // If found, increment the count
        }
        else {
            items[c] = 1; // If not found, insert the item with a count of 1
        }
  
    }

    string toString() {
        string result{ "Inventory: " };
        for (auto& i : items) {
            string plural = i.second > 2 ? "s" : "";
            result += to_string(i.second) + "x" + i.first.name+ plural +" ";
        }

        return result;
    }
};

class SoundSystem {
    sf::SoundBuffer coinb;
    sf::SoundBuffer itemBuffer;

    sf::Sound coin;
    sf::Sound item;

public:
    SoundSystem() {
        if (!coinb.loadFromFile("ding.flac")) {
            std::cout << "Error loading sound file" << std::endl;
            return;
        }
        coin.setBuffer(coinb);
        if (!itemBuffer.loadFromFile("beep.wav")) {
            std::cout << "Error loading sound file" << std::endl;
            return;
        }
        item.setBuffer(itemBuffer);
    }

    void play(const std::string& itemName) {
        std::cout << "Sound System: Playing sound for item - " << itemName << std::endl;

        if (itemName == "coin")
            coin.play();
        else
            item.play();
    }
};

class Achievements {
    //collect n coins
    const int target = 5;
    int coins = 0;

public:
    void collect(Collectable& c) {
        if (c.name == "coin")
            coins++;
    }

    bool complete() { return coins >= target; }

    string toString(){
        return string("") + to_string(coins) + "/" + to_string(target) + " coins collected";
     }
};

class Collectables {

    void removeUsedItems() {
        items.erase(std::remove_if(items.begin(), items.end(),
            [](Collectable c) { return c.used; }), items.end());
    }

public:
    std::vector<Collectable> items;

    void setup(Size size) {
        string names[] = { "health", "extra life", "ammo", "key", "powerup", "weapon" };
        for (int i = 0; i < 10; i++) {
            Pos pos{ rand() % size.x, rand() % size.y };
            string name = names[rand() % 3];
            items.push_back(Collectable{ name, pos, Size{20, 20} });
        }
        for (int i = 0; i < 15; i++) {
            Pos pos{ rand() % size.x, rand() % size.y };

            items.push_back(Collectable{ "coin", pos, Size{20, 20} });
        }
    }

    void checkCollisionWith(Boundary boundary,
        Inventory& i,
        SoundSystem& ss,
        Achievements& a) {
        for (auto& collectable : items) {
            if (collectable.getBounds().intersects(boundary)) {
                i.add(collectable);
                ss.play(collectable.name);
                a.collect(collectable);

                collectable.used = true;
            }
        }

        removeUsedItems();
    }
};

class PlayerController {
public:
    void control(Player& p) {
        int dx = 0, dy = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            dx = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            dx = +1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            dy = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            dy = +1;

        p.move(Size{ dx, dy });
    }
};


class Game {
    int screenWidth = 1200;
    int screenHeight = 800;

    sf::RenderWindow window;
    sf::Font font;

    Player player;
    Collectables collectables;

    Inventory inventory;
    SoundSystem soundSystem;
    Achievements achievments;

    void update() {

        PlayerController pc;
        pc.control(player);

        collectables.checkCollisionWith(player.getBounds(), inventory, soundSystem, achievments);
    }

    void mainScreen() {
        window.clear();

        PlayerRenderer playerRenderer;
        playerRenderer.draw(window, player.getPos(), player.radius());

        CollectableRenderer cr;
        for (auto& c : collectables.items) cr.draw(window, c.name, c.pos);

        sf::Text inventoryText("", font, 16);
        inventoryText.setString(inventory.toString());
        inventoryText.setPosition(0, 0);
        window.draw(inventoryText);

        sf::Text achievmentText("", font, 16);
        achievmentText.setString(achievments.toString());
        achievmentText.setPosition(0, 20);
        window.draw(achievmentText);

        window.display();
    }

    void gameOverScreen() {
        window.clear();

        sf::Text gameOverText("Achievment Unlocked\n    Game Over!", font, 100);
  
        gameOverText.setPosition(screenWidth/2, screenHeight/2);

        sf::FloatRect textRect = gameOverText.getLocalBounds();
        gameOverText.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        gameOverText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
        window.draw(gameOverText);


        window.display();
    }

public:
    Game() : window(sf::VideoMode(screenWidth, screenHeight), "Observer Worksheet") {}

    void setup() {
        const int playerSize = 50;
        const int playerRadius = playerSize / 2;

        Boundary playerBoundary(playerRadius, screenWidth - playerRadius, playerRadius, screenHeight - playerRadius);
        player = Player(playerBoundary, Pos{ (float)screenWidth / 2, (float)screenHeight / 2 }, Size{ playerSize , playerSize });

        string fontfile = "C:\\Windows\\Fonts\\Consola.ttf";
        if (!font.loadFromFile(fontfile.c_str())) {
            throw new exception((string("font file not found") + fontfile).c_str());
        }

        collectables.setup(Size{screenWidth,screenHeight});

    }


    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            if (achievments.complete())
                gameOverScreen();
            else {
                update();
                mainScreen();
            }
        }
    }
};

int main() {

    Game game;
    game.setup();
    game.run();
}
