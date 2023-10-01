#include "Card.h"
#include"Helping.h"
#include<iostream>
using namespace std;

Card::Card(Suit _S, Rank _R, bool _faceUp, int _ri, int _ci)
{
    this->S = _S;
    this->R = _R;
    this->ri = _ri;
    this->ci = _ci;
    this->faceUp = _faceUp;
    //this->Rec.setSize(sf::Vector2f(126, 175));
    this->Rec.setSize(sf::Vector2f(110, 153));
    Rec.setPosition(ci - 1, ri - 1);
    sf::Color gold(204, 191, 63);
    Rec.setFillColor(gold);

    if (!temp2.loadFromFile("back5.jpg"))
    {
        throw("Unable to load img");
    }
    _cardBack.setTexture(temp2);
    _cardBack.setScale(0.35, 0.35);
    _cardBack.setPosition(ci, ri);

    if (S == SPADES)
    {
        switch (R)
        {
        case ACE:
            if (!temp.loadFromFile("1s.png"))
            {
                throw("Unable to load img");
            }
            break;
        case TWO:
            if (!temp.loadFromFile("2s.png"))
            {
                throw("Unable to load img");
            }
            break;
        case THREE:
            if (!temp.loadFromFile("3s.png"))
            {
                throw("Unable to load img");
            }
            break;
        case FOUR:
            if (!temp.loadFromFile("4s.png"))
            {
                throw("Unable to load img");
            }
            break;
        case FIVE:
            if (!temp.loadFromFile("5s.png"))
            {
                throw("Unable to load img");
            }
            break;
        case SIX:
            if (!temp.loadFromFile("6s.png"))
            {
                throw("Unable to load img");
            }
            break;
        case SEVEN:
            if (!temp.loadFromFile("7s.png"))
            {
                throw("Unable to load img");
            }
            break;
        case EIGHT:
            if (!temp.loadFromFile("8s.png"))
            {
                throw("Unable to load img");
            }
            break;
        case NINE:
            if (!temp.loadFromFile("9s.png"))
            {
                throw("Unable to load img");
            }
            break;
        case TEN:
            if (!temp.loadFromFile("10s.png"))
            {
                throw("Unable to load img");
            }
            break;
        case JACK:
            if (!temp.loadFromFile("11s.png"))
            {
                throw("Unable to load img");
            }
            break;
        case QUEEN:
            if (!temp.loadFromFile("12s.png"))
            {
                throw("Unable to load img");
            }
            break;
        case KING:
            if (!temp.loadFromFile("13s.png"))
            {
                throw("Unable to load img");
            }
            break;
        }
    }
    else if (S == HEARTS)
    {
        switch (R)
        {
        case ACE:
            if (!temp.loadFromFile("1h.png"))
            {
                throw("Unable to load img");
            }
            break;
        case TWO:
            if (!temp.loadFromFile("2h.png"))
            {
                throw("Unable to load img");
            }
            break;
        case THREE:
            if (!temp.loadFromFile("3h.png"))
            {
                throw("Unable to load img");
            }
            break;
        case FOUR:
            if (!temp.loadFromFile("4h.png"))
            {
                throw("Unable to load img");
            }
            break;
        case FIVE:
            if (!temp.loadFromFile("5h.png"))
            {
                throw("Unable to load img");
            }
            break;
        case SIX:
            if (!temp.loadFromFile("6h.png"))
            {
                throw("Unable to load img");
            }
            break;
        case SEVEN:
            if (!temp.loadFromFile("7h.png"))
            {
                throw("Unable to load img");
            }
            break;
        case EIGHT:
            if (!temp.loadFromFile("8h.png"))
            {
                throw("Unable to load img");
            }
            break;
        case NINE:
            if (!temp.loadFromFile("9h.png"))
            {
                throw("Unable to load img");
            }
            break;
        case TEN:
            if (!temp.loadFromFile("10h.png"))
            {
                throw("Unable to load img");
            }
            break;
        case JACK:
            if (!temp.loadFromFile("11h.png"))
            {
                throw("Unable to load img");
            }
            break;
        case QUEEN:
            if (!temp.loadFromFile("12h.png"))
            {
                throw("Unable to load img");
            }
            break;
        case KING:
            if (!temp.loadFromFile("13h.png"))
            {
                throw("Unable to load img");
            }
            break;
        }
    }
    else   if (S == DIAMONDS)
    {
        switch (R)
        {
        case ACE:
            if (!temp.loadFromFile("1d.png"))
            {
                throw("Unable to load img");
            }
            break;
        case TWO:
            if (!temp.loadFromFile("2d.png"))
            {
                throw("Unable to load img");
            }
            break;
        case THREE:
            if (!temp.loadFromFile("3d.png"))
            {
                throw("Unable to load img");
            }
            break;
        case FOUR:
            if (!temp.loadFromFile("4d.png"))
            {
                throw("Unable to load img");
            }
            break;
        case FIVE:
            if (!temp.loadFromFile("5d.png"))
            {
                throw("Unable to load img");
            }
            break;
        case SIX:
            if (!temp.loadFromFile("6d.png"))
            {
                throw("Unable to load img");
            }
            break;
        case SEVEN:
            if (!temp.loadFromFile("7d.png"))
            {
                throw("Unable to load img");
            }
            break;
        case EIGHT:
            if (!temp.loadFromFile("8d.png"))
            {
                throw("Unable to load img");
            }
            break;
        case NINE:
            if (!temp.loadFromFile("9d.png"))
            {
                throw("Unable to load img");
            }
            break;
        case TEN:
            if (!temp.loadFromFile("10d.png"))
            {
                throw("Unable to load img");
            }
            break;
        case JACK:
            if (!temp.loadFromFile("11d.png"))
            {
                throw("Unable to load img");
            }
            break;
        case QUEEN:
            if (!temp.loadFromFile("12d.png"))
            {
                throw("Unable to load img");
            }
            break;
        case KING:
            if (!temp.loadFromFile("13d.png"))
            {
                throw("Unable to load img");
            }
            break;
        }
    }
    else
    {
        switch (R)
        {
        case ACE:
            if (!temp.loadFromFile("1c.png"))
            {
                throw("Unable to load img");
            }
            break;
        case TWO:
            if (!temp.loadFromFile("2c.png"))
            {
                throw("Unable to load img");
            }
            break;
        case THREE:
            if (!temp.loadFromFile("3c.png"))
            {
                throw("Unable to load img");
            }
            break;
        case FOUR:
            if (!temp.loadFromFile("4c.png"))
            {
                throw("Unable to load img");
            }
            break;
        case FIVE:
            if (!temp.loadFromFile("5c.png"))
            {
                throw("Unable to load img");
            }
            break;
        case SIX:
            if (!temp.loadFromFile("6c.png"))
            {
                throw("Unable to load img");
            }
            break;
        case SEVEN:
            if (!temp.loadFromFile("7c.png"))
            {
                throw("Unable to load img");
            }
            break;
        case EIGHT:
            if (!temp.loadFromFile("8c.png"))
            {
                throw("Unable to load img");
            }
            break;
        case NINE:
            if (!temp.loadFromFile("9c.png"))
            {
                throw("Unable to load img");
            }
            break;
        case TEN:
            if (!temp.loadFromFile("10c.png"))
            {
                throw("Unable to load img");
            }
            break;
        case JACK:
            if (!temp.loadFromFile("11c.png"))
            {
                throw("Unable to load img");
            }
            break;
        case QUEEN:
            if (!temp.loadFromFile("12c.png"))
            {
                throw("Unable to load img");
            }
            break;
        case KING:
            if (!temp.loadFromFile("13c.png"))
            {
                throw("Unable to load img");
            }
            break;
        }
    }
    _card.setTexture(temp);
    _card.setScale(0.35, 0.35);
    _card.setPosition(ci, ri);
}

Card::Card(const Card& C)
{
    this->S = C.S;
    this->R = C.R;
    this->ri = C.ri;
    this->ci = C.ci;
    this->faceUp = C.faceUp;

    this->_card = sf::Sprite(C._card);
    this->_cardBack = sf::Sprite(C._cardBack);
    this->Rec = sf::RectangleShape(C.Rec);
}

Suit Card::getSuit() const
{
    return S;
}

Rank Card::getRank() const
{
    return R;
}

bool Card::isFaceUp()
{
    return faceUp;
}
void Card::setFace(bool face)
{
    this->faceUp = face;
}
void Card::Draw(sf::RenderWindow& window,int r,int c)
{
    if (r != -1)
        ri = r, ci = c;
    _cardBack.setPosition(ci, ri);
    _card.setPosition(ci, ri);
    Rec.setPosition(ci - 1, ri - 1);

    window.draw(Rec);
    if (faceUp == true)
        window.draw(_card);
    else
        window.draw(_cardBack);
}

sf::Vector2f Card::getPosition()
{
    return sf::Vector2f(ri, ci);
}

bool Card::isClicked(int r, int c)
{
    if (this->_card.getGlobalBounds().contains(r, c))
        return true;
    return false;
}
void Card::setPosition(int r, int c)
{
    this->ri = r;
    this->ci = c;
}

bool Card::isOppositeColor(Suit _S)
{
    if (S == SPADES || S == CLUBS)
    {
        if (_S == DIAMONDS || _S == HEARTS)
            return true;
    }
    else if (S == DIAMONDS || S == HEARTS)
    {
        if (_S == SPADES || _S == CLUBS)
            return true;
    }
    else
        return false;
}

