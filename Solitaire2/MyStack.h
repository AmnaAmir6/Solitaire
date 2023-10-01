#pragma once
#include"Card.h"
#include<vector>
#include<iostream>
using namespace std;


class MyStack
{
	int s;
	vector<Card*>Vs;
public:
	MyStack(int _s = 0)
	{
		s = _s;
	}
	int size()
	{
		return s;
	}
	Card* back()
	{
		return Vs[s - 1];
	}
	void push_back(Card* v)
	{
		Vs.push_back(v);
		s++;
	}
	vector<Card*> popKValues(int k)
	{
		vector<Card*>Temp;
		for (int i = k; i < s; i++)
		{
			Temp.push_back(Vs[i]);
		}
		for (int i = 0; i < s - k; i++)
		{
			Vs.pop_back();
		}
		s = s - (s - k);
		return Temp;
	}
	Card* operator[](int i) const
	{
		return Vs[i];
	}
};