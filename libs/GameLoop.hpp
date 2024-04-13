#pragma once
#include <chrono>
#include <random>
#include <iostream>
#include "views.hpp"
#include "GameManager.hpp"
#include "utils.hpp"
// #include "Factory.hpp"

using namespace std;

void reset_terminal()
{
#if defined _WIN32
    system("cls");
    // clrscr(); // including header file : conio.h
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    // std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined(__APPLE__)
    system("clear");
#endif
}

void start_team_player()
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

    string name[4], gender[4];
    int age[4];
    cout << "Enter Human name: ";
    cin >> name[0];
    cout << "Enter Human gender: ";
    cin >> gender[0];
    cout << "Enter Human age: ";
    cin >> age[0];

    cout << "Enter Attacker name: ";
    cin >> name[1];
    cout << "Enter Attacker gender: ";
    cin >> gender[1];
    cout << "Enter Attacker age: ";
    cin >> age[1];

    cout << "Enter Tank name: ";
    cin >> name[2];
    cout << "Enter Tank gender: ";
    cin >> gender[2];
    cout << "Enter Tank age: ";
    cin >> age[2];

    cout << "Enter Healer name: ";
    cin >> name[3];
    cout << "Enter Healer gender: ";
    cin >> gender[3];
    cout << "Enter Healer age: ";
    cin >> age[3];

    playerController1->getModel()->set_name(name[0]);
    playerController1->getModel()->setGender(gender[0]);
    playerController1->getModel()->setAge(age[0]);

    playerController1->getModel()->set_name(name[1]);
    playerController1->getModel()->setGender(gender[1]);
    playerController1->getModel()->setAge(age[1]);

    playerController1->getModel()->set_name(name[2]);
    playerController1->getModel()->setGender(gender[2]);
    playerController1->getModel()->setAge(age[2]);

    playerController1->getModel()->set_name(name[3]);
    playerController1->getModel()->setGender(gender[3]);
    playerController1->getModel()->setAge(age[3]);

    GameManager manager = GameManager(players, enemyController, 0, 0, PlayerState::Shop);
    reset_terminal();
    TableSection();
    WeaponTableStatus();
    manager.startRound();
}
void start_solo_player()
{
    reset_terminal();
    srand(time(0));
    Human *player1 = (Human *)CharacterFactory::createCharacter(PlayerType::Human);
    vector<PlayerController *> players;
    PlayerController *playerController1 = new HumanController();
    playerController1->setModel(player1);
    playerController1->isAlive = true;
    playerController1->type = PlayerType::Human;
    players.push_back(playerController1);
    Zombie *enemy = CharacterFactory::createZombie(0);
    EnemyController *enemyController = new ZombieController();
    enemyController->setModel(enemy);
    enemyController->DEFAULT_DAMAGE = enemy->getDamage();

    string name, gender;
    int age;
    cout << "Enter Human name: ";
    cin >> name;
    cout << "Enter Human gender: ";
    cin >> gender;
    cout << "Enter Human age: ";
    cin >> age;

    playerController1->getModel()->set_name(name);
    playerController1->getModel()->setGender(gender);
    playerController1->getModel()->setAge(age);

    GameManager manager = GameManager(players, enemyController, 0, 0, PlayerState::Shop);
    TableSection();
    WeaponTableStatus();
    manager.startRound();
}

void start(int NumPlayers)
{
    srand(time(0));
}