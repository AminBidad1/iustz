#include "Factory.hpp"

Character* Factory::getCharacter(string name)
    {
        if (name == "Human")
        {
            return new Human;
        }
        if (name == "Zombie")
        {
            return new Zombie;
        }
        if (name == "EnemyHuman")
        {
            return new EnemyHuman;
        }
    }

Item* Factory::getItem(string name)
    {
        if (name == "KitchenKnife")
        {
            return new KitchenKnife;
        }
        if (name == "Grande")
        {
            return new Grande;
        }
        if (name == "Molotov")
        {
            return new Molotov;
        }
        if (name == "Bristle")
        {
            return new Bristle;
        }
        if (name == "Firearms")
        {
            return new Firearms;
        }
    }