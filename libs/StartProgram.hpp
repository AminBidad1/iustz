#pragma once
#include <iostream>
#include "GameLoop.hpp"
#include <ctime>
#ifdef __MINGW32__
    #include <windows.h>
    int get_sleep(int number)
    {
        return number;
    }
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    #include<unistd.h>
    #define Sleep sleep
    double get_sleep(int number)
    {
        return number/600;
    }
#endif 

using namespace std;


/* Clear terminal */
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


void StartProgram()
{
    cout << "Hello ";
    Sleep(get_sleep(600));
    cout << "Stranger";
    Sleep(get_sleep(600));
    cout << " By Pressing 'Y' ";
    Sleep(get_sleep(600));
    cout << "you will be part of the mystery.\n";
    Sleep(get_sleep(5000));
    cout << "Just kidding, don't f... the keyboard bruh.\n";
    Sleep(get_sleep(3000));
    cout << "Ok let's just be serious .\n";
    Sleep(get_sleep(1500));
    cout << "Who are you ?\n";
    Sleep(get_sleep(1500));
    cout << "Oh my bad. i forgot to clean the board.\n";
    Sleep(get_sleep(1000));
    reset_terminal();
    Sleep(get_sleep(800));
    cout << "There you go!\n\n";
    Sleep(get_sleep(600));
    cout << "Ok i was asking.Who are you?\n";
    Sleep(get_sleep(600));
    Jump: // TODO: Use While loop
    cout << "1.Human\n";
    Sleep(get_sleep(600));
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
    Sleep(get_sleep(600));
    if (input=='2')
    {
        cout<<"Funny...\n";
        Sleep(get_sleep(600));
        cout<<"what is your name \" NOT HUMAN \"? \n";
    }
    else
    {
        cout<<"Okay human. now what is your name ?\n";
    }
    string name;
    cin>>name;
    cout<<"Okay "<<name<<" .";
    Sleep(get_sleep(600));
    cout<<"What is your sexuality?\n";
    string sexuality;
    cin>>sexuality;
    Sleep(get_sleep(600));
    cout<<"How old are you?";
    string Age;
    cin>>Age;
    start();
}

#ifndef IUSTZ_STARTPROGRAM_H
#define IUSTZ_STARTPROGRAM_H

#endif // IUSTZ_STARTPROGRAM_H
