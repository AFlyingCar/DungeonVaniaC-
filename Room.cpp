#include "Room.h"
#include "Enemy.h"

Room::Room(bool bossRoom):
	m_hp_amt(0),
	m_go_amt(0),
	m_roomSize(0),
	m_time(0),
	m_enemies(),
	m_bossRoom(bossRoom)
{
	if(m_bossRoom){
		// TODO - Uncomment this when the Boss class has been added
		// m_enemies.push_back(new Boss());
		m_roomSize = 6;
	}else{
		generateRandomRoomSize();
		Enemy::m_enemyInRoom = m_roomSize*2;
		generateRandomEnemies();
	}
	generateRandomLoot();
}

Room::~Room(){ }

int Room::increaseTime(){
	m_time++;
	if(m_time > 5){
		m_time=0;
		generateRandomEnemies();
	}
	return m_time;
}

Enemy Room::removeEnemy(int index){
	Enemy e = *(m_enemies.at(index));
	m_enemies.erase(m_enemies.begin()+index); // Have to do this because C++ doesn't have erase by element
	return e;
}

int* Room::loot(){
	if(m_hp_amt == 0 && m_go_amt == 0) return NULL;
	srand(time(NULL));
	float hp_looted = (rand()%100)/100.0f;
	float go_looted = (rand()%100)/100.0f;
	int looted[2] = {(int)(hp_looted*m_hp_amt),(int)(go_looted*m_go_amt)};
	// int* looted = {(int)(hp_looted*m_hp_amt),(int)(go_looted*m_go_amt)};
	m_hp_amt -= looted[0];
	m_go_amt -= looted[1];
	return looted;
}

int Room::getRoomSize(){
	return m_roomSize;
}

std::vector<Enemy*> Room::getEnemies(){
	return m_enemies;
}

Enemy* Room::getEnemy(int index){
	return m_enemies.at(index);
}

int Room::getEnemyAmount(){
	return m_enemies.size();
}

bool Room::canMoveToNextRoom(){
	return m_enemies.empty();
}

bool Room::isBossRoom(){
	return m_bossRoom;
}

void Room::generateRandomLoot(){
	int modifier = (isBossRoom() ? 1 : 2);
	srand(time(NULL));
	m_hp_amt = (int)(rand() % (m_roomSize*(5*modifier)));
	m_go_amt = (int)(rand() % (m_roomSize*(100*modifier)));
}

void Room::generateRandomRoomSize(){
	srand(time(NULL));
	m_roomSize = (int)(rand()%5 + 1);
}

void Room::generateRandomEnemies(){
	for(int i = 0; i < getRoomSize(); i++)
		m_enemies.push_back(new Enemy());
}
