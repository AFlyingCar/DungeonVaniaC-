#include "DungeonVania.h"
#include "Player.h"
#include "Dungeon.h"
#include "Shop.h"
#include "Item.h"
#include "Enemy.h"
#include "Room.h"
#include "Logging.h"

int main(){
	try{
		Player p;
		Dungeon d;
		Shop s(&p);
		// TODO: Add save stuff here once it is written
		createNewPlayer(&p);
		//std::cout << p.getName() << std::endl;
		int input = 0;
		while(true){
			getMenuText(p);
			std::cin >> input;
			getMenu(input,&p,&s,&d);
		}
	}catch(...){
		//std::cout << __FILE__ << __LINE__ << ": " << __FUNCTION__ << std::endl;
		log_error();
	}
}

static void createNewPlayer(Player* p){
	p->setName("Test");
}

/*
A simple function for looping and waiting for a yes or no answer from the user
*/
static bool yesNo(){
	std::string yn = "";
	while(true){
		std::cin >> yn;
		if(yn.compare("yes") == 0)
			return true;
		else if(yn.compare("no") == 0)
			return false;
		else
			std::cout << "'yes' or 'no' please!" << std::endl;
	}
}

/*
Prints the town menu to the screen
*/
static void getMenuText(Player p){
	std::cout << p.getName() << ": starts in the town" << std::endl;
	std::cout << p.getName() << ": checks their pockets and finds " << p.getMoney() << "gold" << std::endl;
	std::cout << "0. Go to bed" << std::endl;
	std::cout << "1. Go to the nearby dungeon" << std::endl;
	std::cout << "2. Go to the store" << std::endl;
	std::cout << "3. Check Inventory" << std::endl;
	std::cout << "4. Save Game" << std::endl;
	std::cout << "Choice: " << std::endl;
}

/*
Prints the player's inventory to the screen in a nice, formatted way.
*/
static void printPlayerInventoryWithFormatting(Player p){
	std::vector<Item*> inv = p.getInventory();
	Item wep = *inv.at(2);
	Item arm = *inv.at(1);
	Item pot = *inv.at(0);

	std::cout << p.getName() << std::endl;
	std::cout << "Money: " << p.getMoney() << std::endl;
	std::cout << "Health: " << p.getHealth() << std::endl;

	std::cout << "Weapon Tier: " << wep.getItemAttribute("TIER") << std::endl;
	std::cout << "Weapon Damage: " << wep.getItemAttribute("MIN_DAMAGE") << " to " << wep.getItemAttribute("MAX_DAMAGE") << std::endl;
	std::cout << "Armour Tier: " << arm.getItemAttribute("TIER") << std::endl;
	std::cout << "Armour Defense: " << arm.getItemAttribute("DEFENSE") << std::endl;
	std::cout << "Amount of Potions: " << pot.getItemAttribute("AMOUNT") << std::endl;
}

static void endGame(){
	exit(0);
}

/*
static void deathMessage(Dungeon d){
}
*/

static void goToDungeon(Player* p, Dungeon* d){
	std::cout << p->getName() << ": walks to the nearby dungeon." << std::endl;
	std::vector<Enemy*> enemies;
	int choice = -1;
	while(choice != 0 || d->canMoveToNextRoom()){
		enemies = d->getCurrentRoom()->getEnemies();
		if(enemies.size()>0)
			std::cout << p->getName() << ": encounters " << enemies.size() << " enemies." << std::endl;
		for(int i = 0; i < enemies.size(); i++){
			std::cout << enemies.at(i)->getName() << " " << (i+1) << "'s health: " << enemies.at(i)->getHealth() << "\t";
			std::cout << "Defense: " << enemies.at(i)->getDefense() << "\t";
			std::cout << "Damage: " << enemies.at(i)->getDamage() << "\t" << std::endl;
		}
		std::cout << p->getName() << "'s health: " << p->getHealth() << std::endl;
		std::cout << p->getName() << "'s damage: " << p->getInventory().at(2)->getItemAttribute("MIN_DAMAGE") << " to " << p->getInventory().at(2)->getItemAttribute("MAX_DAMAGE") << std::endl;

		if(d->canMoveToNextRoom()){
			std::cout << "1. Search room" << std::endl;
			std::cout << "2. Check Inventory" << std::endl;
			std::cout << "3. Use Items" << std::endl;
			std::cout << "4. Move to next Room" << std::endl;
			std::cout << "0. Escape" << std::endl;
		}else{
			std::cout << "1. Attack" << std::endl;
			std::cout << "2. Check Inventory" << std::endl;
			std::cout << "3. Use Items" << std::endl;
			std::cout << "4. Move to next Room" << std::endl;
			std::cout << "0. Escape" << std::endl;
		}

		std::cout << "Choice: ";
		int input;
		std::cin >> input;
		switch(input){
			int dAmt;
			case 0:
				srand(time(NULL));
				dAmt = rand() %enemies.size();
				std::cout << p->getName() << " tried to escape, and took " << dAmt << " damage." << std::endl;
				p->addHealth(-dAmt);
				return;
			case 1:
				if(d->canMoveToNextRoom())
					p->searchRoom(d->getCurrentRoom());
				else{
					if(enemies.size() > 1){
						std::cout << "Which enemy would you like to attack?" << std::endl;
						for(int i = 0; i < enemies.size(); i++)
							std::cout << "Enemy " << (i+1) << "\t";
						std::cout << "Choice: ";
						std::cin >> input;
					}else
						input = 1;
					
				
					std::cout << "Enemy " << input << ": took " << p->damageEnemy(enemies.at(input-1)) << " damage." << std::endl;
					log_error();
					if(enemies.at(input-1)->isDead())
						std::cout << enemies.at(input-1)->getName() << input << " died!" << std::endl;
				}
				break;
			case 2:
				printPlayerInventoryWithFormatting(*p);
				continue;
			case 3:
				printPlayerInventoryWithFormatting(*p);
				std::cout << "How many potions would you like to use: ";
				std::cin >> input;
				for(int i=0; i < input; i++)
					p->usePotion();
				break;
			case 4:
				if(d->moveToNextRoom())
					std::cout << p->getName() << " moves on from " << (d->getRoomPtr()-1) << ", and ventures further into the dungeon." << std::endl;
				else
					std::cout << "Cannot move onto the next room because there are enemies in the way!" << std::endl;
				continue;
			default:
				std::cout << "Invalid choice: " << input;
				continue;
		}
		d->Execute(p);
		if(p->isDead()){
			//deathMessage(*d);
			return;
		}
	}
}

/*
Calls the Shop's menu
*/
static void goToStore(Player p, Shop s){
	std::cout << p.getName() << ": enters the store" << std::endl;
	std::cout << s.menu() << std::endl;
}

/*
Parse the user's choice and call the appropriate function.
*/
static void getMenu(int choice, Player* p, Shop* s, Dungeon* d){
	switch(choice){
	 case 0:
		endGame();
		break;
	 case 1:
		goToDungeon(p,d);
		break;
	 case 2:
		goToStore(*p,*s);
		break;
	 case 3:
		printPlayerInventoryWithFormatting(*p);
		break;
	 case 4:
		// Save stuff here
		break;
	 default:
		std::cout << "Invalid choice: " << choice << std::endl;
		break;
	}
}
