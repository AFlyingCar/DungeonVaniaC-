#include "DungeonVania.h"
#include "Player.h"
#include "Dungeon.h"
#include "Shop.h"
#include "Item.h"

int main(){
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
		getMenu(input,p,s,d);
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

static void goToDungeon(){
}

static void goToStore(Player p, Shop s){
	std::cout << p.getName() << ": enters the store" << std::endl;
	std::cout << s.menu() << std::endl;
}

/*
Parse the user's choice and call the appropriate function.
*/
static void getMenu(int choice, Player p, Shop s, Dungeon d){
	switch(choice){
	 case 0:
		endGame();
		break;
	 case 1:
		goToDungeon();
		break;
	 case 2:
		goToStore(p,s);
		break;
	 case 3:
		printPlayerInventoryWithFormatting(p);
		break;
	 case 4:
		// Save stuff here
		break;
	 default:
		std::cout << "Invalid choice: " << choice << std::endl;
		break;
	}
}
