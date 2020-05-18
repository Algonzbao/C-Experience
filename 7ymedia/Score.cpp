#include <fstream>
#include <string>
using namespace std;

const double HALF = 0.5;
const int SEVEN = 7;

float calculateScore(int card) {
	float score;
	if (card > SEVEN) {
		score = HALF;
	}
	else {
		score = card;
	}
	return score;
}