#include "Skill.hpp"

Skill::Skill(InventoryItem* inventoryItem, int level)
{
    this->inventoryItem = inventoryItem;
    this->level = level;
}

void Skill::levelup(int count)
{
    this->level += count;
    // TODO: change the percentage error
}
