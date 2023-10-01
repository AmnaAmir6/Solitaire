#include "Solitaire.h"
#include<iostream>
using namespace sf;

Solitaire::Solitaire(int _NOC)
{
    this->NOC = _NOC;
    this->time = 0;
    B = new Board(NOC);
}

void Solitaire::doUndo()
{
    if(!Undo.empty())
    {
        Redo.push_back(*B);
        this->B = new Board(Undo.back());
        Undo.pop_back();
    }
}

void Solitaire::doRedo()
{
    if (!Redo.empty())
    {
        this->B = new Board(Redo.back());
        Redo.pop_back();
    }
}

void Solitaire::displayWin(sf::RenderWindow& window)
{

}


void Solitaire::Play(sf::RenderWindow& window)
{
    bool CardSelected = false;
    Undo.push_back(*B);
    int j = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if(!CardSelected)
                    {
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                        B->isValidSc(mousePosition.x, mousePosition.y, CardSelected);
                    }
                }
            }
            Board T(*B);
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos2 = sf::Mouse::getPosition(window);

                    if(CardSelected)
                    {
                        if (B->isValidDes(mousePos2.x, mousePos2.y))
                        {
                            B->MovetoDc(window);
                            Undo.push_back(*B);
                        }
                        else
                            B->MovetoSc();
                        CardSelected = false;
                    }
                    else if (B->isUndoClicked(mousePos2.x, mousePos2.y))
                    {
                        doUndo();
                    }
                    else if (B->isRedoClicked(mousePos2.x, mousePos2.y))
                    {
                        doRedo();
                    }
                    else
                    {
                        if (B->isDeckClicked(mousePos2.x, mousePos2.y))
                            B->RevealDeck();
                    }
                }
            }
            if (CardSelected)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                B->move(mousePosition.y, mousePosition.x);
            }
        }
        j++;
        if (j == 350)
        {
            time += 1;
            j = 0;
        }
        window.clear();
        B->draw(window);
        
        B->setTime(time);
        if (B->isWin())
        {
            displayWin(window);
            window.close();
        }
        window.display();
    }
}


