#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string.h>

/*
#include "SaveGameUtils.h"
#include "Dungeon.h"
#include "Shop.h"
*/
class Player;
class Dungeon;

#include "Player.h"

static void createNewPlayer(Player* p);
static bool yesNo();
static void getMenuText(Player p);
static void printPlayerInventoryWithFormatting(Player p);
static void endGame();
static void deathMessage(Dungeon d);
static void goToDungeon();
static void goToStore();
static void getMenu(int choice, Player p);
