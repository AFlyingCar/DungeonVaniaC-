#ifndef _SHOP_H_
#define _SHOP_H_

#include <string>

class Player;

class Shop{
public:
	Shop(Player* p);
	~Shop();
	std::string menu();
private:
	Player* m_player;
	std::string buyHealth();
	std::string buyArmour();
	std::string buyDamage();
};

#endif
