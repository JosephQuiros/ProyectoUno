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
	void PlayUno();

private:
	void CreateDeck();
	void ShuffleDeck();
	void SwapCardPosition(Card* pCard1, Card* pCard2);
	int getRandomNum(int pFirstNumber, int pLastNumber);
	void PrintDeck(int pIDplayer, Card CardinCenter);
	void FillPlayersDecks();
	void RefillDeck(int pLastCardInDiscartedVec);
	void putCardOnCenter(int pPositioninCardVec,Card* pAuxiliarCard ,int pPositioninDiscardedVec);
	void putCardOnCenter(int pIDplayer, int pPositioninCardVec, int pPositioninDiscardedVec);
	int SelectPlayerCard(int pIDplayer, Card pPositioninDiscardedVec, int &currentPositionInVecDiscarded);
	void drawCard(int pIDplayer, int &currentPositionInVecDiscarded);
	void shuffleDiscardedDeck(int pLastCard);
	void DoSpecialAction(int &pIDplayer, Card* pCardinCenter, int& currentPositionInVecDiscarded);
	void changeColorCard(Card* CardinCenter);
	bool deckHasCards();
	bool stillFindingWinner(int* pPoints);
	bool playerHasCards(int pIDplayer );
	bool IsAnUndefinedCard(int pIDplayer, int pPositioninCardVec);
	bool IsUnableCard(int pIDplayer, int pPositioninCardVec, Card pCardinCenter);
	bool IsSpecialCard(Card CardinCenter);
};