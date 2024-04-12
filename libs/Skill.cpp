#include "Skill.hpp"

Skill::Skill(InventoryItem *inventoryItem, int level)
{
    this->inventoryItem = inventoryItem;
    this->level = level;
}

void Skill::levelup(int count)
{
    level += count;
    AttackingItem *attackingItem = (AttackingItem *)inventoryItem->item;
    double miss_percent = attackingItem->getMiss_percent();
    double new_miss_percent = pow(0.96, level) * miss_percent;
    attackingItem->setMiss_percent(new_miss_percent);
}

int Skill::getLevel() { return level; }
