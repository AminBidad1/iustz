#include <iostream>
#include <windows.h>
#include <ctime>
using namespace std;
void StartProgram(){
    cout << "Hello ";
    Sleep(600);
    cout << "Stranger";
    Sleep(600);
    cout << " By Pressing 'Y' ";
    Sleep(600);
    cout<<"you will be part of the mystery.\n";
    Sleep(5000);
    cout << "Just kidding, don't f... the keyboard bruh.\n";
    Sleep(3000);
    cout<<"Ok let's just be serious .\n";
    Sleep(1500);
    cout<<"Who are you ?\n";
    Sleep(1500);
    cout<<"Oh my bad. i forgot to clean the board.\n";
    Sleep(1000);
    system("cls");
    Sleep(800);
    cout<<"There you go!\n\n";
    Sleep(600);
    cout<<"Ok i was asking.Who are you?\n";
    Sleep(600);
    cout<<"1.Human\n";
    Sleep(600);
    cout<<"2.Not Human\n";
    Chance:
    char whatever;
    cin>>whatever;
        if(whatever!='1' || whatever!='2') {
            Sleep(800);
            system("cls");
            cout << "ohhhh.\n";
            Sleep(1000);
            cout << "so You wanna play???\n";
            Sleep(1300);
            cout << "Ok let's play the game.\n";
            Sleep(1800);
            cout<<"You've been swallowed by a demon\n";
            Sleep(1500);
            cout<<"you died\n";
            Sleep(2000);
            exit(0);
        }




}

#ifndef IUSTZ_STARTPROGRAM_H
#define IUSTZ_STARTPROGRAM_H

#endif //IUSTZ_STARTPROGRAM_H
