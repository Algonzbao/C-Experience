#include "Score.h"
using namespace std;
#include "checkML.h"

bool chargeScores(tScores &points) {
	ifstream file;
	string UserName;
	tPlayerScore PlayerData;
	bool Charged;

	file.open("Score.txt");
	if (!file.is_open()) {
		cout << "Could not open Score file" << endl;
		Charged = false;
	}
	else {
		points.capacity = Players;
		points.Counter = 0;
		points.Scores = new tPlayerScore[points.capacity];

		readScore(file, PlayerData);

		while (!file.eof()) {
			if (points.Counter == points.capacity) {
				resize(points, points.capacity);
			}
			points.Scores[points.Counter].name = PlayerData.name;  // Saves into PlayerScores the data saved in PlayerData
			points.Scores[points.Counter].score = PlayerData.score;
			points.Counter++;
			readScore(file, PlayerData);
		}
		Charged = true;
		file.close();
	}
	return Charged;
}
void readScore(ifstream &file, tPlayerScore &PlayerScore) {  // read from istream and copy it to PlayerScore
	file >> PlayerScore.name;
	file >> PlayerScore.score;
}
void saveScores(tScores &points) {
	ofstream ofile;

	ofile.open(FILENAME1);
	if (!ofile.is_open()) {
		cout << "Could´t save any value" << endl;
	}
	else {
		DefaultOrder(points);
		for (int i = 0; i < points.Counter; i++) {
			writeScores(ofile, points.Scores[i]);  // info in ofile and the scores 
		}
		ofile.close();
	}
}
void writeScores(ofstream &ofile, const tPlayerScore &PlayerScore) {
	ofile << PlayerScore.name;
	ofile << " ";
	ofile << PlayerScore.score;
}
void printScores(const tScores &points) {
	for (int i = 0; i < points.Counter; i++) {
		cout << points.Scores[i].name << setw(4) << points.Scores[i].score << endl;
	}
}

void loadScores(tScores &points, const string &name, int newPoints) {

	if (PlayerExists(points, name)) {
		points.Scores[PlayerPosition(points, name)].score += newPoints;

	}
	else {
		if (points.Counter == points.capacity) {
			resize(points, points.capacity);
		}
			points.Scores[points.Counter].name = name;
			points.Scores[points.Counter].score = newPoints;
			points.Counter++;
			DefaultOrder(points);
		}

	}
bool PlayerExists(const tScores &points, string name) {
	int i = 0;
	bool exists = false;
	while (i < points.Counter && name != points.Scores[i].name) {
		i++;
	}
	if (name == points.Scores[i].name) {
		exists = true;
	}
	return exists;
}

int PlayerPosition(const tScores &points, string name) {
	int i = 0;
	while (i < points.Counter && name != points.Scores[i].name) {
		i++;
	}
	return i;
}
bool ComparePoints(const tScores &points, int newPoints, int &LowestScore) {
	int i = 0;
	bool comp = false;
	while (newPoints <= points.Scores[i].score && i < points.Counter) {
		i++;
	}
	if (newPoints > points.Scores[i].score) {
		LowestScore = points.Scores[i].score;
		comp = true;
	}
	return comp;
}
int LowestScorePos(const tScores &points, int newPoints) {
	int i = 0;
	while (newPoints != points.Scores[i].score && i < points.Counter) {
		i++;
	}
	return i;
}

int menuSCORES() {
	int opt;
	cout << "1. Alphabetic order according to the Player´s name " << endl;
	cout << "2. Default" << endl;
	cin >> opt;
	while (1 > opt > 2) {
		cout << "1. Alphabetic order according to the Player´s name " << endl;
		cout << "2. Default" << endl;
		cin >> opt;
	}
	return opt;
}
void resize(tScores &points, int capacity) {
	int NewSize = capacity + 4;
	tScoreListPtr aux;
	aux = new tPlayerScore[points.capacity];
	for (int i = 0; i < capacity; i++) {
		points.Scores[i] = aux[i];
	}
	points.Scores = new tPlayerScore[NewSize];
	for (int i = 0; i < capacity; i++) {
		aux[i] = points.Scores[i];
	}
	delete [] aux;
	capacity = NewSize;
}

void AlphabeticOrder(tScores &points) {
	tScoreListPtr TEMP;
	TEMP = new tPlayerScore[points.capacity];

	for (int i = 0; i < points.Counter - 1; i++) {
		for (int j = points.Counter - 1; j > 1; j--) {
			if (points.Scores[j].name < points.Scores[j - 1].name) {
				TEMP[j - 1] = points.Scores[j];
				TEMP[j] = points.Scores[j - 1];
			}
		}
	}
	for (int i = 0; i < points.Counter; i++) {
		cout << points.Scores[i].name << setw(5) << points.Scores[i].score << endl;
	}
}
void DefaultOrder(tScores &points) {
	tPlayerScore auxiliar;
	string auxiliar2;
	for (int i = 0; i < points.Counter - 1; i++) {
		for (int j = points.Counter - 1; j > 1; j--) {
			if (points.Scores[j].score > points.Scores[j - 1].score) {
				auxiliar = points.Scores[j];
				points.Scores[j] = points.Scores[j - 1];
				points.Scores[j - 1] = auxiliar;
			}
			if (points.Scores[j].score == points.Scores[j - 1].score) {
				if(points.Scores[j].name < points.Scores[j - 1].name) {
					auxiliar2 = points.Scores[j].name;
					points.Scores[j].name = points.Scores[j - 1].name;
					points.Scores[j - 1].name = auxiliar2;
				}
			}
		}
	}

}
void freeScores(tScores & points) {
	delete[] points.Scores;
	points.Scores = nullptr;
}



