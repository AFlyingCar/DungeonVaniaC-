#ifndef _BOSS_H_
#define _BOSS_H_

#include "Enemy.h"

class Boss: public Enemy{
public:
	Boss();
	~Boss();
	bool Execute();
protected:
	void generateHealth();
	void generateMoney();
	void generateDamage();
	void generateDefense();
	void generateName();
};

#endif
