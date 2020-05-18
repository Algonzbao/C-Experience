#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>


const std::string FILENAME1 = "Score.txt";
const int Players = 4;

typedef struct {
	std::string name;
	int score;
}tPlayerScore;

typedef tPlayerScore * tScoreListPtr;

//Array of pointers

typedef struct {
	tScoreListPtr Scores;
	int Counter;
	int capacity;
} tScores;


bool chargeScores(tScores &points);
void saveScores(tScores &points);
void printScores(const tScores &points);
void loadScores(tScores &points, const std::string &name, int newPoints);
void readScore(std::ifstream &file, tPlayerScore &PlayerScore);
void writeScores(std::ofstream &ofile, const tPlayerScore &PlayerScore);
int PlayerPosition(const tScores &points, std::string name);
bool PlayerExists(const tScores &points, std::string name);
int LowestScorePos(const tScores &points, int newPoints);
bool ComparePoints(const tScores &points, int newPoints, int &LowestScore); 
int menuSCORES();
void AlphabeticOrder(tScores &points);
void resize(tScores &points, const int capacity);
void DefaultOrder(tScores &points);
void freeScores(tScores &points);