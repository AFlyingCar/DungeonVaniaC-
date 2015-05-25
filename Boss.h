#ifndef _BOSS_H_
#define _BOSS_H_

#include "Enemy.h"

class Boss : Enemy {
 public:
	Boss(Room* r);
	~Boss();
	bool Execute();

 protected:
	void generateHealth();
	void generateMoney();
	void generateDamage();
};
#endif

