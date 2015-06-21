#include "Player.h"

Player::Player():
 m_name(""),
 m_money(0),
 m_health(0)
 //m_inventory()
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

void Player::resetInventory(){

}
