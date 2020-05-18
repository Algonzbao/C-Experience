#include <iostream>
#include "Score.h"
#include "Game.h"
#include "checkML.h"

using namespace std;

int menu();

int main() {
	tGame Game;
	tScores Points;
	int op;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	bool CurrentGame = false;
	bool GameEnded = false;
	bool Finish = false;
	bool Scores = false;

	if (chargeScores(Points)) {
		while (!GameEnded) {
			op = menu();
			cout << "Your choice: " << op << endl;
			cout << "_____________" << endl;
			if (op == 1) {
				if (loadGame(Game)) {
					CurrentGame = true;
				}
				while (CurrentGame) {
					printGame(Game);
					Finish = playTurn(Game);
					if (Finish) {
						loadScores(Points, Game.PlayerList[Game.currentturn].name, Game.NumberPlayers);
						CurrentGame = false;
					}
					else {
						nextTurn(Game);
						printGame(Game);
					}
				}
			}
			else if (op == 2) {
				int choice;
				switch (menuSCORES()) {
					case 1: AlphabeticOrder(Points);
						break;
					case 2 : printScores(Points);
						break;
				}
			}
			else {
				GameEnded = true;
				saveScores(Points);
				freeScores(Points);

				for (int i = 0; i < Game.NumberPlayers; i++) {
					free(Game.PlayerList[i].pack);
				}
			}
		}
	}
	system("pause");
	return 0;
}

int menu() {
	int op;
	cout << "[-----------]" << endl;
	cout << "| 1. Play   | " << endl;
	cout << "| 2. Scores |" << endl;
	cout << "|           |" << endl;
	cout << "| 0. Exit   |" << endl;
	cout << "[-----------]" << endl;
	cin >> op;
	while (0 > op > 2) {
		cout << "[-----------]" << endl;
		cout << "| 1. Play   | " << endl;
		cout << "| 2. Scores |" << endl;
		cout << "|           |" << endl;
		cout << "| 0. Exit   |" << endl;
		cout << "[-----------]" << endl;
		cin >> op;
	}
	return op;
}