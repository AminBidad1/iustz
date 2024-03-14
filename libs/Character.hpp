#include <iostream>
// #include "Hp.hpp"
// #include "Level.hpp"
// #include "Xp.hpp"
// #include "Mana.hpp"

using namespace std;

class Character
{
protected:
    string name;
    int age;
    string gender;
    int hp;
    int level;
    int mana;
    // Round round;
    // Mana mana;
    // Hp hp;
    // Level level;
    // Xp xp;
public:
    string get_name();
    void set_name(string name);
    // void add_xp(Xp xp);
    // void add_hp(Hp hp);
    // void add_mana(Mana mana);
    // void levelup(Level level);
};
