#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <vector>

#include "DungeonVania.h"

#include "Item.h"

class Player{
public:
	Player();
	~Player();
	std::string getName();
	int getMoney();
	int getHealth();
	int addMoney(int);
	int addHealth(int);
	int setMoney(int);
	int setHealth(int);
	int getArmourAbsorption();
	std::vector<Item*> getInventory();
protected:
	void setName(std::string newName);
private:
	std::string m_name;
	int m_money;
	int m_health;
	std::vector<Item*> m_inventory;

	void resetInventory();
public:
	friend void createNewPlayer(Player*);
};
#endif
