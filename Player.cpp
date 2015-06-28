#include "Player.h"
#include "Item.h"
#include "Room.h"
#include "Enemy.h"

Player::Player():
 m_name(""),
 m_money(0),
 m_health(0),
 m_inventory()
{
	m_health = 100;
	resetInventory();
}

Player::~Player(){}

std::string Player::getName(){ 
	return m_name; 
}

void Player::setName(std::string newName){
	m_name = newName;
}

/*
Resets the player's inventory to default
*/
void Player::resetInventory(){
	m_inventory.clear();
	m_inventory.push_back(new Item("Potions"));
	m_inventory.push_back(new Item("Armour"));
	m_inventory.push_back(new Item("Weapon"));

	Item* i1 = m_inventory.at(0);
	Item* i2 = m_inventory.at(1);
	Item* i3 = m_inventory.at(2);

	i1->addAttribute("AMOUNT",1);
	i1->addAttribute("HEALTH_POINTS",15);
	i1->addAttribute("UPGRADE_COST",5);

	i2->addAttribute("DEFENSE",1);
	i2->addAttribute("TIER",0);
	i2->addAttribute("MAX_TIER",5);
	i2->addAttribute("UPGRADE_COST",10);

	i3->addAttribute("MIN_DAMAGE",2);
	i3->addAttribute("MAX_DAMAGE",4);
	i3->addAttribute("TIER",0);
	i3->addAttribute("MAX_TIER",5); 
	i3->addAttribute("UPGRADE_COST",10);
}

int Player::getMoney(){
	return m_money;
}
int Player::getHealth(){
	return m_health;
}
int Player::addMoney(int m){
	m_money += m;
}
int Player::addHealth(int h){
	m_health += h;
}
int Player::setMoney(int m){
	m_money = m;
}
int Player::setHealth(int h){
	m_health = h;
}

std::vector<Item*> Player::getInventory(){
	return m_inventory;
}

/*
Calculates the amount of damage the player's armour can absorb
*/
int Player::getArmourAbsorption(){
	// TODO - Write this method.
	return 0;
}

// TODO - write these methods
bool Player::buyPotion(){
}
bool Player::upgradeWeapon(){
}
bool Player::upgradeArmour(){
}

void Player::searchRoom(Room* r){
	int* loot = r->loot();
	if(loot == NULL){
		std::cout << "It doesn't appear as though there is anything left in this room." << std::endl;
		return;
	}
	int pAmt = m_inventory.at(0)->getItemAttribute("AMOUNT");
	m_inventory.at(0)->setItemAttribute("AMOUNT",pAmt+loot[0]);
	addMoney(loot[1]);
	std::cout << "Found " << loot[0] << " gold and " << loot[1] << "potions." << std::endl;
	delete[] loot;
}

int Player::damageEnemy(Enemy* e){
	int minDamage = m_inventory.at(2)->getItemAttribute("MIN_DAMAGE");
	int maxDamage = m_inventory.at(2)->getItemAttribute("MAX_DAMAGE");
	srand(time(NULL));
	int damageAmt = rand() % (maxDamage-minDamage) + minDamage;
	damageAmt -= e->getDefense();
	if(damageAmt < 0) damageAmt = 0;
	if(e->getDefense() > 0) e->addDefense(-2);
	e->addHealth(-damageAmt);
	return damageAmt;
}

std::string Player::usePotion(){
	int pAmt = m_inventory.at(0)->getItemAttribute("AMOUNT");
	if(pAmt > 0){
		m_inventory.at(0)->setItemAttribute("AMOUNT",pAmt-1);
		addHealth(m_inventory.at(0)->getItemAttribute("HEALTH_POINTS"));
		return "Consumed 1 potion.";
	}else
		return "No potions!";
}

bool Player::isDead(){
	return m_health <= 0;
}
