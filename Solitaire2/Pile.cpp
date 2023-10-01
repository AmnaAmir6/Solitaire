#include "Pile.h"

Pile::Pile(int s, Deck* D, int _ri, int _ci)
{
	this->ri = _ri;
	this->ci = _ci;
	this->size = s;
	this->RevealCards = 1;
	this->topCardSelected = false;
	this->ti = size - 1;
	this->isFirst = true;
	this->Rec.setSize(sf::Vector2f(178, 490));
	Rec.setPosition(ci - 25, ri - 18);
	int sri = ri - 20;
	for (int i = 0; i < size; i++)
	{
		S.push_back(D->getCard());
		sri += 20;
		S.back()->setPosition(sri, ci);
	}
	S.back()->setFace(true);
}

Pile::Pile(const Pile& P)
{
	this->ri = P.ri;
	this->ci = P.ci;
	this->size = P.size;
	this->RevealCards = P.RevealCards;
	this->topCardSelected = P.topCardSelected;
	this->ti = P.ti;
	this->isFirst = P.isFirst;
	this->Rec = sf::RectangleShape( P.Rec);

	for (int i = 0; i < size; i++)
	{
		Card* C = new Card(*P.getCardAt(i));
		S.push_back(C);
	}
}

void Pile::append(vector<Card*> Cs)
{
	for (int i = 0; i < Cs.size(); i++)
	{
		S.push_back(Cs[i]);
		size++;
		RevealCards++;
	}
}

bool Pile::canAppend(vector<Card*> Cs)
{
	if (!isEmpty())
	{
		if (S.back()->getSuit() == HEARTS || S.back()->getSuit() == DIAMONDS)
		{
			if (Cs[0]->getSuit() == SPADES || Cs[0]->getSuit() == CLUBS)
			{
				if (S.back()->getRank() == Cs[0]->getRank() + 1)
					return true;
			}
		}
		else if (S.back()->getSuit() == SPADES || S.back()->getSuit() == CLUBS)
		{
			if (Cs[0]->getSuit() == HEARTS || Cs[0]->getSuit() == DIAMONDS)
			{
				if (S.back()->getRank() == Cs[0]->getRank() + 1)
					return true;
			}
		}
	}
	else
	{
		if (Cs[0]->getRank() == KING)
			return true;
	}
	return false;
}

vector<Card*> Pile::split(int i)
{
	RevealCards = RevealCards - (size - i);
	size = size - (size - i);
	return S.popKValues(i);
}

bool Pile::isEmpty()
{
	return size == 0;
}

void Pile::selectTopCard(int i)
{
	if (!isEmpty())
	{
		ti = i;
		this->topCardSelected = true;
	}
}

void Pile::deselectTopCard()
{
	this->topCardSelected = false;
	ti = -1;
}

bool Pile::isCardSelected(int r, int c)
{
	if (this->Rec.getGlobalBounds().contains(r, c))
		return true;
	return false;
}

void Pile::draw(sf::RenderWindow& window,Pile** Ps,sf::Sprite bg, Board* B)
{
	int i = 0;
	int x = 0, y = 0;
	if (isFirst)
	{
		isFirst = false;
		for (int i = 0; i < S.size(); i++)
		{
			int sri = 20;
			float sci = 160;
			float dri ,dci=ci;
			dri = ri + (20 * i);
			float r=sri, c=sci;
			float max = 30;
			for (int x = 0; x < max; x++)
			{
				r = r + ((dri - sri) / max);
				c = c + ((dci - sci) / max);
				window.clear();
				window.draw(bg);
				B->drawUndoRedo(window);
				B->drawScore(window);
				B->drawMoves(window);
				B->displayTime(window);
				B->drawFreeCells(window);
				B->drawDeck(window);
				for (int j = 0; j < size - 1; j++)
				{
					Ps[j]->draw(window, Ps, bg, B);
				}
				for (int j = 0; j < i; j++)
				{
					S[j]->Draw(window);
				}
				S[i]->Draw(window,r ,c );
				window.display();
			}
		}
	}
	else
	{
		for (int i = 0; i < S.size(); i++)
		{
			if (i >= size - RevealCards)
			{
				S[i]->Draw(window, ri + (20 * x) + (40 * y), ci); y++;
			}
			else
			{
				S[i]->Draw(window, ri + (20 * x), ci); x++;
			}
		}
	}
	return;
}
//void Pile::draw(sf::RenderWindow& window, Pile** Ps, sf::Sprite s)
//{
//	int x = 0, y = 0;
//	for (int i = 0; i < S.size();i++)
//	{
//		//S[i]->Draw(window, ri + (35 * i), ci);
//		if (i >= size-RevealCards)
//		{
//			S[i]->Draw(window, ri + (20 * x) + (40 * y), ci); y++;
//		}
//		else
//		{
//			S[i]->Draw(window, ri + (20 * x), ci); x++;
//		}
//	}
//	return;
//}

Card* Pile::getCardAt(int i) const
{
	return S[i];
}

int Pile::getSize()
{
	return size;
}

sf::Vector2f Pile::getPos()
{
	return sf::Vector2f(ri, ci);
}

void Pile::revealNext()
{
	S.back()->setFace(true);
	RevealCards++;
}

int Pile::getRevealCards()
{
	return RevealCards;
}