#pragma once
#include "bits/stdc++.h"
#include "Character.hpp"


class CharacterView
{
public:
    static void showAttack(Character* character, Character* enemy);
    static void showTakeDamage(Character* character);
};

class HumanView : public CharacterView
{
public:
   static void showUseItem(Human* human, Item* item);
   static void showAppendHP(int value ,Human* human);
   static void showAppendStamina(int value, Human* human);
};

class ZombieView : public CharacterView
{
public:
   static void showAttack(Character* character , Zombie* zombie);
};

class EnemyHumanView : public CharacterView {};
