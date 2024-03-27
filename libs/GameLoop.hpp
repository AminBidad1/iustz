#pragma once
#include <chrono>
#include <random>
#include <iostream>
#include <conio.h>
#include "views.hpp"
#include "GameManager.hpp"
#include "utils.hpp"
using namespace std;
void shop(Character* player);
void attack(Character * player);
static int i=0;
void HowItStarts() 
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine rng(seed);
    uniform_int_distribution<int> distribution(1, 100);
    int random_number = distribution(rng);
    cout<<random_number<<endl;
    CharacterType human;
    Character* player=CharacterController::createCharacter(human);
     while(random_number>70)
     {
         i++;
         attack(player);
     }
    shop(player);
}
void attack(Character* player)
{
    Zombie *zombie=CharacterController::createZombie(i);
    while (zombie->hp->getValue() !=0 || player->hp->getValue()!=0)
    {
        player->take_damage(zombie->getDefault_damage());
        Character* character_player = dynamic_cast<Character*>(player);
        ZombieView* zombieView;
        ZombieView::showAttack(character_player , zombieView);
        CharacterView* characterView;
        HumanView::showTakeDamage(characterView);

        zombie->take_damage(player->getDefault_damage());
        if (player->hp->getValue()<=0)
        {
            cout<<"you died...\n";
            exit(0);
        }
        if (zombie->hp->getValue()<=0)
        {
            cout<<"you killed the zombie\n";
        }
   }
    return;
}
void shop(Character* player)
{
    cout<<"you have"<<player->money->getValue()<<endl;
    while(_getch()!=27)
    {
        cout<<"Press ESC to exit the shop...";
    }
    i++;
    attack(player);
}