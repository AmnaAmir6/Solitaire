#include "Deck.h"
#include"Helping.h"

Deck::Deck()
{
	this->size = 52;
	for (int suit = HEARTS; suit <= SPADES; suit++)
	{
		for (int rank = ACE; rank <= KING; rank++)
		{
			Card* C = new Card(Suit(suit), Rank(rank));
			Cards.push_back(C);
		}
	}
}


Deck::Deck(const Deck& D)
{
	this->size = D.size;
	for (int i = 0; i < size; i++)
	{
		Card* C = new Card(D.Cards[i]->getSuit(), D.Cards[i]->getRank(), D.Cards[i]->isFaceUp(), D.Cards[i]->getPosition().x, D.Cards[i]->getPosition().y);
		Cards.push_back(C);
	}
}

void Deck::shuffle()
{
	srand(time(0));
	int indx1, indx2;
	for (int i = 0; i < 100; i++)
	{
		indx1 = rand() % 52;
		indx2 = rand() % 52;
		swap(Cards[indx1], Cards[indx2]);
	}
}

Card* Deck::getCard()
{
	Card* C = Cards[size - 1];
	size--;
	Cards.pop_back();
	return C;
}

bool Deck::Empty()
{
	return size == 0;
}
