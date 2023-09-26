#include "Uno.h"
Uno::Uno()
{
	this->totalCards = 108;
	this->deck = new Card[totalCards];
	this->discardedDeck = new Card[totalCards];
	srand(time(NULL));
	CreateDeck();
}

Uno::~Uno()
{
	delete[] deck;
	delete[] discardedDeck;
}

void Uno::CreateDeck()
{
	std::string ColorsOfCards[5] = { "Amarillo", "Azul", "Verde", "Rojo", "Negro"};
	int currentPositioninVec = 0;

	for (int color = 0; color < 4; color++)
	{
		deck[currentPositioninVec++] = Card(ColorsOfCards[color], 0);
		for (int index = 1; index <= 9; index++)
		{
			deck[currentPositioninVec++] = Card(ColorsOfCards[color], index);
			deck[currentPositioninVec++] = Card(ColorsOfCards[color], index);
		}

		for (int loop = 0; loop < 2; loop++)
		{
			deck[currentPositioninVec++] = Card(ColorsOfCards[color], -1);
			deck[currentPositioninVec++] = Card(ColorsOfCards[color], -2);
			deck[currentPositioninVec++] = Card(ColorsOfCards[color], -3);
		}

	}

	for (int loop = 0; loop < 4; loop++)
	{
		deck[currentPositioninVec++] = Card(ColorsOfCards[4], -4);
		deck[currentPositioninVec++] = Card(ColorsOfCards[4], -5);
	}

}

void Uno::ShuffleDeck()
{
	for (int currentPositioninVec = 0; currentPositioninVec < totalCards; currentPositioninVec++) {
		int number = getRandomNum(currentPositioninVec, totalCards);
		SwapCardPosition( &deck[currentPositioninVec], &deck[number]);
	}
}

void Uno::SwapCardPosition(Card* pCard1, Card* pCard2) {
	Card x;

	x = *pCard1;
	*pCard1 = *pCard2;
	*pCard2 = x;
}

int Uno::getRandomNum(int pFirstNumber, int pLastNumber)
{
	int x = pFirstNumber + rand() % (totalCards - pFirstNumber);

	return x;
}

void Uno::PrintDeck(int pIDplayer, Card CardinCenter)
{
	for (int i = 0; i < 50; i++)
	{

		if (player[pIDplayer][i].getColorCard() != "Undefined") {
			std::cout << i + 1 << ": ";
			player[pIDplayer][i].PrintValuesCard();

		}
	}
	std::cout << "\n\nSi desea comer una carta digite 0\n";
	std::cout << "\nLa carta que hay en la mesa es: ";
	CardinCenter.PrintValuesCard();
	std::cout << "Jugador " << pIDplayer + 1 << ". Cual carta desea lanzar?\n";
	
}

void Uno::PlayUno1vs1()
{
	int points[2] = {0};
	int currentPositionInVecDiscarded = 0;
	int turnOfPlayer = 0;
	int selectedCard;
	Card auxiliarCard;
	

	//while (stillFindingWinner(points)) 
	//{
		ShuffleDeck();
		FillPlayersDecks();
		putCardOnCenter(14, &auxiliarCard, currentPositionInVecDiscarded);
		currentPositionInVecDiscarded++;

		while (playerHasCards(0) && playerHasCards(1)) 
		{	
				if(turnOfPlayer == 0){
					selectedCard = SelectPlayerCard(turnOfPlayer, auxiliarCard, currentPositionInVecDiscarded);
					auxiliarCard = player[turnOfPlayer][selectedCard];
					putCardOnCenter(turnOfPlayer, selectedCard , currentPositionInVecDiscarded);
					if (IsSpecialCard(auxiliarCard)) {
						DoSpecialAction(turnOfPlayer, &auxiliarCard, currentPositionInVecDiscarded);
					}
					currentPositionInVecDiscarded++;
					turnOfPlayer++;

				}

				if (turnOfPlayer == 1) {
					selectedCard = SelectPlayerCard(turnOfPlayer, auxiliarCard, currentPositionInVecDiscarded);
					auxiliarCard = player[turnOfPlayer][selectedCard];
					putCardOnCenter(turnOfPlayer, selectedCard, currentPositionInVecDiscarded);
					if (IsSpecialCard(auxiliarCard)) {
						DoSpecialAction(turnOfPlayer, &auxiliarCard, currentPositionInVecDiscarded);
					}
					currentPositionInVecDiscarded++;
					turnOfPlayer--;
				}


		}
	//}
	system("cls");
	std::cout << "Un jugador ha ganado";
	system("pause");

}

void Uno::FillPlayersDecks()
{
	int currentPositioninVec = 0;

	for (int loop = 0; loop < 14; loop += 2) {
		SwapCardPosition(&deck[loop], &player[0][currentPositioninVec]);
		SwapCardPosition(&deck[loop + 1],&player[1][currentPositioninVec]);
		currentPositioninVec++;
	}
}

void Uno::putCardOnCenter(int pPositioninCardVec,Card* pAuxiliarCard ,int pPositioninDiscardedVec)
{
	*pAuxiliarCard = deck[pPositioninCardVec];

	SwapCardPosition(&deck[pPositioninCardVec], &discardedDeck[pPositioninDiscardedVec]);
}

void Uno::putCardOnCenter(int pIDplayer,int pPositionPlayerDeck, int pPositioninDiscardedVec)
{

	SwapCardPosition(&player[pIDplayer][pPositionPlayerDeck], &discardedDeck[pPositioninDiscardedVec]);
}

int Uno::SelectPlayerCard(int pIDplayer, Card pCardinCenter, int &currentPositionInVecDiscarded)
{
	int selectedCard = 0;
	
	

	int tries = 0;
	do {
		system("cls");
		if (tries > 0) {
			std::cout << "\n\n\t\tAccion no permitida, vuelva a intetarlo.\n\n";
			system("pause");
			system("cls");
		}
		PrintDeck(pIDplayer, pCardinCenter);
		std::cin >> selectedCard;
		selectedCard -= 1;
		tries++;
		while (selectedCard < -1 || selectedCard > 49) {
			std::cout << "\n\n\t\tAccion no permitida, vuelva a intetarlo.\n\n";
			system("pause");
			system("cls");

			PrintDeck(pIDplayer, pCardinCenter);
			std::cin >> selectedCard;
			selectedCard -= 1;
		}

		while (selectedCard == -1) {
			drawCard(pIDplayer, currentPositionInVecDiscarded);
			system("cls");
			PrintDeck(pIDplayer, pCardinCenter);

			std::cin >> selectedCard;
			selectedCard -= 1;
		}

		
	} while (IsAnUndefinedCard(pIDplayer, selectedCard) || IsUnableCard(pIDplayer,selectedCard, pCardinCenter));

	return selectedCard;
}

void Uno::drawCard(int pIDplayer, int &currentPositionInVecDiscarded)
{
	static int currentPositionInDeckVec = 15;
	int loop = 0;

	if (deckHasCards()) {

		while (!IsAnUndefinedCard(pIDplayer,loop)) {
			loop++;
		}
		SwapCardPosition(&player[pIDplayer][loop],&deck[currentPositionInDeckVec]);
		currentPositionInDeckVec++;
	}
	else {
		SwapCardPosition(&discardedDeck[0], &discardedDeck[currentPositionInDeckVec - 1]);
		shuffleDiscardedDeck(currentPositionInDeckVec - 1);
		RefillDeck(currentPositionInDeckVec-1);
		currentPositionInDeckVec = 0;
		currentPositionInVecDiscarded = 1;

		SwapCardPosition(&player[pIDplayer][loop], &deck[currentPositionInDeckVec]);
		currentPositionInDeckVec++;
	}
}

void Uno::shuffleDiscardedDeck(int pLastCardInDiscardedDeck)
{
	for (int actualCard = 1; actualCard < pLastCardInDiscardedDeck; actualCard++) {
		int number = getRandomNum(actualCard, pLastCardInDiscardedDeck);
		SwapCardPosition(&discardedDeck[actualCard], &deck[number]);
	}
}

void Uno::RefillDeck(int pLastCardInDiscartedVec)
{
	

	for (int loop = 1; loop <= pLastCardInDiscartedVec; loop++) {
		SwapCardPosition(&discardedDeck[loop], &deck[loop - 1]);
	}
}

bool Uno::deckHasCards()
{
	int hasCard = 0;
	for (int loop = 0; loop < totalCards; loop++) {
		if (deck[loop].getColorCard() != "Undefined") {
			hasCard++;
		}
	}
	if (hasCard == 0) {
		return false;
	}

	return true;
}

void Uno::DoSpecialAction(int& IDplayer, Card* pCardinCenter, int& currentPositionInVecDiscarded)
{
	//pIDplayer 0
	if (IDplayer == 0) {
		switch (pCardinCenter->getIndexCard()) {
		case -1:
			for (int loop = 0; loop < 2; loop++) {
				drawCard(IDplayer + 1, currentPositionInVecDiscarded);
			}
			IDplayer--;
			break;

		case -2:
			IDplayer--;
			break;

		case -3:
			IDplayer--;
			break;

		case -4:
			changeColorCard(pCardinCenter);
			for (int loop = 0; loop < 4; loop++) {
				drawCard(IDplayer + 1, currentPositionInVecDiscarded);
			}
			IDplayer--;
			break;

		case -5:
			changeColorCard(pCardinCenter);
			break;
		}
	}
	//pIDplayer 1
	else if (IDplayer == 1){
		switch (pCardinCenter->getIndexCard()) {
		case -1:
			for (int loop = 0; loop < 2; loop++) {
				drawCard(IDplayer - 1, currentPositionInVecDiscarded);
			}
			IDplayer++;
			break;

		case -2:
			IDplayer++;
			break;

		case -3:
			IDplayer++;
			break;

		case -4:
			changeColorCard(pCardinCenter);
			for (int loop = 0; loop < 4; loop++) {
				drawCard(IDplayer - 1, currentPositionInVecDiscarded);
			}
			IDplayer++;
			break;

		case -5:
			changeColorCard(pCardinCenter);
			break;

		}
	}
}

void Uno::changeColorCard(Card* CardinCenter)
{
	int color = 0;
	std::cout << "\n\nSelecione el color deseado:\n1)Amarillo\n2)Azul\n3)Verde\n4)Rojo\n";
	std::cin >> color;

	do {
		switch (color)
		{
		case 1:
			CardinCenter->setColorCard("Amarillo");
			break;
		case 2:
			CardinCenter->setColorCard("Azul");
			break;
		case 3:
			CardinCenter->setColorCard("Verde");
			break;
		case 4:
			CardinCenter->setColorCard("Rojo");
			break;

		default:
			break;
		}
	}while (color < 1 && color > 5);
	
}

bool Uno::stillFindingWinner(int* pPoints)
{
	if (pPoints[0] < 500 || pPoints[1] < 500) {
		return true;
	}

	return false;
}

bool Uno::playerHasCards(int pIDplayer)
{
	int playerHasCards = 0;

	for (int loop = 0; loop < 50; loop++) {
		if (player[pIDplayer][loop].getColorCard() != "Undefined") {
			playerHasCards++;
		}
	}
	if (playerHasCards != 0) {
		return true;
	}
	return false;
}

bool Uno::IsAnUndefinedCard(int pIDplayer, int pPositioninCardVec)
{
	if (player[pIDplayer][pPositioninCardVec].getColorCard() != "Undefined") {
		return false;
	}
	
	return true;
}

bool Uno::IsUnableCard(int pIDplayer, int pPositioninCardVec, Card pCardinCenter)
{
	if (player[pIDplayer][pPositioninCardVec].getColorCard() == pCardinCenter.getColorCard()) {
		return false;
	}
	if (player[pIDplayer][pPositioninCardVec].getIndexCard() == pCardinCenter.getIndexCard()) {
		return false;
	}
	if (player[pIDplayer][pPositioninCardVec].getColorCard() == "Negro") {
		return false;
	}
	return true;
}

bool Uno::IsSpecialCard(Card CardinCenter)
{
	if (CardinCenter.getIndexCard() >= -5 && CardinCenter.getIndexCard() < 0 ) {
		return true;
	}

	return false;
}

