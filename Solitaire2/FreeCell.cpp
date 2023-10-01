#include "FreeCell.h"

FreeCell::FreeCell(Suit _S,int r,int c)
{
	size = 0;
	S = _S;
	ri = r;
	ci = c;
	if (S == SPADES)
	{
		CoinTex.loadFromFile("spade2.png");
	}
	else if (S == CLUBS)
	{
		CoinTex.loadFromFile("club2.png");
	}
	else if (S == DIAMONDS)
	{
		CoinTex.loadFromFile("diamond2.png");
	}
	else
	{
		CoinTex.loadFromFile("heart2.png");
	}
	Coin.setTexture(CoinTex);
	Coin.setScale(0.5, 0.5);
	Coin.setPosition(ci + 25, ri + 50);
	FrameTex.loadFromFile("frame2.png");
	Frame.setTexture(FrameTex);
	Frame.setScale(0.35, 0.35);
	Frame.setPosition(ci, ri);

	Rec.setSize(sf::Vector2f(130,173));
	Rec.setPosition(ci - 10, ri - 10);
}

FreeCell::FreeCell(const FreeCell& FC)
{
	this->size = FC.size;
	this->S = FC.S;
	this->ri = FC.ri;
	this->ci = FC.ci;

	this->Coin = sf::Sprite(FC.Coin);
	this->Frame = sf::Sprite(FC.Frame);
	this->Rec = sf::RectangleShape(FC.Rec);

	stack<Card*> Help1 = FC.Cs;
	stack<Card*> Help2;
	for (int i = 0; i < Help1.size(); i++)
	{
		Card* C = new Card(*Help1.top());
		Help1.pop();
		Help2.push(C);
	}
	while (!Help2.empty())
	{
		Cs.push(Help2.top());
		Help2.pop();
	}
}


bool FreeCell::isComplete()
{
	return size == 13;
}

bool FreeCell::isEmpty()
{
	return size == 0;
}
bool FreeCell::canAppend(Card* C)
{
	if(C->getSuit()==S)
	{
		if (isEmpty())
		{
			if (C->getRank() == ACE)
				return true;
		}
		else
		{
			if (C->getRank() - 1 == Cs.top()->getRank())
				return true;
		}
	}
	return false;
}
void FreeCell::append(Card* C)
{
	Cs.push(C);
	size++;
}

void FreeCell::draw(sf::RenderWindow& window)
{
	window.draw(Frame);
	window.draw(Coin);
	if (!Cs.empty())
		Cs.top()->Draw(window,ri,ci);
}
bool FreeCell::isClicked(int r, int c)
{
	if (this->Rec.getGlobalBounds().contains(r, c))
		return true;
	return false;
}
vector<Card*> FreeCell::split()
{
	vector<Card*> A;
	A.push_back(Cs.top());
	Cs.pop();
	size--;
	return A;
}
sf::Vector2f FreeCell::getPostion()
{
	return sf::Vector2f(ri, ci);
}
