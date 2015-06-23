#include "Enemy.h"
#include "Player.h"

int Enemy::m_count = 0;
int Enemy::m_enemyInRoom = 0;

//Enemy::Enemy(const Room& r):
Enemy::Enemy():
	m_health(0),
	m_money(0),
	m_name(""),
	m_defense(0),
	m_damage(0)/*,*/
	//m_room(r)
{
	m_count++;
	generateHealth();
	generateMoney();
	//generateDefense();
	generateDamage();
	generateName();
}

Enemy::~Enemy(){}

void Enemy::addHealth(int newHealth){
	m_health += newHealth;
}
void Enemy::setHealth(int newHealth){
	m_health = newHealth;
}

int Enemy::getHealth(){ return m_health; }
int Enemy::getDamage(){ return m_damage; }
std::string Enemy::getName(){ return m_name; }
int Enemy::getDefense(){ return m_defense; }
int Enemy::getMoney(){ return m_money; }

void Enemy::addDefense(int d){
	m_defense += d;
}

/*
Increases the enemy's defense if it is less than 10
*/
void Enemy::defend(){
	if(m_defense < 10)
		m_defense++;
}

/*
Calculates how to damage the player. Damage dealt is based on damage value and player's armour
*/
int Enemy::damagePlayer(Player *p){
	int damageAmt = (m_damage - p->getArmourAbsorption());
	p->addHealth(-damageAmt);
	return damageAmt;
}

bool Enemy::isDead(){
	return m_health <= 0;
}

/*
Generates the starting health for the enemy
*/
void Enemy::generateHealth(){
	srand(time(NULL));
	m_health = (int)(rand() % (m_enemyInRoom+10)+10);
}

/*
Generates the starting money for the enemy to drop upon death.
*/
void Enemy::generateMoney(){
	srand(time(NULL));
	m_money = (int)(rand() % (m_enemyInRoom+2)+2);
}

// Commented out to prevent compiler stupidity
/*
void Enemy::generateDefense(){
	srand(time(NULL));
	m_defense = (int)(rand() % (2*m_count*(m_enemyInRoom/10.0f)));
}
*/

/*
Generates the starting damage that the enemy can deal
*/
void Enemy::generateDamage(){
	srand(time(NULL));
	m_damage = (int)(rand() % (10-m_enemyInRoom)+3);
}

// Generates a unique name for each enemy. Guaranteed to be random.
void Enemy::generateName(){
	m_name = "Enemy";
}
