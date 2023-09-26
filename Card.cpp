#include "Card.h"




Card::Card()
{
	this->color = "Undefined";
	this->index = 0;

}

Card::Card(std::string pColor, int pIndex)
{
	this->color = pColor;
	this->index = pIndex;

}

Card::~Card()
{
}

void Card::printValuesCard()
{


	if (index >= 0 && index <= 9) {
		std::cout << color << " ( " << index << " )" << std::endl;
	}
	else {
		switch (index) {
		case -1:
			std::cout << color << " ( +2 )" << std::endl;
			break;
		case -2:
			std::cout << color << " ( Reversa )" << std::endl;
			break;
		case -3:
			std::cout << color  << " ( Salto )" << std::endl;
			break;
		case -4:
			std::cout<< color << " ( +4 )" << std::endl;
			break;
		case -5:
			std::cout<< color << " ( Cambio Color )" << std::endl;
			break;


		}
	}

}

std::string Card::getColorCard()
{
	return color;
}

int Card::getIndexCard()
{
	return index;
}

void Card::setColorCard(std::string pColor)
{
	this->color = pColor;
}


