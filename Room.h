#include <vector>

class Room
{
public:
	Room();
	~Room();

	int increaseTime();
	Enemy* removeEnemy(int index);
	int* loot();
	int getRoomSize();
	std::vector<Enemy*> getEnemies();
	Enemy* getEnemy(int index);
	int getEnemyAmount();
	bool canMoveToNextRoom();
	bool isBossRoom();

private:
	int m_hpAmt;
	int m_goldAmt;
	int m_size;
	int m_time;
	std::vector<Enemy*> m_enemies;
	bool m_bossRoom;
	
	void generateRandomLoot();
	void generateRandomRoomSize();
	void generateRandomEnemies();
};
