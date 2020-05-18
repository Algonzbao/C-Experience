#include "Set.h"
#include "checkML.h"

using namespace std;


void emptySet(tSet &set) {
	set.counter = 0;
}
void fullSet(tSet &set) {
	for (int i = 0; i < SET_SIZE; i++) {
		set.listNum[i] = i + 1;
		set.counter++;
	}
}
bool isIn(const tSet &set, int n) {
	bool exist = false;
	int i = 0;
	if (n != 32) {
		int value = n - ASCIIVALUE;
		while (i < set.counter && !exist) {
			if (value == set.listNum[i]) {
				exist = true;
			}
			i++;
		}
	}
	return exist;
}
void add(tSet &set, int n) {					
	if (!isIn(set,n)) {
		set.listNum[set.counter] = n - ASCIIVALUE;
		set.counter++;
	}
}
void erase(tSet &set, int n) {
	int pos;
	if (set.counter != 1) {
		if (isIn(set, n)) {
			pos = searchPosition(set, n - ASCIIVALUE);

			for (int i = pos + 1; i < set.counter; i++) {
				set.listNum[i - 1] = set.listNum[i];
			}
			set.listNum[set.counter - 1] = 0;
			set.counter--;
		}
	}
}
int searchPosition(const tSet &set, int n) {
	bool wherenum = false;
	int i = 0, pos = 0;
	while (i < set.counter && !wherenum) {
		if (n == set.listNum[i]) {
			pos = i;
			wherenum = true;
		}
		i++;
	}
	return pos;
}
int size(const tSet &set) {
	return set.counter;
}
bool one(const tSet &set, int &n) {
	n = set.listNum[0];
	return set.counter == 1;
}
void display(const tSet &set) {
	for (int i = 0; i < set.counter; i++) {
		cout << set.listNum[i] << endl;
	}
}
