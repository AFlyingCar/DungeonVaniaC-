#include "DungeonVania.h"

int main(){
	Player p;
	//Dungeon d;
	// TODO: Add save stuff here once it is written
	createNewPlayer(&p);
	//std::cout << p.getName() << std::endl;
	int input = 0;
	while(true){
		getMenuText(p);
		std::cin >> input;
		getMenu(input,p);
	}
}

static void createNewPlayer(Player* p){
	p->setName("Test");
}

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

static void goToStore(){
}

static void getMenu(int choice, Player p){
	switch(choice){
	 case 0:
		endGame();
		break;
	 case 1:
		goToDungeon();
		break;
	 case 2:
		std::cout << p.getName() << " goes to the store." << std::endl;
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
