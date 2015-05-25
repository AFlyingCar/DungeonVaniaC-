#include "Room.h"

Room::Room(bool isBoss):
	m_hpAmt(0),
	m_goldAmt(0),
	m_size(0),
	m_time(0),
	m_enemies(NULL),
	m_bossRoom(isBoss)
{
	if(m_bossRoom){
		m_enemies = new std::vector<Enemy*>();
		m_enemies.push_back(new Boss(this));
		m_size = 6;
	}else{
		generateRandomRoomSize();
		m_enemies = new std::vector<Enemy*>();
		Enemy::enemyInRoom = m_size*2;
		generateRandomEnemies();
	}
	generateRandomLoot();
	m_time = 0;
}

Room::~Room(){ }

int Room::increaseTime(){
	m_time++;
	if(m_time > 5){
		m_time = 0;
		generateRandomEnemies();
	}
	return m_time;
}

void Room::generateRandomLoot(){
	srand(time(NULL));

	if(!isBossRoom()){
		m_hpAmt = rand()%(m_size*5);
		m_goldAmt = rand()%(m_size*100);
	}else{
		m_hpAmt = rand()%(m_size*10);
		m_goldAmt = rand()%(m_size*200);
	}
}

void Room::generateRandomRoomSize(){
	srand(time(NULL));
	m_size = rand()%5 + 1;
}

void Room::generateRandomEnemies(){
	for(int i = 0; i < getRoomSize(); i++){
		m_enemies.push_back(new Enemy(this));
	}
}

int* Room::loot(){
	srand(time(NULL));

	if(m_hpAmt == 0 && m_goldAmt == 0) return NULL;

	double hp_looted = rand();
	double gold_looted = rand();
	int r[2] = {(int)(m_hpAmt*hp_looted),(int)(m_goldAmt*gold_looted)};
	m_hpAmt -= r[0];
	m_goldAmt -= r[1];
	return r;
}

int Room::getRoomSize(){
	return m_size;
}

std::vector<Enemy*> Room::getEnemies(){
	return m_enemies;
}

Enemy* Room::getEnemy(int index){
	return m_enemies[index];
}

int getEnemyAmount(){
	return m_enemies.size();
}

bool Room::canMoveToNextRoom(){
	return m_enemies.empty();
}

bool Room::isBossRoom(){
	return m_bossRoom;
}
