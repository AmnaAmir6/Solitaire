#pragma once

#include"Helping.h"

class Card
{
protected:
	Suit S;
	Rank R;
	int ri, ci;
	bool faceUp;
	sf::Sprite _card;
	sf::Texture temp;
	sf::Sprite _cardBack;
	sf::Texture temp2;
	sf::RectangleShape Rec;
public:
	Card(Suit _S, Rank _R, bool faceUp = false, int _ri = 0, int _ci = 0);
	Card(const Card& C);
	void Draw(sf::RenderWindow& window,int r=-1,int c=-1);
	Suit getSuit() const;
	Rank getRank() const;
	bool isFaceUp();
	void setFace(bool face);
	sf::Vector2f getPosition();
	void setPosition(int ri, int ci);
	bool isClicked(int r, int c);
	bool isOppositeColor(Suit _S);
};

