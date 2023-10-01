#pragma once
#include"Card.h"
#include"MyStack.h"
#include"Board.h"
#include"Deck.h"
#include<stack>
using namespace std;

class Board;
class Pile
{
private:
	int size;
	MyStack S;
	int ti;
	int RevealCards;
	int ri, ci;
	bool topCardSelected;
	bool isFirst;
	sf::RectangleShape Rec;
	
public:
	Pile(int size, Deck* D, int ri, int ci);
	Pile(const Pile& P);
	void append(vector<Card*> Cs);
	bool canAppend(vector<Card*> Cs);
	vector<Card*> split(int i);
	bool isEmpty();
	void selectTopCard(int i);
	void deselectTopCard();
	bool isCardSelected(int r, int c);
	void draw(sf::RenderWindow& window, Pile** Ps, sf::Sprite bg, Board* B);
	Card* getCardAt(int i) const;
	int getSize();
	sf::Vector2f getPos();
	void revealNext();
	int getRevealCards();
};

