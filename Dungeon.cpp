#include <time.h>
#include <stdlib.h>

#include "Dungeon.h"
#include "Room.h"
#include "Player.h"
#include "Enemy.h"

const int Dungeon::MAX_ROOM_AMT = 100;

Dungeon::Dungeon():
	m_rooms(),
	m_name(""),
	m_roomPtr(0)
{
	generateRandomName();
	generateRooms();
}

Dungeon::Dungeon(std::string newName):
	m_rooms(),
	m_name(newName),
	m_roomPtr(0)
{
	generateRooms();
}

Dungeon::~Dungeon(){ }

/*
Increments the room counter by one and returns true if and only if there is another room to go to. False otherwise.
PreCondition: rooms has been initialized and filled
PostCondition: c_rooom = c_room + 1
*/
bool Dungeon::moveToNextRoom(){
	if(doesHaveNextRoom() && canMoveToNextRoom()){
		m_roomPtr++;
		// Needs Enemy class to be written for this to work
		// Enemy::enemyInRoom=0
		return true;
	}else
		return false;
}

/*
Returns true if and only if there is another room to go to.
PreCondition: rooms has been initialized and filled
*/
bool Dungeon::doesHaveNextRoom(){
	return !getCurrentRoom()->isBossRoom();
}

/*
Returns true if and only if the player can move to next room
PreCondition: Current room is not null
*/
bool Dungeon::canMoveToNextRoom(){
	return getCurrentRoom()->canMoveToNextRoom();
}

/*
Returns the current room that is pointed to by c_room
PreCondition: rooms has been initialized and filled
*/
Room* Dungeon::getCurrentRoom(){
	return m_rooms.at(m_roomPtr);
}

int Dungeon::getRoomPtr(){
	return m_roomPtr;
}

/*
Performs actions for each enemy in the current room. Assumes that the player has already performed an action.
PreCondition: rooms is not null, p is not null
*/
void Dungeon::Execute(Player *p){
	Room* r = getCurrentRoom();
	if(canMoveToNextRoom() && !r->isBossRoom()){
		r->increaseTime();
		return;
	}

	for(int i = 0; i < r->getEnemies().size(); i++){
		Enemy* e = r->getEnemies().at(i);
		if(e->isDead()){
			r->removeEnemy(i);
			continue;
		}
		srand(time(NULL));
		int action = rand()%2;
		switch(action){
			int d;
			case 0:
			 d = e->damagePlayer(p);
			 std::cout << "Enemy " << (i+1) << " attacked " << p->getName() << " for " << d << " damage!" << std::endl;
			 break;
			case 1:
			 if(r->isBossRoom()) break;
			 e->defend();
			 std::cout << "Enemy " << (i+1) << " defended itself!" << std::endl;
			 break;
		}
	}
}

std::string Dungeon::getName(){
	return m_name;
}

/*
Generates a random number of rooms in the dungeon, from 1 to the maximum
PreCondition: rooms has been initialized
PostCondition: rooms is filled with a random number of rooms, and has a boss room at the end
*/
void Dungeon::generateRooms(){
	srand(time(NULL));
	int dungeonSize = rand()%MAX_ROOM_AMT+1;
	for(int i = 0; i < dungeonSize; i++){
		m_rooms.push_back(new Room(false));
	}
	m_rooms.push_back(new Room(true));
}

/*
Generates a random unique name for the dungeon.
PostCondition: NAME = a random name that has not been used before.
*/
void Dungeon::generateRandomName(){
	m_name = "Dungeon";
}
