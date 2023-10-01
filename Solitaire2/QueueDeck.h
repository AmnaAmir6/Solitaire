#pragma once
#include"Card.h"
#include"Deck.h"
#include<vector>
#include<queue>
using namespace std;

class QueueDeck
{
	vector<Card*> Show;
	queue<Card*> Hide;
	queue<Card*> Help;
	int NOC;
	int size;
	int ri, ci;
	sf::Texture FrameTex;
	sf::Sprite Frame;
	sf::RectangleShape Rec;
	bool isCard;
public:
	QueueDeck(int NOC, Deck* D);
	QueueDeck(const QueueDeck& QD);
	void append(Card* c);
	void draw(sf::RenderWindow& window);
	Card* removeCard();
	void showNext(int& score);
	void showNextTop(int& score);
	bool isDClicked(int r, int c);
	bool isCardSelected(int r, int c);
	bool IsCard();
	void setIsCard(bool c);
};

