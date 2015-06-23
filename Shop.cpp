#include <iostream>

#include "Shop.h"
#include "Player.h"

Shop::Shop(Player* p){
	m_player = p;
}

// Don't actually delete anything, because player is supposed to delete itself later
Shop::~Shop(){ }

std::string Shop::menu(){
	std::cout << m_player->getName() << ": enters the shop." << std::endl;
	std::cout << "Shopkeeper: What do ya need?" << std::endl;
	std::cout << "0. Exit" << std::endl;
	std::cout << "1. Buy Health Potions" << std::endl;
	std::cout << "2. Upgrade Armour" << std::endl;
	std::cout << "3. Upgrade Weapon" << std::endl;
	std::cout << "Choice: ";
	int choice;
	std::cin >> choice;
	switch(choice){
		case 0:
		 return m_player->getName() + ": Leaves the store.";
		case 1:
		 return buyHealth();
		case 2:
		 return buyArmour();
		case 3:
		 return buyDamage();
		default:
		 std::cout << "Invalid choice: " << choice << std::endl;
		 return menu();
	}
}

std::string Shop::buyHealth(){
	std::cout << "How many potions would you like to buy?" << std::endl;
	std::cout << "Amount: ";
	int amt;
	std::cin >> amt;
	if(amt > 0){
		int count=0;
		for(int i = 0; i < amt; i++){ 
			if(m_player->buyPotion())
				count++;
			else
				break;
		}
		std::string r_message = m_player->getName() + ": bought ";
		r_message += count;
		r_message += " potion(s)\n" + m_player->getName() + "'s gold: ";
		r_message += m_player->getMoney();
		return r_message;
		//return m_player->getName() + ": bought " + count + " potion(s)\n" + player->getName() + "'s gold.: " + m_player->getMoney();
	}else{
		std::cout << "You can't buy " << amt << " potions!" << std::endl;
		return buyHealth();
	}
}

std::string Shop::buyArmour(){
}

std::string Shop::buyDamage(){
}
