#include "DungeonVania.h"

int main(){
	Player p;
	//Dungeon d;
	// TODO: Add save stuff here once it is written
	createNewPlayer(&p);
	//std::cout << p.getName() << std::endl;
	int input = 0;
	while(true){
		getMenuText();
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

static void getMenuText(){

}

static void printPlayerInventoryWithFormatting(Player p){
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
