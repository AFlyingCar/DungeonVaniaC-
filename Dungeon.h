/*
 * Header file for Dungeon class.
*/
#ifndef _DUNGEON_H_
#define _DUNGEON_H_

#include <vector>
#include <string>

class Room;
class Player;

//TODO - Add a friend declaration for setName to the SaveGameUtils
class Dungeon{
public:
	Dungeon();
	Dungeon(std::string newName);
	~Dungeon();
	bool moveToNextRoom();
	bool doesHaveNextRoom();
	bool canMoveToNextRoom();
	Room* getCurrentRoom();
	int getRoomPtr();
	void Execute(Player* p);
	std::string getName();
private:
	std::vector<Room*> m_rooms;
	std::string m_name;
	int m_roomPtr;
	static const int MAX_ROOM_AMT;
	void generateRooms();
	void generateRandomName();
protected:
	void setName();
};

#endif
