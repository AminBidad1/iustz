#include "Skill.hpp"

Skill::Skill(AttackingItem* item, int level)
{
    this->item = item;
    this->level = level;
}

void Skill::levelup(int count)
{
    this->level += count;
    // TODO: change the percentage error
}
