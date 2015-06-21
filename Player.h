#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <vector>
#include "DungeonVania.h"

class Player{
public:
	Player();
	~Player();
	std::string getName();
protected:
	void setName(std::string newName);
private:
	std::string m_name;
	int m_money;
	int m_health;
	//std::vector<Item> m_inventory;

	void resetInventory();
public:
	friend void createNewPlayer(Player*);
};
#endif
