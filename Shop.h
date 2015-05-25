#ifndef _SHOP_H_
#define _SHOP_H_
#include "Player.h"

class Shop{
 public:
	Shop(Player* p);
	~Shop();	
	char* menu();
 private:
	Player* m_player;

	char* buyHealth();
	char* buyArmour();
	char* buyDamage();
};
#endif

