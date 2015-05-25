#ifndef _SAVE_GAME_UTILS
#define _SAVE_GAME_UTILS

#include <stdio.h>
#include <vector>
#include <map>

#include "Player.h"

namespace SaveGame
{
	const char[4] MAGIC = {0xde,0xad,0xbe,0xef}

	// Player* load(){
	// 	if(SaveGame::doesSaveFileExist()){
	// 		FILE* file = fopen("DungeonVaniaSave.sav","rb");
	// 	}else{
	// 		printf("No save file found!\n");
	// 		return NULL;
	// 	}
	// }

	// void save(Player* p){
	// 	FILE* file = fopen("DungeonVaniaSave.sav","wb");
	// 	// fwrite(MAGIC,sizeof(MAGIC),1,file);
	// 	fprintf(file, MAGIC);
	// }

	Player* load(){

	}

	void save(Player* p){
		FILE* file = fopen("./Saves/player.txt","w");

		fprintf(file, "%s\n", p->getName());
		fprintf(file, "%d\n", p->getMoney());
		fprintf(file, "%d\n", p->getHealth());
		fclose(file);

		delete file;

		std::vector<Item*> inv = p->getInventory();

		for(int i = 0; i < inv.size(); i++){
			char* filename = "./Saves/Inventory/Item%d.txt",i;
			file = fopen("./Saves/Inventory/Item%d.txt",i,"w");
			fprintf(file, "%s\n", inv[i]->getName());
			std::map<char*,int> at = inv[i]->getAllAttributes();

			for(std::map<char*,int>::iterator i = at.begin(); i != at.end(); ++i){
				char* k = i->first;
				int v = i->second;
				fprintf(file, "%s:", k);
				fprintf(file, "%d\n", v);
			}
			fclose(file);
			delete file;
		}
	}

	bool doesFileExist(){
		FILE* f = fopen("./Saves/player.txt","r");
		return scanf(f,"%*s") <= 0;
	}
}

#endif