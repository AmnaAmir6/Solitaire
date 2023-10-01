#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include"Solitaire.h"
using namespace std;
using namespace sf;

void animateSolitaire(sf::RenderWindow& window, sf::Sound& Back)
{
    sf::Font font;
    font.loadFromFile("font.otf");
    
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("grd1.png");
    sf::Sprite background(backgroundTexture);

    sf::Text text("Solitaire", font, 200);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(3);

    sf::Vector2f initialPosition(window.getSize().x / 2, window.getSize().y / 2);
    text.setPosition(initialPosition);
    text.setScale(0.0f, 0.0f);

    sf::Color textColor = text.getFillColor();
    sf::Clock clock;
    Back.play();
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        float elapsed = clock.getElapsedTime().asSeconds();

        if (elapsed <= 3.0f)
        { 
            float scale = elapsed / 3.0f;
            text.setScale(scale, scale);

            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
            text.setPosition(window.getSize().x / 2, window.getSize().y / 2);
        }

        window.draw(background);
        window.draw(text);
        window.display();

        if (elapsed >= 3.0f)
        {
            break;
        }
    }
    sf::sleep(sf::seconds(1));
}

int LevelSelection(sf::RenderWindow& window,sf::Sound& ClickSound,sf::Sound& Back) 
{
    sf::Color Magenda(sf::Color(224, 20, 44));
    sf::Color LightBlue(sf::Color(47, 79, 104));

    sf::Texture texture;
    if (!texture.loadFromFile("backgrd2.png"))
    {
        std::cout << "Error loading image." << std::endl;
        return -1;
    }

    sf::Sprite img;
    img.setTexture(texture);
    img.setScale(1, 1);
    img.setPosition(0, 0);

    sf::Font font;
    if (!font.loadFromFile("Molot.otf")) 
    {
        std::cerr << "Error loading font." << std::endl;
        return 1;
    }

    sf::Text easyText("Easy", font, 80);
    easyText.setPosition(150, 120);
    easyText.setOutlineThickness(5);

    sf::Text mediumText("Medium", font, 80);
    mediumText.setPosition(150, 300);
    mediumText.setOutlineThickness(5);


    sf::Text hardText("Hard", font, 80);
    hardText.setPosition(150, 480);
    hardText.setOutlineThickness(5);



    sf::Color defaultColor = sf::Color(208, 177, 122);
    sf::Color hoverColor = LightBlue;

    int selectedLevel = 0;
    Back.play();
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) 
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (easyText.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                {
                    ClickSound.play();
                    selectedLevel = 1;
                }
                else if (mediumText.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                {
                    ClickSound.play();
                    selectedLevel = 2;
                }
                else if (hardText.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                {
                    ClickSound.play();
                    selectedLevel = 3;
                }
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (easyText.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            easyText.setFillColor(hoverColor);
            easyText.setOutlineColor(Magenda);
        }
        else
        {
            easyText.setFillColor(defaultColor);
            easyText.setOutlineColor(sf::Color::Transparent);

        }

        if (mediumText.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            mediumText.setFillColor(hoverColor);
            mediumText.setOutlineColor(Magenda);

        }
        else
        {
            mediumText.setFillColor(defaultColor);
            mediumText.setOutlineColor(sf::Color::Transparent);

        }

        if (hardText.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            hardText.setFillColor(hoverColor);
            hardText.setOutlineColor(Magenda);

        }
        else 
        {
            hardText.setFillColor(defaultColor);
            hardText.setOutlineColor(sf::Color::Transparent);

        }

        window.draw(img);
        window.draw(easyText);
        window.draw(mediumText);
        window.draw(hardText);

        window.display();

        if (selectedLevel != 0) 
        {
            window.clear();

            return selectedLevel;
            break;
        }
    }
}

int main()
{
    RenderWindow window(sf::VideoMode(1360, 700), "Solitaire", sf::Style::Close | sf::Style::Resize);
    window.setPosition(sf::Vector2i(-6, 0));

    //---------Card Sound
    sf::SoundBuffer Buffer;
    if (!Buffer.loadFromFile("LevelClick.wav"))
        cout << "not sound";
    sf::Sound ClickSound(Buffer);

    //---------Game Sound
    sf::SoundBuffer GameBuffer;
    if (!GameBuffer.loadFromFile("GAmeSound.wav"))
        cout << "not sound";
    sf::Sound GameSound(GameBuffer);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        animateSolitaire(window, GameSound);
        int level = LevelSelection(window,ClickSound, GameSound);
        window.clear();
        Solitaire C(level);
        C.Play(window,GameSound);
        window.display();
    }

    return 0;
}

int main1()
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

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (ch == 'S')
        {
            Solitaire C(3);
           // C.Play(window);
        }
        window.clear();
        window.display();
    }
    return 0;
}