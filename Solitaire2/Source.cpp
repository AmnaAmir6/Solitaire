#include <SFML/Graphics.hpp>
#include <iostream>
#include"Solitaire.h"
using namespace std;
using namespace sf;

int main()
{
    char ch = 'S';
    RenderWindow window(sf::VideoMode(1360, 700), "Solitaire", sf::Style::Close | sf::Style::Resize);
    window.setPosition(sf::Vector2i(-10, 0));
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Error loading font." << std::endl;
        return 1;
    }

    sf::Text newGameText("New Game", font, 50);
    newGameText.setPosition(100, 50);
    sf::Text loadGameText("Load Game", font, 50);
    loadGameText.setPosition(100, 150);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (ch == 'S')
        {
            Solitaire C(3);
            C.Play(window);
        }
        window.clear();
        window.display();
    }
    return 0;
}