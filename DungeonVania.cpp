/*
 * Tyler Robbins
 * 5/20/15
 * DungeonVania
 * Main class
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "Player.h"
#include "SaveGameUtils.h"
#include "Dungeon.h"
#include "Shop.h"

const long MAGIC = 0x57ddec8c;

Player* player;
Dungeon* dungeon;
Shop* shop;

int main(){
	if(SaveGame::doesFileExist()){
		printf("A save file exists, would you like to load it? (yes/no): ");
		if(yesNo())
			player = SaveGame::load();
		else
			createNewPlayer();
	}else
		createNewPlayer();

	shop = new Shop(player);

	printf(player->getName() + ": starts in the town\n");
	printf(player->getName() + ": checks their pockets and finds " + player->getMoney() + " gold\n");
	printf("0. Go to Bed\n");
	printf("1. Go to the nearby dungeon\n");
	printf("2. Go to the store\n");
	printf("3. Check Inventory\n");
	printf("4. Save Game\n");
	printf("Choice: ");
	int intPut;
	cin >> intPut;

	getMenu(intPut);

	while(intPut != 0){
		getMenuText();
		cin >> intPut;
		getMenu(intPut);
	}
}

void createNewPlayer(){
	printf("Name: ");
	char* name;
	std::cin >> name;
	player = new Player(name);
}

bool yesNo(){
	char* yn = "";
	while(true){
		cin >> yn;
		// Add code here to compare yn to yes, y, ye
		// Add code here to compare yn to no, n
	}
}

void getMenuText(){
	printf("0. Go to Bed\n");
	printf("1. Go to Nearby Dungeon\n");
	printf("2. Go to Store\n");
	printf("3. Check Inventory\n");
	printf("4. Save Game\n");
	printf("Choice: ");
}

void printPlayerInventoryWithFormatting(Player* p){
	std::vector<Item*> inv = p->getInventory();
	Item wep = inv[2];
	Item arm = inv[1];
	Item pot = inv[0];

	int health = p->getHealth();
	int money = p->getMoney();

	printf("Name: %s\n", p->getName());
	printf("Health: %d\n", health);
	printf("Money: %dg\n", money);

	printf("Weapon Tier: %d\n", wep->getItemAttribute("TIER"));
	printf("Weapon damage: %d to %d\n", wep->getItemAttribute("MIN_DAMAGE"), wep->getItemAttribute("MAX_DAMAGE"));
	printf("Armour Tier: %d\n", arm->getItemAttribute("TIER"));
	printf("Armour Defense: %d\n", arm->getItemAttribute("DEFENSE"));
	printf("Amount of Potions: %d\n", pot->getItemAttribute("AMOUNT"));
}

void getMenu(int choice){
	if(choice == 1)
		goToDungeon();
	else if(choice == 2){
		printf("%s: walks to the nearby store.", player->getName());
		goToStore();
	}else if(choice == 3)
		printPlayerInventoryWithFormatting();
	else if(choice == 4){
		if(SaveGame::doesFileExist()){
			printf("A save file already exists, are you sure you would like to overwrite it? (yes/no) ");
			if(!yesNo())
				return;
		}
		printf("Saving Game...\n");
		SaveGame::save(player);
	}else if(choice == 0)
		endGame();
	else
		printf("%d is not a valid choice!\n",choice);
}

void endGame(){
	// Deconstruct the pointers, then force-quit.
	// Because fuck memory leaks
	delete player;
	delete dungeon;
	delete shop;
	std::exit();
}

void goToDungeon(){
	printf("%s: walks to the nearby dungeon.\n", p->getName());
	dungeon = new Dungeon();
	std::vector<Enemy*> enemies;
	int choice = -1;

	while(choice != 0 || dungeon->canMoveToNextRoom()){
		enemies = dungeon->getCurrentRoom()->getEnemies();
		if(enemies.size() > 0)
			printf("%s: encounters %d enemies.\n", p->getName(), enemies.size());

		for(int i = 0; i < enemies.size(); i++){
			printf("%s %d's health: %d\t",enemies[i]->getName(),i,enemies[i]->getHealth());
			printf("Defense: %d\t",enemies[i]->getDefense());
			printf("Damage: %d\n", enemies[i]->getDamage());
		}

		printf("%s's health: %d\n", player->getName(),player->getHealth());
		printf("%s's damage: %d to %d\n", player->getName(),player->getInventory()[2]->getItemAttribute("MIN_DAMAGE"),player->getInventory()[2]->getItemAttribute("MIN_DAMAGE"));

		if(dungeon->canMoveToNextRoom()){
			printf("1. Search room\n");
			printf("2. Check Inventory\n");
			printf("3. Use Items\n");
			printf("4. Move to next room\n");
			printf("0. Escape\n");
		}else{
			printf("1. Attack\n");
			printf("2. Check Inventory\n");
			printf("3. Use Items\n");
			printf("4. Move to next room\n");
			printf("0. Escape\n");
		}

		printf("Choice: ");
		int intPut;
		cin >> intPut;
		if(intPut == 1){
			if(dungeon->canMoveToNextRoom())
				player->searchRoom(dungeon->getCurrentRoom());
			else{
				if(enemies.size() > 1){
					printf("Which enemy would you like to attack?\n");
					for(int i = 0; i < enemies.size(); i++)
						printf("Enemy %d\t",i+1);

					printf("\nChoice: ");
					cin >> intPut;
					intPut--;

					int damageTaken = player->damageEnemy(enemies[intPut]);
					printf("%s %d: took %d damage\n", enemies[intPut]->getName(),intPut+1,damageTaken);
					if(enemies[intPut]->isDead())
						printf("%s %d died!\n", enemies[intPut]->getName(),intPut+1);
				}else{
					int damageTaken = player->damageEnemy(enemies[0]);
					printf("%s 1: took %d damage\n", damageTaken);
					if(enemies[0]->isDead())
						printf("%s 1 died!\n", enemies[0]->getName());
				}
			}
		}else if(intPut == 2){
			printPlayerInventoryWithFormatting();
			continue;
		}else if(intPut == 3){
			printPlayerInventoryWithFormatting();
			printf("How many potions would you like to use: ");
			cin >> intPut;
			for(int i=0; i < intPut; i++)
				player->usePotion();
		}else if(intPut == 4){
			if(dungeon->moveToNextRoom())
				printf("%s moves on from room %d, and ventures further into the dungeon.\n", player->getName(), (dungeon->getCRoom()-1));
			else
				printf("Cannot move to the next room because there are enemies in the way!\n");
		}else if(intPut == 0){
			srand(time(NULL));
			int damageTaken = rand()%enemies.size();
			printf("%s tried to escape, and took %d damage in the process.\n", player->getName(), damageTaken);
			player->addHealth(-damageTaken);
			return;
		}else{
			printf("Invalid choice!\n");
			continue;
		}

		dungeon->Execute(player);

		if(player->isDead()){
			deathMessage(dungeon);
			return;
		}
	}
}

void goToStore(){
	printf("%s: enters the store\n", player->getName());
	printf(shop->menu());
}

void deathMessage(Dungeon* d){
	printf("After many battles, %s was finally defeated in room #%d of the Dungeon %s.\n", player->getName(),d->getCRoom(),d->getName());
	printf("%s died while carrying %d gold and %d potions.\n", player->getName(),player->getMoney(),player->getInventory()->getItemAttribute("AMOUNT"));
	printf("Would you like to load a previous save, or quit? (yes/no) ");
	if(yesNo())
		player = SaveGame::load();
	else
		endGame();
}
