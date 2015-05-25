#include "Enemy.h"

Enemy::Enemy(Room* r):
	m_money(0),	
	m_damage(0),
	m_defense(0),
	m_name(NULL),
	m_room(r),
{
	generateHealth();
	generateMoney();
	generateDamage();
	generateName();
}

Enemy::~Enemy(){}

void Enemy::generateHealth(){
	srand(time(NULL));
	m_health = rand()%(10+enemyInRoom) + 10;
}

void Enemy::generateMoney(){
	srand(time(NULL));
	m_money = rand()%(2+enemyInRoom) + 2;
}

void Enemy::generateDamage(){
	srand(time(NULL));
	m_damage = rand()%(2+enemyInRoom) + 2;
}	

void Enemy::generateDefense(){
	srand(time(NULL));
	m_defense = rand()%(2+enemyInRoom) + 2;
}

void Enemy::generateDamage(){
	srand(time(NULL));
	m_damage = rand()%(2+enemyInRoom) + 2;
}

void Enemy::generateName(){
	m_name = "Enemy";
}

void Enemy::addHealth(int newHealth){
	m_health += newHealth;
}

void Enemy::setHealth(int newHealth){
	m_health = newHealth;
}

int Enemy::getDamage(){ 
	return m_damage;
}

int Enemy::getHealth(){
	return m_health;
}

char* Enemy::getName(){
	return m_name;
}

int Enemy::getDefense(){
	return m_defense;
}

int Enemy::getMoney(){
	return m_money;
}

void Enemy::addDefense(int d){
	defense += d;
}

void Enemy::defend(){
	if(defense < 10)
		defense++;
}

int Enemy::damagePlayer(Player* p){
	int damageAmt = -(m_damage - p->getArmourAbsorption());
	p->addHealth(damageAmt);
	return damageAmt;
}

bool Enemy::isDead(){
	return m_health <= 0;
}
float Enemy::FastInvSqrt(float x){
	float xhalf = 0.5f*x;
	int i = *(int*)&x;
	i = 0x5f3759df - (i>>1);
	x = *(float*)&i;
	x = x *(1.5f-(xhalf*x*x));
	return x;
}

