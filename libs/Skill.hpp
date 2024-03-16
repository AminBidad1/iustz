#include "Item.hpp"

class Skill
{
private:
    int level = 0;
    AttackingItem* item;
public:
    Skill() = default;
    Skill(AttackingItem* item, int level);
    void levelup(int count);
};

