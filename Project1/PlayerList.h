#include "Player.h"

const int INISIZE = 5;
const std::string PLAYERLISTFILE = "playerlist.txt";

typedef struct {
	tPlayerPtr *player;
	int counter;
	int size;
}tListPlayers;

void create(tListPlayers &list);
bool load(tListPlayers &list);
void display(const tListPlayers &list);
bool save(const tListPlayers &list);
void playerScore(tListPlayers &list, int score);
bool find(const tListPlayers &list, std::string id, int &pos, int ini, int end);
tListPlayers rankSort(tListPlayers &list);
tListPlayers rankID(tListPlayers &list);
void resize(tListPlayers &list);
void free(tListPlayers &list);