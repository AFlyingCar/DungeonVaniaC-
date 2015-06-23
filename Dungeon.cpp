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

bool Dungeon::moveToNextRoom(){
	if(doesHaveNextRoom() && canMoveToNextRoom()){
		m_roomPtr++;
		// Needs Enemy class to be written for this to work
		// Enemy::enemyInRoom=0
		return true;
	}else
		return false;
}

bool Dungeon::doesHaveNextRoom(){
	return !getCurrentRoom()->isBossRoom();
}

bool Dungeon::canMoveToNextRoom(){
	return getCurrentRoom()->canMoveToNextRoom();
}

Room* Dungeon::getCurrentRoom(){
	return m_rooms.at(m_roomPtr);
}

int Dungeon::getRoomPtr(){
	return m_roomPtr;
}

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

void Dungeon::generateRooms(){
	srand(time(NULL));
	int dungeonSize = rand()%MAX_ROOM_AMT+1;
	for(int i = 0; i < dungeonSize; i++){
		m_rooms.push_back(new Room(false));
	}
	m_rooms.push_back(new Room(true));
}

// Generates a random unique name for the dungeon
// Cached for efficiency
void Dungeon::generateRandomName(){
	m_name = "Dungeon";
}
