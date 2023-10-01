#pragma once
#include"Card.h"
#include<stack>
#include"Helping.h"
using namespace std;

class FreeCell
{
	stack<Card*> Cs;
	int size;
	Suit S;
	int ri, ci;
	sf::Texture CoinTex;
	sf::Texture FrameTex;
	sf::Sprite Coin;
	sf::Sprite Frame;
	sf::RectangleShape Rec;
public:
	FreeCell(Suit _S,int r, int c);
	FreeCell(const FreeCell& FC);
	bool isComplete();
	bool isEmpty();
	bool canAppend(Card* C);
	void append(Card* C);
	void draw(sf::RenderWindow& window);
	bool isClicked(int r, int c);
	vector<Card*> split();
	sf::Vector2f getPostion();
};

