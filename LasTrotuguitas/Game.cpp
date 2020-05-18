#include "Game.h"
using namespace std;
#include "checkML.h"

bool loadGame(tGame &Game) {
	bool loaded = false;
	ifstream file;
	std::string filename;
	int numBoard, TurtlesFound = 0;
	std::string stringBoard;
	char charBoard;

	cout << " How many players will participate: " << endl;
	cin >> Game.NumberPlayers;
	while ((1 > Game.NumberPlayers) || (Game.NumberPlayers > 4)) {
		cout << "That is an invalid number of player, remember that the maximun is 4 and the minumun is 1" << endl;
		cin >> Game.NumberPlayers;
	}
	file.open("Board.txt");
	if (!file.is_open()) {
		cout << "An error ocurred while trying to open board file " << endl;
	}
	else {
		loaded = true;
		file >> numBoard;
		file.ignore(); // goes directly to the first values i want to get ignoring spaces
		while (numBoard != Game.NumberPlayers) {
			for (int i = 0; i < ROWS; i++) {
				getline(file, stringBoard);
			}
			file >> numBoard;
			file.ignore();
		}

		for (int i = 0; i < ROWS; i++) {
			getline(file, stringBoard);
			for (int j = 0; j < COLUMNS; j++) {
				charBoard = stringBoard.at(j);
				if (charBoard == '#') {
					Game.board[i][j].state = WALL;
				}
				else if (charBoard == '*') {
					Game.board[i][j].state = EMPTY;
				}
				else if (charBoard == '@') {
					Game.board[i][j].state = ICE;
				}
				else if (charBoard == '$') {
					Game.board[i][j].state = GEM;
				}
				else if (charBoard == 'C') {
					Game.board[i][j].state = BOX;
				}
				else {
					Game.board[i][j].state = TURTLE;

					switch (charBoard) {
					case 'U':
						Game.board[i][j].turtle.Direction = NORTH;
						break;
					case 'D':
						Game.board[i][j].turtle.Direction = SOUTH;
						break;
					case 'R':
						Game.board[i][j].turtle.Direction = EAST;
						break;
					case 'L':
						Game.board[i][j].turtle.Direction = WEST;
					}
					TurtlesFound++;
					Game.board[i][j].turtle.number = TurtlesFound;
					Game.PlayerList[TurtlesFound - 1].actual.row = i;
					Game.PlayerList[TurtlesFound - 1].actual.column = j;
				}
			}
		}
	}
	Game.currentturn = 0;
	tCard card;
	for (int i = 0; i < Game.NumberPlayers; i++) {   // Charges name, cards and the hand
		cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << endl;
		cout << "Introduce the Username for the player " << i + 1 << endl;
		cin >> Game.PlayerList[i].name;
		createRandomPack(Game.PlayerList[i].pack); // create a random deck for the player i 
		Game.PlayerList[i].hand.advance = 0;
		Game.PlayerList[i].hand.turnleft = 0;
		Game.PlayerList[i].hand.turnright = 0;
		Game.PlayerList[i].hand.laser = 0;
		Game.PlayerList[i].hand.total = 0;
		for (int j = 0; j < MAX_CARDS_HAND; j++) {
			if (take(Game.PlayerList[i].pack, card)) {
				includeCard(Game.PlayerList[i].hand, card);
			}
		}
	}
	return loaded;
}
void printGame(const tGame &Game) {
	system("cls");
	int colour;
	string tile2show;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			tile2show = tile2string(Game.board[i][j], colour);
			changeColour(colour);
			cout << tile2show;
		}
		cout << endl;
	}
	changeColour(0);
	cout << "\n";

	for (int i = 0; i < Game.NumberPlayers; i++) {
		changeColour(PlayerColour(i + 1));
		if (Game.currentturn == i) {
			cout << "->  ";
		}
		cout << "Player " << i + 1  <<  " "<< Game.PlayerList[i].name << ":";
		changeColour(0);
		cout << " ";

		changeColour(PALETTE[9]);
		cout << "^"; changeColour(0);
		cout << " " << Game.PlayerList[i].hand.advance;

		changeColour(PALETTE[9]);
		cout << "<"; changeColour(0);
		cout << " " << Game.PlayerList[i].hand.turnleft;

		changeColour(PALETTE[9]);
		cout << ">"; changeColour(0);
		cout << " " << Game.PlayerList[i].hand.turnright;

		changeColour(PALETTE[9]);
		cout << "~"; changeColour(0);
		cout << " " << Game.PlayerList[i].hand.laser;
		cout << "\n";
	}
	changeColour(0);
}
void includeCard(tHand &hand, tCard card){
	switch (card) {
	case ADVANCE:
		hand.advance++;
		break;
	case TURNLEFT:
		hand.turnleft++;
		break;
	case TURNRIGHT:
		hand.turnright++;
		break;
	case LASER:
		hand.laser++;
		break;
	}
	hand.total++;
}
std::string tile2string(tTile tile, int &colour){
	string icon;
	switch (tile.state) {
	case BOX:
		icon = "[]";
		colour = PALETTE[3];
		break;
	case GEM:
		icon = "00";

		colour = PALETTE[4];
		break;
	case ICE:
		icon = "**";
		colour = PALETTE[1];
		break;
	case WALL:
		icon = "||";
		colour = PALETTE[2];
		break;
	case EMPTY:
		icon = "  ";
		colour = PALETTE[0];
		break;

	case TURTLE:
		switch (tile.turtle.Direction) {
		case NORTH:
			icon = "^^";
			switch (tile.turtle.number) {
			case 1:
				colour = PALETTE[5];
				break;
			case 2:
				colour = PALETTE[6];
				break;
			case 3:
				colour = PALETTE[7];
				break;
			case 4:
				colour = PALETTE[8];
				break;
			}
			break;
		case SOUTH:
			icon = "vv";
			switch (tile.turtle.number) {
			case 1:
				colour = PALETTE[5];
				break;
			case 2:
				colour = PALETTE[6];
				break;
			case 3:
				colour = PALETTE[7];
				break;
			case 4:
				colour = PALETTE[8];
				break;
			}
			break;
		case EAST:
			icon = ">>";
			switch (tile.turtle.number) {
			case 1:
				colour = PALETTE[5];
				break;
			case 2:
				colour = PALETTE[6];
				break;
			case 3:
				colour = PALETTE[7];
				break;
			case 4:
				colour = PALETTE[8];
				break;
			}
			break;
		case WEST:
			icon = "<<";
			switch (tile.turtle.number) {
			case 1:
				colour = PALETTE[5];
				break;
			case 2:
				colour = PALETTE[6];
				break;
			case 3:
				colour = PALETTE[7];
				break;
			case 4:
				colour = PALETTE[8];
				break;
			}
			break;
		}
	}
	return icon;
}
void changeColour(int colour) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (colour << 4));
}
bool playTurn(tGame &Game) {
	tAction action;
	bool canSteal = true;
	bool ValidSequence = false;
	tDeck NewSequence;
	tKey Key, choice;
	cout << "###########################################" << endl;
	cout << "# What do you want to do this turn?       #" << endl;
	cout << "# Press E if you want to build a sequence #" << endl;
	cout << "# Press S if you want to steal a card     #" << endl;
	cout << "###########################################" << endl;
	choice = readKey();
	if (choice == Getcard) {
		cout << "S : Steal a card" << endl;
		cout << "^^^^^^^^^^^^^^^^^^" << endl;
		action = GET_CARD;
	}
	else if (choice == Sequence) {
		cout << " E : Build a sequence" << endl;
		cout << " ^^^^^^^^^^^^^^^^^^^^"<< endl;
		action = MAKE_MOVE;
	}
	else {
		action = NONE;
	}

	while (action == NONE) {
		cout << "###########################################" << endl;
		cout << "# What do you want to do this turn?       #" << endl;
		cout << "# Press E if you want to build a sequence #" << endl;
		cout << "# Press S if you want to steal a card     #" << endl;
		cout << "###########################################" << endl;
		choice = readKey();
		if (choice == Getcard) {
			action = GET_CARD;
		}
		else if (choice == Sequence){
			action = MAKE_MOVE;
		}
		else {
			action = NONE;
		}
	}

	if (action == GET_CARD) {
		canSteal = getCard(Game);
		if (!canSteal) {
			cout << "There are not enough cards to steal" << endl;
		}
	}
	else if (action == MAKE_MOVE) {
		createEmpty(NewSequence);
		cout << "Please introduce the sequence you want to play: " << endl;
		cout << "_________________________________________________" << endl;
		Key = readKey();
		showKey(Key);
		while (Key != Exit) {
			if (Key != None) {
				NewSequence.list[NewSequence.cardNUM] = new tCard;
				*NewSequence.list[NewSequence.cardNUM] = Key2Card(Key);
				NewSequence.cardNUM++;
			}
				Key = readKey();
				showKey(Key);
		}
		printGame(Game);
		ValidSequence = sequence(Game, NewSequence);

		for (int i = 0; i < NewSequence.cardNUM; i++) {
			delete NewSequence.list[i];
		}
	}
	return ValidSequence;
}
bool getCard(tGame &Game) {
	bool stolen = false;
	tCard Card;
	if (take(Game.PlayerList[Game.currentturn].pack, Card)) {
		stolen = true;
		includeCard(Game.PlayerList[Game.currentturn].hand, Card);
	}
	return stolen;
}

void nextTurn(tGame &Game) {
	if (Game.currentturn < Game.NumberPlayers - 1) {
		Game.currentturn++;
	}
	else {
		Game.currentturn = 0;
	}
}
bool sequence(tGame &Game, tDeck &Sequence) {
	bool Winner = false;
	int i = 0;
	while (i < Sequence.cardNUM && !Winner) {
		switch (*Sequence.list[i]) {
		case ADVANCE:
			Winner = TurtleAdvance(Game);
			Game.PlayerList[Game.currentturn].hand.advance--;
			break;
		case TURNLEFT:
			TurtleTurnLeft(Game);
			Game.PlayerList[Game.currentturn].hand.turnleft--;
			break;
		case TURNRIGHT:
			TurtleTurnRight(Game);
			Game.PlayerList[Game.currentturn].hand.turnright--;
			break;
		case LASER:
			LaserShot(Game);
			Game.PlayerList[Game.currentturn].hand.laser--;
			break;
		}
		Game.PlayerList[Game.currentturn].hand.total--;
		insert(Game.PlayerList[Game.currentturn].pack, *Sequence.list[i]);
		i++;
	}
	return Winner;
}

//KEYS 
tKey readKey() {
	tKey Key;
	int dir;
	cin.sync();
	dir = _getch();
	if (dir == 0xe0) {
		dir = _getch();
		switch (dir) {
		case 72:
			Key = Advance;
			break;
		case 77:
			Key = Right;
			break;
		case 75:
			Key = Left;
			break;
		default:
			Key = None;
			break;
		}
	}
	else if (dir == 32) {
		Key = Laser;
	}
	else if (dir == 13) {
		Key = Exit;
	}
	else if((dir == 83)||(dir == 115)){
		Key = Getcard;
	}
	else if((dir == 69)||(dir == 101)){
		Key = Sequence;
	}
	else {
		Key = None;
	}
	return Key;
}
void showKey(tKey Key) {
	switch (Key) {
	case Advance:
		cout << "^";
		break;
	case Right:
		cout << ">";
		break;
	case Left:
		cout << "<";
		break;
	case Laser:
		cout << "~";
		break;
	case Exit:
		cout << " ";
		break;
	case None:
		cout << " ";
			break;

	}
}
bool TurtleAdvance(tGame &Game) {
	tCoordinate NewCoordinate;

	bool winner = false;
	NewCoordinate = Game.PlayerList[Game.currentturn].actual;
	switch (Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.Direction) {
	case NORTH:
		NewCoordinate.row--;
		break;
	case SOUTH:
		NewCoordinate.row++;
		break;
	case EAST:
		NewCoordinate.column++;
		break;
	case WEST:
		NewCoordinate.column--;
		break;
	}
	if (!(0 > NewCoordinate.column > COLUMNS || 0 > NewCoordinate.row > ROWS)) {
		switch (Game.board[NewCoordinate.row][NewCoordinate.column].state) {
		case EMPTY:
			Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].state = EMPTY;
			Game.board[NewCoordinate.row][NewCoordinate.column].state = TURTLE;
			Game.board[NewCoordinate.row][NewCoordinate.column].turtle.Direction = Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.Direction;
			Game.board[NewCoordinate.row][NewCoordinate.column].turtle.number = Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.number;
			Game.PlayerList[Game.currentturn].actual = NewCoordinate;
			break;
		case BOX:
			tCoordinate BoxCoordinate;
			BoxCoordinate = NewCoordinate;
			switch (Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.Direction) {
			case NORTH:
				BoxCoordinate.row--;
				break;
			case SOUTH:
				BoxCoordinate.row++;
				break;
			case EAST:
				BoxCoordinate.column++;
				break;
			case WEST:
				BoxCoordinate.column--;
				break;
			}
			if (!(0 > BoxCoordinate.column > COLUMNS || 0 > BoxCoordinate.row > ROWS)) {
				if (Game.board[BoxCoordinate.row][BoxCoordinate.column].state == EMPTY) {
					Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].state = EMPTY;
					Game.board[BoxCoordinate.row][BoxCoordinate.column].state = BOX;
					Game.board[NewCoordinate.row][NewCoordinate.column].state = TURTLE;
					Game.board[NewCoordinate.row][NewCoordinate.column].turtle.Direction = Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.Direction;
					Game.board[NewCoordinate.row][NewCoordinate.column].turtle.number = Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.number;
					Game.PlayerList[Game.currentturn].actual = NewCoordinate;
				}
			}
			break;
		case GEM:
			Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].state = EMPTY;
			Game.board[NewCoordinate.row][NewCoordinate.column].state = TURTLE;
			Game.board[NewCoordinate.row][NewCoordinate.column].turtle.Direction = Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.Direction;
			Game.board[NewCoordinate.row][NewCoordinate.column].turtle.number = Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.number;
			Game.PlayerList[Game.currentturn].actual = NewCoordinate;
			winner = true;
			break;
		}
	}
	printGame(Game);
	return winner;
}
void TurtleTurnRight(tGame &Game) {
	switch (Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.Direction) {
	case NORTH:
		Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.Direction = EAST;
		break;
	case EAST:
		Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.Direction = SOUTH;
		break;
	case SOUTH:
		Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.Direction = WEST;
		break;
	case WEST:
		Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.Direction = NORTH;
		break;
	}
	printGame(Game);
}
void TurtleTurnLeft(tGame &Game) {
	switch (Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.Direction) {
	case NORTH:
		Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.Direction = WEST;
		break;
	case EAST:
		Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.Direction = NORTH;
		break;
	case SOUTH:
		Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.Direction = EAST;
		break;
	case WEST:
		Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.Direction = SOUTH;
		break;
	}
	printGame(Game);
}
void LaserShot(tGame &Game) {
	bool obstacle = true;
	tCoordinate LasCoordinate;
	LasCoordinate = Game.PlayerList[Game.currentturn].actual;
	while (obstacle == true) {
		switch (Game.board[Game.PlayerList[Game.currentturn].actual.row][Game.PlayerList[Game.currentturn].actual.column].turtle.Direction) {
		case NORTH:
			LasCoordinate.row--;
			break;
		case SOUTH:
			LasCoordinate.row++;
			break;
		case EAST:
			LasCoordinate.column++;
			break;
		case WEST:
			LasCoordinate.column--;
			break;
		}
		if (0 > LasCoordinate.column > COLUMNS || 0 > LasCoordinate.row > ROWS) {
			obstacle = false;
		}
		else if (Game.board[LasCoordinate.row][LasCoordinate.column].state == ICE) {
			obstacle = false;
			Game.board[LasCoordinate.row][LasCoordinate.column].state = EMPTY;
		}
		else {
			obstacle = false;
		}
	}
	printGame(Game);
}
tCard Key2Card(tKey Key) {
	tCard NewCard;
	switch (Key) {
	case Advance:
		NewCard = ADVANCE;
		break;
	case Left:
		NewCard = TURNLEFT;
		break;
	case Right:
		NewCard = TURNRIGHT;
		break;
	case Laser:
		NewCard = LASER;
		break;
	
	}
	return NewCard;
}
int PlayerColour(int turn) {
	int colour;
	switch (turn) {
	case 1:
		colour = PALETTE[5];
		break;
	case 2:
		colour = PALETTE[6];
			break;
	case 3:
		colour = PALETTE[7];
		break;
	case 4: 
		colour = PALETTE[8];
		break;
	}
	return colour;
}