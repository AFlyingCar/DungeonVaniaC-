/*
 * Tyler Robbins
 * Player
 * 5/20/15
 * Defines the player class
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdlib.h>
#include <time.h>
#include <vector>

class Player{
 public:
	Player(char* newName);
	~Player();
	
	char* getName();
	std::vector<Item*> getInventory();
	Item setInventoryItem(int index, Item element);
	int getMoney();
	void setMoney(int emoe);
	void addMoney(int emone);
	int getHealth();
	void setHealth(int newHealth);
	void addHealth(int newHealth);
	int getArmourAbsorption();
	int damageEnemy(Enemy* e);
	char* usePotion();
	bool buyPotion();
	bool upgradeArmour();
	bool upgradeWeapon();
	void setInventory(std::vector<Item*> inv);
	bool isDead();
	void searchRoom(Room* r);

 private:
 	void resetInventory();

	std::vector<Item*> m_inventory;
	const char* m_NAME;
	int m_money;
	int m_health;
};

#endif
