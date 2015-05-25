#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Room.h"
#include "Player.h"

class Enemy
{
public:
	static int enemyInRoom;

	Enemy(Room* r);
	~Enemy();
	
	void addHealth(int newHealth);
	void setHealth(int newHealth);
	int getHealth();
	int getDamage();
	char* getName();
	int getDefense();
	int getMoney();
	void addDefense();
	void defend();
	int damagePlayer(Player* p);
	bool isDead();

	static float FastInvSqrt(float x);

protected:
	static int m_count = 0;
	int m_money;
	int m_damage;
	int m_defense;
	char* m_name;
	Room* room;
	void generateHealth();
	void generateMoney();
	void generateDefense();
	void generateDamage();
	void generateName();
private:
	int health;
};

#endif
