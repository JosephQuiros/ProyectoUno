#pragma once
#include <string>
#include <iostream>

class Card
{
private:
	std::string color;
	int index;

public:
	Card();
	Card(std::string pColor, int pIndex);
	~Card();

	std::string getColorCard();
	int getIndexCard();
	void printValuesCard();
	void setColorCard(std::string pColor);
};

