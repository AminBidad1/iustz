#pragma once
#include "bits/stdc++.h"
#include "Character.hpp"


class CharacterView
{
protected:
    Character* model;
public:
    virtual void showAttack(Character* enemy);
    virtual void showTakeDamage();
};

class HumanView : public CharacterView
{
protected:
    Human* model;
public:
    void showUseItem(Item* item);
    void showAppendHP(int value);
    void showAppendStamina(int value);
    
};

class ZombieView : public CharacterView
{
protected:
    Zombie* model;
public:
    void showAttack(Character* character) override;
};

class EnemyHumanView : public CharacterView {};
