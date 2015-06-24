#include "Boss.h"

Boss::Boss():
	Enemy()
{
m_count--;
}

Boss::~Boss(){ }

void Boss::generateHealth(){
	setHealth(1000);
}

void Boss::generateMoney(){
	srand(time(NULL));
	m_money = (int)(rand() % 100) + 100;
}

void Boss::generateDamage(){
	srand(time(NULL));
	m_damage = (int)(rand() % (20)) +10;
}

// Boss does not get any defense
void Boss::generateDefense(){
	m_defense = 0;
}

void Boss::generateName(){
	m_name = "Generic Boss";
}
