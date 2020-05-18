#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "Card.h"
#include <Windows.h>

const std::string FILENAME = "Board.txt";
const int MAX_ICE = 12;
const int NUMBER_OF_TILE_TYPES = 6;
const int MAX_PLAYERS = 4;
const int COLUMNS = 8;
const int ROWS = 8;

const int PALETTE[NUMBER_OF_TILE_TYPES + 4] = { 1, 11, 7, 4, 12, 5, 13, 9, 10, 3 };


typedef enum tTileState { EMPTY, ICE, WALL, BOX, GEM, TURTLE };
typedef enum tAction { MAKE_MOVE, GET_CARD, NONE };
typedef enum tKey { Advance, Right, Left, Laser, None, Exit,Sequence, Getcard};


typedef enum tDir { NORTH, SOUTH, EAST, WEST };

typedef struct {
	int number;
	tDir Direction;
} tTurtle;

typedef struct {
	tTileState state;
	tTurtle turtle;
} tTile;

typedef struct {
	int row;
	int column;
} tCoordinate;

typedef struct {
	int advance;
	int turnleft;
	int turnright;
	int laser;
	int total;
} tHand;

typedef struct {
    std::string name;
	tDeck pack;
	tHand hand;
	tCoordinate actual;
} tPlayer;

typedef tTile tBoard[COLUMNS][ROWS];

typedef struct {
	int NumberPlayers;
	int currentturn;
	tPlayer PlayerList[MAX_PLAYERS];
	tBoard board;
} tGame;

bool loadGame(tGame &Game); // nombre del fivhero y numero de players. Inicializa los mazos
void printGame(const tGame &Game); // estado actual del juego // 2 for que muestran una casilla
bool playTurn(tGame &Game); // lee turno y ejecuta, el bool hace dice si llega a la joya o no  //pide c o s y llama a sequence o get card
bool getCard(tGame &Game);
bool sequence(tGame &Game, tDeck &Sequence); // ejecuta la secuencia y consume las cartas
void nextTurn(tGame &Game); // Next jugador  
							//bool endGame(tGame &Game); // comprobar partida finalizada
void includeCard(tHand &Hand, tCard Card); //incluye una nueva carta en la mano
std::string tile2string(tTile tile, int &colour);
void changeColour(int colour);
//KEYS
tKey readKey();
void showKey(tKey Key);
bool TurtleAdvance(tGame &Game);
void TurtleTurnRight(tGame &Game);
void TurtleTurnLeft(tGame &Game);
void LaserShot(tGame &Game);
tCard Key2Card(tKey Key);
int PlayerColour(int turn);