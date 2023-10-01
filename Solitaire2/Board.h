#pragma once
#include"Helping.h"
#include"Deck.h"
#include"Pile.h"
#include"QueueDeck.h"
#include"FreeCell.h"

class Pile;
class Board
{
private:
	int NOC;
	int score;
	int moves;
	int sri, sci;
	int dri, dci;
	Deck* deck;
	FreeCell** Cs;
	Pile** Ps;
	QueueDeck* QD;
	int pileNo, cardNo;
	int DcPileNo;
	int time;
	vector<Card*> SelectedCards;
	bool DeckCardSelected;
	bool isAutoMove;

	sf::Texture tempBg;
	sf::Sprite bg;
	sf::Texture texUndo;
	sf::Sprite Undo;
	sf::Texture texRedo;
	sf::Sprite Redo;
	sf::Font ScoreFont;
	sf::Text _Score;
	sf::Text _Move;
	sf::Text Timetxt;

	
	void emptyStack();
public:
	Board(int _NOC);
	Board(const Board& _B);
	void draw(sf::RenderWindow& window);
	void drawPiles(sf::RenderWindow& window);
	void drawUndoRedo(sf::RenderWindow& window);
	void drawScore(sf::RenderWindow& window);
	void drawMoves(sf::RenderWindow& window);
	void drawDeck(sf::RenderWindow& window);
	void drawFreeCells(sf::RenderWindow& window);
	void drawSelectedCards(sf::RenderWindow& window);
	void isValidSc(int r, int c, bool& isSelected);
	bool isValidDes(int r, int c);
	bool isDeckClicked(int r, int c);
	bool isUndoClicked(int r, int c);
	bool isRedoClicked(int r, int c);
	void RevealDeck();
	void MovetoDc(sf::RenderWindow& window);
	void MovetoSc();
	void move(int r, int c);
	void CardWinAnimation(sf::RenderWindow& window);
	bool isWin();
	void displayTime(sf::RenderWindow& window);
	void setTime(int t);
};

