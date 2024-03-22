#pragma once
#include "Item.hpp"

class Skill
{
private:
    int level = 0;
    InventoryItem* inventoryItem;
public:
    Skill() = default;
    Skill(InventoryItem* inventoryItem, int level);
    void levelup(int count);
};
