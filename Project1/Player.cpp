#include "Player.h"
#include "checkML.h"
#include <iostream>
#include <string>
using namespace std;

string toString(const tPlayer &player) {
	return player.name + " " + to_string(player.score);
}
void modifyPlayer(tPlayer & player, int score) {
	player.score += score;
}
bool operator<(const tPlayer &opLeft, const tPlayer &opRight) {
	bool smaller = false;
	if (opLeft.name < opRight.name) {
		smaller = true;
	}
	return smaller;
}
bool smaller(const tPlayer &p1, const tPlayer &p2) {
	bool isSmaller = false;
	if (p1.score < p2.score) {
		isSmaller = true;
	}
	else if (p1.score == p2.score) {
		if (p2 < p1) {
			isSmaller = true;
		}
	}
	return isSmaller;
}
