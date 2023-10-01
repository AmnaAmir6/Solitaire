#pragma once
#include<vector>
#include"Card.h"
using namespace std;

class Deck
{
private:
	vector<Card*> Cards;
	int size;
public:
	Deck();
	Deck(const Deck& D);
	void shuffle();
	Card* getCard();
	bool Empty();
};

