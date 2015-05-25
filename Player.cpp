/*
 * Tyler Robbins
 * 5/20/15
 * Player
 * Controls how the player works in the game
 */

#include "Player.h"

// Nothing to see here, just trying to convert Java into C++ in a way that makes sense.

Player::Player(char* newName)
	: m_inventory(NULL),
	m_NAME(NULL),
	m_money(0),
	m_health(100)
{
	m_inventory = new std::vector<Item*>();
	m_NAME = newName;
	resetInventory();
}

Player::~Player(){ }

char* Player::getName(){ return m_NAME; }

std::vector<Item*> Player::getInventory(){ return m_inventory; }

Item* Player::setInventoryItem(int index, Item element){
	Item* n = m_inventory[index];
	m_inventory[index] = element;
	return n;
}

int Player::getMoney(){ return m_money; }

void Player::setMoney(int emoe){ m_money = emoe; }

void Player::addMoney(int emone){ m_money += emone; }

int Player::getHealth(){ return m_health; }

void Player::setHealth(int newHealth){ m_health = newHealth; }

void Player::addHealth(int newHealth){ m_health += newHealth; }

int Player::getArmourAbsorption(){
	return m_inventory[1]->getItemAttribute("DEFENSE")/2;
}

int Player::damageEnemy(Enemy* e){
	srand(time(NULL));

	Item* wep = m_inventory[2];
	int min_damage = wep->getItemAttribute("MIN_DAMAGE");
	int max_damage = wep->getItemAttribute("MAX_DAMAGE");
	int damage_amount = rand()%(max_damage-min_damage)+min_damage;
	damage_amount = damage_amount - e->getDefense();

	if(damage_amount < 0) damage_amount = 0;

	if(e->getDefense() > 0)
		e->addDefense(-1);
	e->addHealth(-damage_amount);
	return damage_amount;
}

char* Player::usePotion(){
	Item* pot_pouch = m_inventory[0];
	int pot_amt = pot_pouch->getItemAttribute("AMOUNT");
	if(pot_amt > 0){
		pot_pouch->setItemAttribute("AMOUNT",pot_amt-1);
		addHealth(pot_pouch->getItemAttribute("HEALTH_POINTS"));
		return "Consumed 1 potion.";
	}
	return "No potions!";
}

bool Player::buyPotion(){
	Item* pot_pouch = m_inventory[0];
	int pot_cost = pot_pouch->getItemAttribute("UPGRADE_COST");
	int pot_amt = pot_pouch->getItemAttribute("AMOUNT");

	if(m_money >= pot_cost){
		pot_pouch->setItemAttribute("AMOUNT",pot_amt+1);
		m_money -= pot_amt;
		return true;
	}
	return false;
}

bool Player::upgradeArmour(){
	Item* armour = m_inventory[1];
	int up_cost = armour->getItemAttribute("UPGRADE_COST");
	int tier = armour->getItemAttribute("TIER");
	int max_tier = armour->getItemAttribute("MAX_TIER");
	int defense = armour->getItemAttribute("DEFENSE");

	if(m_money >= up_cost){
		if(tier != max_tier){
			armour->setItemAttribute("DEFENSE",defense+1);
			armour->setItemAttribute("TIER",tier+1);
			armour->setItemAttribute("UPGRADE_COST",up_cost*2);
			m_money -= up_cost;
			return true;
		}
	}
	return false;
}

bool Player::upgradeWeapon(){
	Item* wep = m_inventory[1];
	int up_cost = wep->getItemAttribute("UPGRADE_COST");
	int tier = wep->getItemAttribute("TIER");
	int max_tier = wep->getItemAttribute("MAX_TIER");
	int max_damage = wep->getItemAttribute("MAX_DAMAGE");
	int min_damage = wep->getItemAttribute("MIN_DAMAGE");

	if(m_money >= up_cost){
		if(tier != max_tier){
			wep->setItemAttribute("MIN_DAMAGE",min_damage*2);
			wep->setItemAttribute("MAX_DAMAGE",max_damage*2);
			wep->setItemAttribute("TIER",tier+1);
			wep->setItemAttribute("UPGRADE_COST",up_cost*2);
			m_money -= up_cost;
			return true;
		}
	}
	return false;
}

void Player::setInventory(std::vector<Item> inv){
	m_inventory = inv;
}

bool Player::isDead(){
	return health <= 0;
}

void searchRoom(Room* r){
	int[] loot = r->loot();

	if(loot == NULL){
		printf("It doesn't appear as though there is anything left in this room.");
		return;
	}

	Item* pot_pouch = m_inventory[0];
	int pot_amt = pot_pouch->getItemAttribute("AMOUNT");
	pot_pouch->setItemAttribute("AMOUNT",pot_amt+loot[0]);
	addMoney(loot[1]);
	printf("Found %d gold and %d potions.",loot[1],loot[0]);
}
