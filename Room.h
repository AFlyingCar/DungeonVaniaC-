#ifndef _ROOM_H_
#define _ROOM_H_

#include <vector>

class Enemy;

class Room{
public:
	Room(bool bossRoom);
	~Room();
	int increaseTime(); 
	Enemy removeEnemy(int index);
	int* loot();
	int getRoomSize();
	std::vector<Enemy*> getEnemies();
	Enemy* getEnemy(int index);
	int getEnemyAmount();
	bool canMoveToNextRoom();
	bool isBossRoom();
private:
	int m_hp_amt;
	int m_go_amt;
	int m_roomSize;
	int m_time;
	std::vector<Enemy*> m_enemies;
	bool m_bossRoom;

	void generateRandomLoot();
	void generateRandomRoomSize();
	void generateRandomEnemies();
};

#endif
