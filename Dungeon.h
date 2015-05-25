#ifndef _DUNGEON_H_
#define _DUNGEON_H_

#include <vector>

#include "Room.h"

class Dungeon
{
public:
	Dungeon();
	Dungeon(char* newName);
	~Dungeon();

	void generateRooms();
	void generateRandomName();
	bool moveToNextRoom();
	bool doesHaveNextRoom();
	bool canMoveToNextRoom();
	Room* getCurrentRoom();
	int getCRoom();
	void Execute(Player* p);
	char* getName();

private:
	std::vector<Room*> m_rooms;
	const char* m_NAME;
	int m_cRoom;
	const int MAX_AMOUNT_OF_ROOMS = 100;
};

#endif