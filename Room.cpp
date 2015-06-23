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

/*
Increase the time counter for how many iterations the player has been inside a room
Re-generates enemies if the player has been in the room for too long.
*/
int Room::increaseTime(){
	m_time++;
	if(m_time > 5){
		m_time=0;
		generateRandomEnemies();
	}
	return m_time;
}

/*
Remove an enemy from the room.
*/
Enemy Room::removeEnemy(int index){
	Enemy e = *(m_enemies.at(index));
	m_enemies.erase(m_enemies.begin()+index); // Have to do this because C++ doesn't have erase by element
	return e;
}

/*
Calculates how much gold and how many health potions will be found in a single search by the player.
*/
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

/*
Returns true if and only if there are no enemies left in the room
*/
bool Room::canMoveToNextRoom(){
	return m_enemies.empty();
}

bool Room::isBossRoom(){
	return m_bossRoom;
}

/*
Generates the amount of loot that can be found in a room based on its size.
*/
void Room::generateRandomLoot(){
	int modifier = (isBossRoom() ? 1 : 2);
	srand(time(NULL));
	m_hp_amt = (int)(rand() % (m_roomSize*(5*modifier)));
	m_go_amt = (int)(rand() % (m_roomSize*(100*modifier)));
}

/*
Generates a random between 1 and 5 which determine's the room's size
*/
void Room::generateRandomRoomSize(){
	srand(time(NULL));
	m_roomSize = (int)(rand()%5 + 1);
}

/*
Generates enemies for the room based on its size
*/
void Room::generateRandomEnemies(){
	for(int i = 0; i < getRoomSize(); i++)
		m_enemies.push_back(new Enemy());
}
