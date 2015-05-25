#include <stdio.h>
#include <iostream>

#include "Shop.h"

Shop::Shop(Player* p){
	m_player = p;
}
Shop::~Shop(){ }

char* Shop::menu(){
	printf("%s: enters the shop.", m_player->getName());
	printf("ShopKeeper: What do ya need?");
	printf("0: Exit");
	printf("1: Buy Health Potions");
	printf("2: Upgrade Armour");
	printf("3: Upgrade Weapon");
	printf("Choice");
	int c;
	cin >> c;
	switch(c){
		case 0:
		 return "%s: Leaves the store",m_player->getName();
		case 1:
		 return buyHealth();
		case 2:
		 return buyArmour();
		case 3:
		 return buyDamage();
		default:
		 printf("%d is not a choice.",c);
		 return menu();
	}
}

char* Shop::buyHealth(){
	printf("How many would ya like to buy?");
	printf("Choice:");
	int c;
	cin >> c;
	int count = 0;
	if(count > 0){
		for(int i = 0; i < choice; i++){
			if(m_player->buyPotion())
				count++;
			else
				break;
		}
		return "%s: bought %d potion(s)\n%s's gold: %d", m_player->getName(), count, m_player->getName(), m_player->getMoney();
	}else{
		printf("You can't buy %d potions!",choice);
		return buyHealth();
	}
}

char* Shop::buyArmour(){
	printf("How many times would you like to upgrade?");
	printf("Choice:");
	int c;
	cin >> c;
	int count = 0;
	if(count > 0){
		for(int i = 0; i < choice; i++){
			if(m_player->upgradeArmour());
				count++;
			else
				break;
		}
		return "%s: bought %d upgrade(s)\n%s's gold: %d", m_player->getName(), count, m_player->getName(), m_player->getMoney();
	}else{
		printf("You can't buy %d upgrades!",choice);
		return buyArmour();
	}
}

char* Shop::buyDamage(){
	printf("How many times would you like to upgrade?");
	printf("Choice:");
	int c;
	cin >> c;
	int count = 0;
	if(count > 0){
		for(int i = 0; i < choice; i++){
			if(m_player->upgradeWeapon());
				count++;
			else
				break;
		}
		return "%s: bought %d upgrade(s)\n%s's gold: %d", m_player->getName(), count, m_player->getName(), m_player->getMoney();
	}else{
		printf("You can't buy %d upgrades!",choice);
		return buyDamage();
	}
}
