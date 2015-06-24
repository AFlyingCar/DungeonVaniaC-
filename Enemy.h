#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <string>

class Player;
class Room;

class Enemy{
public:
	static int m_enemyInRoom;
	//Enemy(const Room& r);
	Enemy();
	~Enemy();
	void addHealth(int newHealth);
	void setHealth(int newHealth);
	int getHealth();
	int getDamage();
	std::string getName();
	int getDefense();
	int getMoney();
	void addDefense(int d);
	void defend();
	int damagePlayer(Player* p);
	bool isDead();
protected:
	static int m_count;
	int m_health;
	int m_money;
	std::string m_name;
	int m_defense;
	int m_damage;
	//Room& m_room;

	virtual void generateHealth();
	virtual void generateMoney();
	virtual void generateDamage();
	virtual void generateDefense();
	virtual void generateName();
};

#endif
