#include "Uno.h"

Uno::Uno()
{
	this->totalCards = 108;
	this->deck = new Card[totalCards];
	this->discardedDeck = new Card[totalCards];
	srand(time(NULL));
	createDeck();
}

Uno::~Uno()
{
	delete[] deck;
	delete[] discardedDeck;
}

void Uno::createDeck()
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

void Uno::shuffleDeck()
{
	for (int currentPositioninVec = 0; currentPositioninVec < totalCards; currentPositioninVec++) {
		int number = getRandomNum(currentPositioninVec);
		swapCardPosition( &deck[currentPositioninVec], &deck[number]);
	}
}

void Uno::swapCardPosition(Card* pCard1, Card* pCard2) {
	Card x;

	x = *pCard1;
	*pCard1 = *pCard2;
	*pCard2 = x;
}

int Uno::getRandomNum(int pFirstNumber)
{
	int number = pFirstNumber + rand() % (totalCards - pFirstNumber);

	return number;
}

int Uno::getRandomNum(int pFirstNumber, int pLastNumber)
{
	int number = pFirstNumber + rand() % pLastNumber;

	return number;
}

void Uno::playUNO()
{
	
	int menu = 0;
	int tries = 0;
	do {
		system("cls");
		std::cout << "\n\t\tBienvenido a mi juego UNO.\n\n\nSelecione un modo para jugar:\n1) 1vs1\n2) 1vsCPU\n3) Salir\n\n";
		std::cin >> menu;

		switch (menu) {
		case 1:
			playUno1vs1();
			menu = 3;
			break;
		case 2:
			playUno1vsCPU();
			menu = 3;
			break;
		case 3:
			exit(1);
			break;

		default:
			system("cls");
			std::cout << "Opcion erronea. Por favor, intentelo de nuevo.\n";
			system("pause");
			system("cls");
			break;
		}
	} while (menu != 3);
	
}

void Uno::printDeck(int pIDplayer, Card CardinCenter)
{
	for (int i = 0; i < 50; i++)
	{

		if (player[pIDplayer][i].getColorCard() != "Undefined") {
			std::cout << i + 1 << ": ";
			player[pIDplayer][i].printValuesCard();

		}
	}
	std::cout << "\n\nSi desea comer una carta digite 0\n";
	std::cout << "\nLa carta que hay en la mesa es: ";
	CardinCenter.printValuesCard();
	std::cout << "Jugador " << pIDplayer + 1 << ". Cual carta desea lanzar?\n";
	
}

void Uno::playUno1vs1()
{
	int currentPositionInVecDiscarded = 0;
	int turnOfPlayer = 0;
	int selectedCard;
	Card auxiliarCard;
	

		shuffleDeck();
		fillPlayersDecks();
		putCardOnCenter(14, &auxiliarCard, currentPositionInVecDiscarded);
		currentPositionInVecDiscarded++;

		while (playerHasCards(0) && playerHasCards(1)) 
		{	
				if(turnOfPlayer == 0){
					selectedCard = SelectPlayerCard(turnOfPlayer, auxiliarCard, currentPositionInVecDiscarded);
					auxiliarCard = player[turnOfPlayer][selectedCard];
					putCardOnCenter(turnOfPlayer, selectedCard , currentPositionInVecDiscarded);
					if (isSpecialCard(auxiliarCard)) {
						doSpecialAction(turnOfPlayer, &auxiliarCard, currentPositionInVecDiscarded);
					}
					currentPositionInVecDiscarded++;
					turnOfPlayer++;
					arrangeDeck(turnOfPlayer);
				}

				if (turnOfPlayer == 1) {
					selectedCard = SelectPlayerCard(turnOfPlayer, auxiliarCard, currentPositionInVecDiscarded);
					auxiliarCard = player[turnOfPlayer][selectedCard];
					putCardOnCenter(turnOfPlayer, selectedCard, currentPositionInVecDiscarded);
					if (isSpecialCard(auxiliarCard)) {
						doSpecialAction(turnOfPlayer, &auxiliarCard, currentPositionInVecDiscarded);
					}
					currentPositionInVecDiscarded++;
					turnOfPlayer--;
					arrangeDeck(turnOfPlayer);
				}


		}
	system("cls");
	std::cout << "Un jugador ha ganado";
	system("pause");

}

void Uno::playUno1vsCPU()
{
	int currentPositionInVecDiscarded = 0;
	int turnOfPlayer = 0;
	int selectedCard;
	Card auxiliarCard;
	shuffleDeck();
	fillPlayersDecks();
	putCardOnCenter(14, &auxiliarCard, currentPositionInVecDiscarded);
	currentPositionInVecDiscarded++;
	
	while (playerHasCards(0) && playerHasCards(1))
	{
		if (turnOfPlayer == 0) {
			selectedCard = SelectPlayerCard(turnOfPlayer, auxiliarCard, currentPositionInVecDiscarded);
			auxiliarCard = player[turnOfPlayer][selectedCard];
			putCardOnCenter(turnOfPlayer, selectedCard, currentPositionInVecDiscarded);
			if (isSpecialCard(auxiliarCard)) {
				doSpecialAction(turnOfPlayer, &auxiliarCard, currentPositionInVecDiscarded);
			}
			currentPositionInVecDiscarded++;
			turnOfPlayer++;
			arrangeDeck(turnOfPlayer);
		}

		if (turnOfPlayer == 1) {
			selectedCard = selectCPUCard(auxiliarCard, currentPositionInVecDiscarded);
			auxiliarCard = player[turnOfPlayer][selectedCard];
			putCardOnCenter(turnOfPlayer, selectedCard, currentPositionInVecDiscarded);
			if (isSpecialCard(auxiliarCard)) {
				doSpecialActionCPU(turnOfPlayer, &auxiliarCard, currentPositionInVecDiscarded);
			}
			currentPositionInVecDiscarded++;
			turnOfPlayer--;
			arrangeDeck(turnOfPlayer);
		}


	}
	system("cls");
	std::cout << "Un jugador ha ganado\n\n";
	system("pause");
}

void Uno::fillPlayersDecks()
{
	int currentPositioninVec = 0;

	for (int loop = 0; loop < 14; loop += 2) {
		swapCardPosition(&deck[loop], &player[0][currentPositioninVec]);
		swapCardPosition(&deck[loop + 1],&player[1][currentPositioninVec]);
		currentPositioninVec++;
	}
}

void Uno::putCardOnCenter(int pPositioninCardVec,Card* pAuxiliarCard ,int pPositioninDiscardedVec)
{
	*pAuxiliarCard = deck[pPositioninCardVec];

	swapCardPosition(&deck[pPositioninCardVec], &discardedDeck[pPositioninDiscardedVec]);
}

void Uno::putCardOnCenter(int pIDplayer,int pPositionPlayerDeck, int pPositioninDiscardedVec)
{

	swapCardPosition(&player[pIDplayer][pPositionPlayerDeck], &discardedDeck[pPositioninDiscardedVec]);
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
		printDeck(pIDplayer, pCardinCenter);
		std::cin >> selectedCard;
		selectedCard -= 1;
		tries++;
		while (selectedCard < -1 || selectedCard > 49) {
			std::cout << "\n\n\t\tAccion no permitida, vuelva a intetarlo.\n\n";
			system("pause");
			system("cls");

			printDeck(pIDplayer, pCardinCenter);
			std::cin >> selectedCard;
			selectedCard -= 1;
		}

		while (selectedCard == -1) {
			drawCard(pIDplayer, currentPositionInVecDiscarded);
			system("cls");
			printDeck(pIDplayer, pCardinCenter);

			std::cin >> selectedCard;
			selectedCard -= 1;
		}

		
	} while (isAnUndefinedCard(pIDplayer, selectedCard) || !isUnableCard(pIDplayer,selectedCard, pCardinCenter));

	return selectedCard;
}

int Uno::selectCPUCard(Card pCardinCenter, int& currentPositionInVecDiscarded)
{
	int positionLastCard = 0;
	while(!isAnUndefinedCard(1, positionLastCard)){
		positionLastCard++;
	}

	for (int loop = 0; loop < positionLastCard; loop++) {
		if (isUnableCard(1, loop, pCardinCenter)) {
			return loop;
		}
	}
	do {
		drawCard(1, currentPositionInVecDiscarded);

		if (isUnableCard(1, positionLastCard, pCardinCenter)) {
			return positionLastCard;
		}

		positionLastCard++;
	} while (true);
	
}

void Uno::drawCard(int pIDplayer, int &currentPositionInVecDiscarded)
{
	static int currentPositionInDeckVec = 15;
	int loop = 0;

	if (deckHasCards()) {

		while (!isAnUndefinedCard(pIDplayer,loop)) {
			loop++;
		}
		swapCardPosition(&player[pIDplayer][loop],&deck[currentPositionInDeckVec]);
		currentPositionInDeckVec++;
	}
	else {
		swapCardPosition(&discardedDeck[0], &discardedDeck[currentPositionInDeckVec - 1]);
		shuffleDiscardedDeck(currentPositionInDeckVec - 1);
		refillDeck(currentPositionInDeckVec-1);
		currentPositionInDeckVec = 0;
		currentPositionInVecDiscarded = 1;

		swapCardPosition(&player[pIDplayer][loop], &deck[currentPositionInDeckVec]);
		currentPositionInDeckVec++;
	}
}

void Uno::shuffleDiscardedDeck(int pLastCardInDiscardedDeck)
{
	for (int actualCard = 1; actualCard < pLastCardInDiscardedDeck; actualCard++) {
		int number = getRandomNum(actualCard, pLastCardInDiscardedDeck);
		swapCardPosition(&discardedDeck[actualCard], &deck[number]);
	}
}

void Uno::refillDeck(int pLastCardInDiscartedVec)
{
	

	for (int loop = 1; loop <= pLastCardInDiscartedVec; loop++) {
		swapCardPosition(&discardedDeck[loop], &deck[loop - 1]);
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

void Uno::arrangeDeck(int pIDplayer)
{
	int positionOfIndefinedCard = 0;
	while (!isAnUndefinedCard(pIDplayer, positionOfIndefinedCard)) {
		positionOfIndefinedCard++;
	}

	for (; positionOfIndefinedCard < 49; positionOfIndefinedCard++) {
		swapCardPosition(&player[pIDplayer][positionOfIndefinedCard], &player[pIDplayer][positionOfIndefinedCard+1]);
	}

}

void Uno::doSpecialAction(int& IDplayer, Card* pCardinCenter, int& currentPositionInVecDiscarded)
{
	if (IDplayer == 0) {
		switch (pCardinCenter->getIndexCard()) {
		case -1:
			for (int loop = 0; loop < 2; loop++) {
				drawCard(1, currentPositionInVecDiscarded);
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
				drawCard(1, currentPositionInVecDiscarded);
			}
			IDplayer--;
			break;

		case -5:
			changeColorCard(pCardinCenter);
			break;
		}
	}

	else if (IDplayer == 1){
		switch (pCardinCenter->getIndexCard()) {
		case -1:
			for (int loop = 0; loop < 2; loop++) {
				drawCard(0, currentPositionInVecDiscarded);
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
				drawCard(0, currentPositionInVecDiscarded);
			}
			IDplayer++;
			break;

		case -5:
			changeColorCard(pCardinCenter);
			break;

		}
	}
}

void Uno::doSpecialActionCPU(int &IDplayer, Card* pCardinCenter, int& currentPositionInVecDiscarded)
{
	switch (pCardinCenter->getIndexCard()) {
	case -1:
		for (int loop = 0; loop < 2; loop++) {
			drawCard(0, currentPositionInVecDiscarded);
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
		changeColorCardCPU(pCardinCenter);
		for (int loop = 0; loop < 4; loop++) {
			drawCard(0, currentPositionInVecDiscarded);
		}
		IDplayer++;
		break;

	case -5:
		changeColorCardCPU(pCardinCenter);
		break;
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

void Uno::changeColorCardCPU(Card* CardinCenter)
{
	int color = getRandomNum(1, 4);
	
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

bool Uno::isAnUndefinedCard(int pIDplayer, int pPositioninCardVec)
{
	if (player[pIDplayer][pPositioninCardVec].getColorCard() == "Undefined") {
		return true;
	}
	
	return false;
}

bool Uno::isUnableCard(int pIDplayer, int pPositioninCardVec, Card pCardinCenter)
{
	if (player[pIDplayer][pPositioninCardVec].getColorCard() == pCardinCenter.getColorCard()) {
		return true;
	}
	if (player[pIDplayer][pPositioninCardVec].getIndexCard() == pCardinCenter.getIndexCard()) {
		return true;
	}
	if (player[pIDplayer][pPositioninCardVec].getColorCard() == "Negro") {
		return true;
	}
	return false;
}

bool Uno::isSpecialCard(Card CardinCenter)
{
	if (CardinCenter.getIndexCard() >= -5 && CardinCenter.getIndexCard() < 0 ) {
		return true;
	}

	return false;
}

