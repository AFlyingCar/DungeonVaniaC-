#include <time.h>
#include <stdlib.h>

#include "Dungeon.h"

Dungeon::Dungeon():
	m_rooms(NULL),
	m_NAME(NULL),
	m_cRoom(0)
{
	m_rooms = new std::vector<Room*>();	
	generateRandomName();
	generateRooms();
}

Dungeon::Dungeon(char* newName):
	m_rooms(NULL),
	m_NAME(newName),
	m_cRoom(0)
{
	generateRooms();
}

Dungeon::~Dungeon(){ }

void Dungeon::generateRooms(){
	srand(time(NULL));
	int dungeon_size = rand()%MAX_AMOUNT_OF_ROOMS + 1;

	Room* r;
	for(int i = 0; i < dungeon_size; i++){
		r = new Room(false);
		m_rooms.push_back(r);
	}
	r = new Room(true);
	m_rooms.push_back(r);
}

void Dungeon::generateRandomName(){
	m_NAME = "Dungeon";
}

bool Dungeon::moveToNextRoom(){
	if(doesHaveNextRoom() && canMoveToNextRoom()){
		m_cRoom++;
		Enemy::enemyInRoom = 0;
		return true;
	}
	return false;
}

bool Dungeon::doesHaveNextRoom(){
	return !getCurrentRoom()->isBossRoom();
}

bool Dungeon::canMoveToNextRoom(){
	return getCurrentRoom()->canMoveToNextRoom();
}

Room* Dungeon::getCurrentRoom(){
	return m_rooms[m_cRoom];
}

int Dungeon::getCRoom(){
	return m_cRoom;
}

void Dungeon::Execute(Player* p){
	Room* r = getCurrentRoom();
	if(canMoveToNextRoom() && !r->isBossRoom()){
		r->increaseTime();
		return;
	}

	for(int i = 0; i < r->getEnemies().size(); i++){
		srand(time(NULL));
		Enemy* e = r->getEnemies()[i];

		if(e->isDead()){
			r->removeEnemy(i);
			continue;
		}
		int action = rand()%2;

		switch(action){
			case 0:
			 int d = e->damagePlayer(p);
			 printf("Enemy %d attacked %s for %d damage!\n", (i+1), p->getName(), d);
			 break;
			case 1:
			 if(r->isBossRoom()) break;
			 e->defend();
			 printf("Enemy %d defended itself!\n", (i+1));
			 break;
		}

	}
}

char* Dungeon::getName(){
	return m_NAME;
}
