#include "Character.hpp"
#include "Item.hpp"

class Factory
{
public:
    Character* getCharacter(string name);

    Item* getItem(string name);
};