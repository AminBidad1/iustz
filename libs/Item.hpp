#include "Value.hpp"
#include <vector>
class Item {
private:
    HP hp;
    Mana mana;

public:
    Item(int initial_HP , int initial_mana) : hp(initial_HP ) ,mana(initial_mana) {}
    void set_hp(int amount) {
        if (amount>=0) {
            hp.heal(amount);
        }
        else
            hp.takeDamage(amount);
    }
    void set_mana(int amount) {
        if (amount>=0) {
            mana.restoreMana(amount);
        }
        else
            mana.spendMana(amount);
    }
    virtual void display_message(){
        cout<<"test for message in Item";
    }
};