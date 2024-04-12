#pragma once
#include "bits/stdc++.h"
#include "Character.hpp"
#include "Factory.hpp"

#ifdef __MINGW32__
#include <conio.h>
const int UP_KEY = 72;
const int DOWN_KEY = 80;
const int ENTER_KEY = 13;
const int RIGHT_KEY = 77;
const int LEFT_KEY = 75;
const int ESCAPE_KEY = 27;
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
#include <termios.h>
const int UP_KEY = 65;
const int DOWN_KEY = 66;
const int RIGHT_KEY = 67;
const int LEFT_KEY = 68;
const int ENTER_KEY = int('\n');
const int ESCAPE_KEY = 27;
int getch(void);
#endif


class CharacterView
{
public:
    static void showAttack(Character* character, Character* enemy);
    static void showTakeDamage(Character* character);
    static void showWasKilled(Character* character);
    static void showStatus(Character* character, EnemyType type);
};

class HumanView : public CharacterView
{
public:
    static void showUseItem(Item* item);
    static void failedUseItem(Item* item);
    static void showAppendHP(int value ,Human* human);
    static void showAppendStamina(int value, Human* human);
    static void showStatus(Human* human);
    static InventoryItem* selecetItem();
    static void successBuy();
    static void failedBuy();
    static void showInventory(vector<InventoryItem*> items);
    static int selectInventoryItem(vector<InventoryItem*> items);
    static void showLowStamina(string name);
    static void congratulations(string enemy_name);
    static void levelupSkill(InventoryItem* inventoryItem);
};

class ZombieView : public CharacterView
{
public:
    static void showAttack(Character* character , Zombie* zombie);
    static void showStatus(Zombie* zombie);
};

class EnemyHumanView : public HumanView {};

class ShopView
{
public:
    static bool stay();
    static bool buySection();
    static int sellItems(Human* player);
};

int itemSizeMap(ItemType type);
