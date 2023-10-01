#pragma once
#include"Helping.h"
#include"Deck.h"
#include"Board.h"
#include"QueueDeck.h"
class Solitaire
{
private:
	int NOC;
	int time;
	Board* B;
	vector<Board> Undo;
	vector<Board> Redo;
public:
	Solitaire(int _NOC);
	void Play(sf::RenderWindow& window);
	void doUndo();
	void doRedo();
	void displayWin(sf::RenderWindow& window);

};

