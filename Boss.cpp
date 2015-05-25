#include <time.h>
#include <stdlib.h>

#include "Boss.h"
#include "Room.h"

Boss::Boss(Room* r):
	(r)
{
	boss = "Generic Boss";
	count--;
}

void Boss::generateHealth(){
	setHealth(1000);
}

void Boss::generateMoney(){
	srand(time(NULL));
	m_money = rand()%100 + 100;
}

void Boss::generateDamage(){
	srand(time(NULL));
	m_damage = rand()%20 + 10;
}

// Returns true
bool Boss::Execute(){
	return false;
}

