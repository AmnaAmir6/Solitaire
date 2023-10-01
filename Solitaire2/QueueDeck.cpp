#include "QueueDeck.h"
#include"Deck.h"
#include<iostream>
using namespace std;

QueueDeck::QueueDeck(int _NOC, Deck* D)
{
	this->NOC = _NOC;
	this->size = 0;
	this->ri = 20, this->ci = 160;
	this->isCard = false;

	while (!D->Empty())
	{
		Hide.push(D->getCard());
		Hide.back()->setPosition(20, 160);
	}
	FrameTex.loadFromFile("frame2.png");
	Frame.setTexture(FrameTex);
	Frame.setScale(0.35, 0.35);
	Frame.setPosition(ci, ri);
}
QueueDeck::QueueDeck(const QueueDeck& QD)
{
	this->NOC = QD.NOC;
	this->size = QD.size;
	this->ri = QD.ri;
	this->ci = QD.ci;
	this->isCard = QD.isCard;

	this->Frame = sf::Sprite(QD.Frame);

	queue<Card*> TempHide = QD.Hide;
	for (int i = 0; i < QD.Hide.size(); i++)
	{
		Card *C = new Card(*TempHide.front());
		TempHide.pop();
		Hide.push(C);
	}

	queue<Card*> TempHelp = QD.Help;
	for (int i = 0; i < QD.Help.size(); i++)
	{
		Card* C = new Card(*TempHelp.front());
		TempHelp.pop();
		Help.push(C);
	}

	Show.resize(QD.Show.size());
	for (int i = 0; i < QD.Show.size(); i++)
	{
		Card* C = new Card(*QD.Show[i]);
		Show[i] = C;
	}
}
void QueueDeck::append(Card* c)
{
	Show.push_back(c);
	for (int i = Show.size() - 1; i > 0; i--)
		swap(Show[i], Show[i - 1]);
}
void QueueDeck::draw(sf::RenderWindow& window)
{
	window.draw(Frame);
	if (!Hide.empty())
		Hide.front()->Draw(window,ri,ci);
	for (int i = Show.size()-1;i>=0; i--)
	{
		if(i==Show.size()-1)
			Show[i]->Draw(window, ri, ci + 150);
		else if(i== Show.size() - 2)
			Show[i]->Draw(window, ri, ci + 150 + 50);
		else
			Show[i]->Draw(window, ri, ci + 150 + 100);
	}
}

Card* QueueDeck::removeCard()
{
	Card* c = Show[0];
	Show.erase(Show.begin());
	return c;
}

void QueueDeck::showNext(int& score)
{
	isCard = false;
	int sSize = Show.size();
	if (Hide.size() == 0 && Help.size() != 0)
	{
		score -= 100;
		while (!Help.empty())
		{
			Hide.push(Help.front());
			Help.pop();
		}
		if (!Show.empty())
		{
			for (int i = 0; i < sSize; i++)
			{
				Show[i]->setFace(false);
				Help.push(Show[i]);
			}
			for (int i = 0; i < sSize; i++)
			{
				Show.pop_back();
			}
		}
	}
	else
	{
		if(!Show.empty())
		{
			for (int i = 0; i < NOC; i++)
			{
				Show[i]->setFace(false);
				Help.push(Show[i]);
			}
			for (int i = 0; i < NOC; i++)
			{
				Show.pop_back();
			}
		}
		for (int i = 0; i < NOC && !Hide.empty(); i++)
		{
			Show.push_back(Hide.front());
			Show[i]->setFace(true);
			Hide.pop();
		}
	}
}
bool QueueDeck::isDClicked(int r, int c)
{
	if (this->Frame.getGlobalBounds().contains(r, c))
		return true;
	return false;
}
bool QueueDeck::isCardSelected(int r, int c)
{
	if (!Show.empty() && Show[0]->isClicked(r,c))
	{
		isCard = true;
		return true;
	}
	return false;
}
void QueueDeck::showNextTop(int& score)
{
	isCard = false;
	if (Hide.empty())
		showNext(score);
	else
	{
		Show.push_back(Hide.front());
		Show[Show.size() - 1]->setFace(true);
		Hide.pop();
		size--;
	}
	/*if (Hide.size() == 0 && Help.size() != 0)
	{
		while (!Help.empty())
		{
			Hide.push(Help.front());
			Help.pop();
		}
	}
	Show.push_back(Hide.front());
	Show[Show.size()-1]->setFace(true);
	Hide.pop();
	size--;*/
}
bool QueueDeck::IsCard()
{
	return isCard;
}
void QueueDeck::setIsCard(bool c)
{
	isCard = c;
}