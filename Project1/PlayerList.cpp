#include "PlayerList.h"
#include "checkML.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void create(tListPlayers &list) {
	list.counter = 0;
	list.size = INISIZE;
	list.player = new tPlayerPtr[list.size];
	for (int i = 0; i < list.size; i++) {
		list.player[i] = new tPlayer;
	}
}
bool load(tListPlayers &list) {
	bool loaded = false;
	
	ifstream file;
	file.open(PLAYERLISTFILE);
	if (file.is_open()) {
		while (!file.eof()) {
			if (list.counter == list.size) {
				resize(list);
			}
				file >> list.player[list.counter]->name;
				file >> list.player[list.counter]->score;
				list.counter++;	
		}
		list = rankSort(list);
		loaded = true;
		file.close();
	}
	else {
		cout << "Couldnt open the PlayerList text file" << endl;
	}
	return loaded;
}
void display(const tListPlayers &list) {
	for (int i = 0; i < list.counter; i++) {
		cout << "Player Name= " << list.player[i]->name << "     Player Score= " << list.player[i]->score << endl;
	}
}
bool save(const tListPlayers &list) {
	bool saved = false;
	ofstream file;
	file.open(PLAYERLISTFILE);
	if (file.is_open()) {
		for (int i = 0; i < list.counter; i++) {
			file << list.player[i]->name;

			file << setw(9) << list.player[i]->score;
		}
		saved = true;
	}
	else {
		cout << "Couldnt open the file in order to save the data " << endl;
	}
	return saved;
}
void playerScore(tListPlayers &list, int score) {
	string idname;

	int pos = -1;
	cout << "Please introduce your ID" << endl;
	cin >> idname;
	if (find(list, idname, pos, 0, list.counter)) {
		list.player[pos]->score += score;
		list = rankSort(list);
	}
	else {
		if (list.counter == list.size) {
			resize(list);
		}
		list.player[list.counter]->name = idname;
		list.player[list.counter]->score = score;
		list.counter++;
		list = rankSort(list);
	}
}
bool find(const tListPlayers &list, string id, int &pos, int ini, int end) {
	bool found = false;
	int half;
	if (ini <= end) {
		half = (ini + end) / 2;
		if (id < list.player[half]->name) {
			found = find(list, id, pos, ini, half - 1);
		}
		else if (list.player[half]->name < id) {
			found = find(list, id, pos, half + 1, end);
		}
		else {
			pos = half;
			found = true;
		}
	}
	else {
		pos = ini;
		found = false;
	}
	return found;
}
tListPlayers rankSort(tListPlayers &list) {
	tPlayerPtr auxplayer;
	int j;
	for (int i = 0; i < list.counter; i++) {
		auxplayer = list.player[i];
		j = i;
		while ((j > 0) && (smaller(*auxplayer, *list.player[j-1]))) {
			list.player[j] = list.player[j - 1];
			j--;
		}
		list.player[j] = auxplayer;
	}
	return list;
}
tListPlayers rankID(tListPlayers &list) {
	tPlayerPtr auxplayer;
	int j;
	for (int i = 0; i < list.counter; i++) {
		auxplayer = list.player[i];
		j = i;
		while ((j > 0) && (auxplayer->name < list.player[j - 1]->name)) {
			list.player[j] = list.player[j - 1];
			j--;
		}
		list.player[j] = auxplayer;
	}

	return list;
}
void resize(tListPlayers &list) {
	list.size = list.size * 2;
	tPlayerPtr* aux = new tPlayerPtr[list.size];
	for (int j = 0; j < list.size; j++) {
		aux[j] = new tPlayer;
	}
	for (int i = 0; i < list.counter; i++) {
		aux[i] = list.player[i];
	}
	delete[] list.player;
	list.player = aux;
	aux = nullptr;
}
void free(tListPlayers &list) {
	delete[] list.player;
	list.player = nullptr;
	list.counter = 0;
	list.size = 0;
}