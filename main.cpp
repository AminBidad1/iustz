#include <iostream>
#include <conio.h>
#include "libs/GameLoop.hpp"
#include "libs/views.hpp"

void MenuBar();
void PrintMenuBar(string menubar[3], int selected, int count);
void MenuNewGame();
void MenuLoadGame();
using namespace std;

int main()
{
    reset_terminal();
    MenuBar();
}

void MenuBar()
{
    reset_terminal();
    string menubar[2] = {"1. Start a new game", "2. Exit"};
    int selected = 0;
    PrintMenuBar(menubar, selected, 2);
    bool shouldExit = false;
    while (!shouldExit)
    {
        char choice = getch();
        switch (choice)
        {
        case UP_KEY:
            if (selected == 0)
                selected = 1;
            else
                selected--;
            PrintMenuBar(menubar, selected, 2);
            break;
        case DOWN_KEY:
            if (selected == 1)
                selected = 0;
            else
                selected++;
            PrintMenuBar(menubar, selected, 2);
            break;
        default:
            break;
        case ENTER_KEY:
            shouldExit = true;
            break;
        }
    }
    reset_terminal();
    if (selected == 0)
        MenuNewGame();
    // if (selected == 1)
    //     MenuLoadGame();
    else
        exit(0);
}
void PrintMenuBar(string menubar[], int selected, int count)
{
    for (int i = 0; i < count; i++)
    {
        gotoxy(52, 13 + i);
        if (selected == i)
            cout << color::rize(menubar[i], "", "Red");
        else
            cout << menubar[i];
    }
    gotoxy(52, 16);
}
void MenuNewGame()
{
    string menu[3] = {"1. Solo Player", "2. Team Player", "3. Leave this section"};
    int selected = 0;
    PrintMenuBar(menu, selected, 3);
    bool shouldExit = false;
    while (!shouldExit)
    {
        char choice = getch();
        switch (choice)
        {
        case UP_KEY:
            if (selected == 0)
                selected = 2;
            else
                selected--;
            PrintMenuBar(menu, selected, 3);
            break;
        case DOWN_KEY:
            if (selected == 2)
                selected = 0;
            else
                selected++;
            PrintMenuBar(menu, selected, 3);
            break;
        default:
            break;
        case ENTER_KEY:
            shouldExit = true;
            break;
        }
    }
    // if selected== 0 , 1 TODO:
    /*
        Use
    */
    reset_terminal();
    if (selected == 0)
        start_solo_player();
    if (selected == 1)
        start_team_player();
    if (selected == 2)
        MenuBar();
}
void MenuLoadGame()
{
    string menu[3] = {"1. Load from directory Saves", "2. Choose an address to load a save", "3. Leave this section"};
    int selected = 0;
    PrintMenuBar(menu, selected, 3);
    bool shouldExit = false;
    while (!shouldExit)
    {
        char choice = getch();
        switch (choice)
        {
        case UP_KEY:
            if (selected == 0)
                selected = 2;
            else
                selected--;
            PrintMenuBar(menu, selected, 3);
            break;
        case DOWN_KEY:
            if (selected == 2)
                selected = 0;
            else
                selected++;
            PrintMenuBar(menu, selected, 3);
            break;
        default:
            break;
        case ENTER_KEY:
            shouldExit = true;
            break;
        }
    }
    // if selected== 0 , 1 TODO:
    if (selected == 2)
        MenuBar();
}