#include <iostream>
#include <windows.h>
#include <ctime>
using namespace std;
void StartProgram()
{
    cout << "Hello ";
    // Sleep(600);
    cout << "Stranger";
    // Sleep(600);
    cout << " By Pressing 'Y' ";
    // Sleep(600);
    cout << "you will be part of the mystery.\n";
    // Sleep(5000);
    cout << "Just kidding, don't f... the keyboard bruh.\n";
    // Sleep(3000);
    cout << "Ok let's just be serious .\n";
    // Sleep(1500);
    cout << "Who are you ?\n";
    // Sleep(1500);
    cout << "Oh my bad. i forgot to clean the board.\n";
    // Sleep(1000);
    system("cls");
    // Sleep(800);
    cout << "There you go!\n\n";
    // Sleep(600);
    cout << "Ok i was asking.Who are you?\n";
    // Sleep(600);
    Jump:
    cout << "1.Human\n";
    // Sleep(600);
    cout << "2.Not Human\n";
    char input;
    cin>>input;
    try
    {
        while(input!='1' && input!='2' )
        {
            throw invalid_argument("invalid input!\n");

        }
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        goto Jump;
    }
    Sleep(600);
    if (input=='2')
    {
        cout<<"Funny...\n";
        Sleep(600);
        cout<<"what is your name \" NOT HUMAN \"? \n";
    }
    else
    {
        cout<<"Okay human. now what is your name ?\n";
    }
    string name;
    cin>>name;
    cout<<"Okay "<<name<<" .";
    Sleep(600);
    cout<<"What is your sexuality?\n";
    string sexuality;
    cin>>sexuality;
    Sleep(600);
    cout<<"How old are you?";
    string Age;
    cin>>Age;

}

#ifndef IUSTZ_STARTPROGRAM_H
#define IUSTZ_STARTPROGRAM_H

#endif // IUSTZ_STARTPROGRAM_H