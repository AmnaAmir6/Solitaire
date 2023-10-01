#include "Solitaire.h"
#include<iostream>
using namespace sf;

Solitaire::Solitaire(int _NOC)
{
    this->NOC = _NOC;
    this->time = 0;
    this->moves = 0;
    B = new Board(NOC);
}

void Solitaire::doUndo()
{
    if(!Undo.empty())
    {
        moves += 1;
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
    B->displayWin(window);
}


void Solitaire::Play(sf::RenderWindow& window,sf::Sound& GameSound)
{
    GameSound.setVolume(20);
    GameSound.setLoop(true);
    //---------Card Sound
    sf::SoundBuffer BufferCard;
    if (!BufferCard.loadFromFile("CardSound2.wav"))
        cout << "not sound";
    sf::Sound CardSound(BufferCard);

    //---------Card Shuffling Sound
    sf::SoundBuffer BufferShuffle;
    if (!BufferShuffle.loadFromFile("CardShuffle.wav"))
        cout << "not sound";
    sf::Sound ShuffleCard(BufferShuffle);

    //---------Free Pile Sound
    sf::SoundBuffer Buffer;
    if (!Buffer.loadFromFile("FreePileSound.wav"))
        cout << "not sound";
    sf::Sound FreePileSound(Buffer);

    //---------Click Sound
    sf::SoundBuffer ClickBuffer;
    if (!ClickBuffer.loadFromFile("click.wav"))
        cout << "not sound";
    sf::Sound ClickSound(ClickBuffer);

    //---------Deck Click Sound
    sf::SoundBuffer DeckBuffer;
    if (!DeckBuffer.loadFromFile("DeckSound3.wav"))
        cout << "not sound";
    sf::Sound DeckSound(DeckBuffer);

    //---------Game Win Sound
    sf::SoundBuffer WinBuffer;
    if (!WinBuffer.loadFromFile("GameWin.wav"))
        cout << "not sound";
    sf::Sound WinSound(WinBuffer);

    bool isPlayed = false;
    bool CardSelected = false;
    bool isFirst = true;
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
                            B->MovetoDc(window,CardSound, FreePileSound,isPlayed,moves);
                            if (isPlayed)
                            {
                                Undo.push_back(*B);
                                isPlayed = false;
                            }
                        }
                        else
                            B->MovetoSc();
                        CardSelected = false;
                    }
                    else if (B->isUndoClicked(mousePos2.x, mousePos2.y))
                    {
                        ClickSound.play();
                        doUndo();
                    }
                    else if (B->isRedoClicked(mousePos2.x, mousePos2.y))
                    {
                        ClickSound.play();
                        doRedo();
                    }
                    else
                    {
                        if (B->isDeckClicked(mousePos2.x, mousePos2.y))
                        {
                            moves += 1;
                            DeckSound.play();
                            B->RevealDeck();
                        }
                    }
                }
            }
            if (CardSelected)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                B->move(mousePosition.y, mousePosition.x);
            }
        }
        B->setMoves(moves);
        j++;
        if (j == 350)
        {
            time += 1;
            j = 0;
        }
        window.clear();
        if (isFirst)
        {
            B->draw(window, ShuffleCard);
            isFirst = false;
        }
        else
            B->draw(window);
        
        B->setTime(time);
        if (B->isWin())
        {
            WinSound.play();
            displayWin(window);
            window.close();
        }
        window.display();
    }
}


