#pragma once
#include <chrono>
#include <random>
#include <iostream>
#include "views.hpp"
#include "GameManager.hpp"
#include "utils.hpp"

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
    Human* player= (Human*)CharacterController::createCharacter(CharacterType::Human);
     while(random_number>70)
     {
         i++;
         attack(player);
     }
    shop(player);
}

void attack(Character* player)
{
    Zombie* zombie = CharacterController::createZombie(i);
    while (zombie->hp->getValue() !=0 || player->hp->getValue()!=0)
    {
        if (zombie->attack(player, zombie->getDefault_damage()))
        {
            ZombieView::showAttack(player , zombie);
            cout<<"you died...\n";
            exit(0);
        }
        ZombieView::showAttack(player , zombie);
        HumanView::showTakeDamage(player);

        // TODO: use items to attack

        if (player->attack(zombie, player->getDefault_damage()))
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


#if defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}
#endif
