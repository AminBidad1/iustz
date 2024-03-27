#pragma once
#include "bits/stdc++.h"
#include "Character.hpp"


class CharacterView
{
protected:
    Character* model;
public:
    static void showAttack(Character* enemy , CharacterView* characterView);
    static void showTakeDamage(CharacterView* characterView);
};

class HumanView : public CharacterView
{
protected:
    Human* model;
public:
   static void showUseItem(Item* item , HumanView* humanView);
   static void showAppendHP(int value ,HumanView* humanView);
   static void showAppendStamina(int value , HumanView* humanView);
    
};

class ZombieView : public CharacterView
{
protected:
    Zombie* model;
public:
   static void showAttack(Character* character , ZombieView* zombieView);
};

class EnemyHumanView : public CharacterView {};
