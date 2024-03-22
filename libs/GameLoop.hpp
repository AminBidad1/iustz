#pragma once
#include <chrono>
#include <random>
#include <iostream>
using namespace std;
void HowItStarts() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine rng(seed);
    uniform_int_distribution<int> distribution(1, 100);
    int random_number = distribution(rng);
    cout<<random_number<<endl;
    if (random_number > 70) {
        cout << "attack";
    } else
        cout << "shop";
}
