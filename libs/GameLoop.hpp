#pragma once
#include <chrono>
#include <random>
#include <iostream>
#include "views.hpp"
#include "GameManager.hpp"
#include "utils.hpp"
// #include "Factory.hpp"

using namespace std;

void start()
{
    srand(time(0));
    Human *player1 = (Human *)CharacterFactory::createCharacter(PlayerType::Human);
    Attacker *player2 = (Attacker *)CharacterFactory::createCharacter(PlayerType::Attacker);
    Tank *player3 = (Tank *)CharacterFactory::createCharacter(PlayerType::Tank);
    Healer *player4 = (Healer *)CharacterFactory::createCharacter(PlayerType::Healer);
    vector<PlayerController *> players;
    PlayerController *playerController1 = new HumanController();
    playerController1->setModel(player1);
    playerController1->isAlive = true;
    playerController1->type = PlayerType::Human;
    players.push_back(playerController1);
    PlayerController *playerController2 = new AttackerController();
    playerController2->setModel(player2);
    playerController2->isAlive = true;
    playerController2->type = PlayerType::Attacker;
    players.push_back(playerController2);
    PlayerController *playerController3 = new TankController();
    playerController3->setModel(player3);
    playerController3->isAlive = true;
    playerController3->type = PlayerType::Tank;
    players.push_back(playerController3);
    PlayerController *playerController4 = new HealerController();
    playerController4->setModel(player4);
    playerController4->isAlive = true;
    playerController4->type = PlayerType::Healer;
    players.push_back(playerController4);
    Zombie *enemy = CharacterFactory::createZombie(0);
    EnemyController *enemyController = new ZombieController();
    enemyController->setModel(enemy);
    enemyController->DEFAULT_DAMAGE = enemy->getDamage();
    GameManager manager = GameManager(players, enemyController, 0, 0, PlayerState::Shop);
    manager.saveGame("./test.txt");
    manager.startRound();
}
