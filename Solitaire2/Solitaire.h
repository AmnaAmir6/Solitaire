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
	int moves;
	Board* B;
	vector<Board> Undo;
	vector<Board> Redo;
public:
	Solitaire(int _NOC);
	void Play(sf::RenderWindow& window, sf::Sound& GameSound);
	void doUndo();
	void doRedo();
	void displayWin(sf::RenderWindow& window);

};

