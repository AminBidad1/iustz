#pragma once
#include <chrono>
#include <random>
#include <iostream>
#include "views.hpp"
#include "GameManager.hpp"
#include "utils.hpp"

using namespace std;

void shop(Character* player);
void attack(Character * player);
static int i=0;


void start()
{
    srand(time(0));
    Human* player1 = (Human*)CharacterFactory::createCharacter(CharacterType::Human);
    Human* player2 = (Human*)CharacterFactory::createCharacter(CharacterType::Human);
    vector<Human*> players;
    players.push_back(player1);
    players.push_back(player2);
    Zombie* enemy = CharacterFactory::createZombie(0);
    EnemyController* enemyController = new ZombieController();
    enemyController->setModel(enemy);
    GameManager manager = GameManager(players, enemyController, 0, 0, PlayerState::Shop);
    manager.startRound();
}

void HowItStarts() 
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine rng(seed);
    uniform_int_distribution<int> distribution(1, 100);
    int random_number = distribution(rng);
    cout<<random_number<<endl;
    Human* player= (Human*)CharacterFactory::createCharacter(CharacterType::Human);
     while(random_number>70)
     {
         i++;
         attack(player);
     }
    shop(player);
}

void attack(Character* player)
{
    Zombie* zombie = CharacterFactory::createZombie(i);
    while (zombie->hp->getValue() !=0 || player->hp->getValue()!=0)
    {
        if (zombie->attack(player, zombie->getDamage()))
        {
            ZombieView::showAttack(player , zombie);
            cout<<"you died...\n";
            exit(0);
        }
        ZombieView::showAttack(player , zombie);
        HumanView::showTakeDamage(player);


        if (player->attack(zombie, player->getDamage()))
        {
            cout << "you killed the zombie\n";
        }
   }
    return;
}

void shop(Character* player)
{
    cout << "you have" << player->money->getValue() << endl;
    do
    {
        cout << "Press ESC to exit the shop..." << endl;
    } while(getch() != ESCAPE_KEY);
    i++;
    attack(player);
}
