#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string.h>

class Player;
class Dungeon;
class Shop;

static void createNewPlayer(Player* p);
static bool yesNo();
static void getMenuText(Player p);
static void printPlayerInventoryWithFormatting(Player p);
static void endGame();
static void deathMessage(Dungeon d);
static void goToDungeon(Player* p, Dungeon* d);
static void goToStore(Player p, Shop s);
static void getMenu(int choice, Player* p, Shop* s, Dungeon* d);
