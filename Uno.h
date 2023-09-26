#pragma once
#include "Card.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

class Uno
{
private:
	int totalCards;
	Card* deck;
	Card* discardedDeck;
	Card player[2][50];
	

public:
	Uno();
	~Uno();
	void playUNO();
	


private:
	void playUno1vs1();
	void playUno1vsCPU();
	void createDeck();
	void shuffleDeck();
	void swapCardPosition(Card* pCard1, Card* pCard2);
	int getRandomNum(int pFirstNumber);
	int getRandomNum(int pFirstNumber, int pLastNumber);
	void printDeck(int pIDplayer, Card CardinCenter);
	void fillPlayersDecks();
	void refillDeck(int pLastCardInDiscartedVec);
	void putCardOnCenter(int pPositioninCardVec,Card* pAuxiliarCard ,int pPositioninDiscardedVec);
	void putCardOnCenter(int pIDplayer, int pPositioninCardVec, int pPositioninDiscardedVec);
	int SelectPlayerCard(int pIDplayer, Card pCardinCenter, int &currentPositionInVecDiscarded);
	int selectCPUCard(Card pPositioninDiscardedVec, int& currentPositionInVecDiscarded);
	void drawCard(int pIDplayer, int &currentPositionInVecDiscarded);
	void shuffleDiscardedDeck(int pLastCard);
	void doSpecialAction(int &pIDplayer, Card* pCardinCenter, int& currentPositionInVecDiscarded);
	void doSpecialActionCPU(int &IDplayer, Card* pCardinCenter, int& currentPositionInVecDiscarded);
	void changeColorCard(Card* CardinCenter);
	void changeColorCardCPU(Card* CardinCenter);
	bool deckHasCards();
	void arrangeDeck(int pIDplayer);
	bool stillFindingWinner(int* pPoints);
	bool playerHasCards(int pIDplayer );
	bool isAnUndefinedCard(int pIDplayer, int pPositioninCardVec);
	bool isUnableCard(int pIDplayer, int pPositioninCardVec, Card pCardinCenter);
	bool isSpecialCard(Card CardinCenter);
	
};