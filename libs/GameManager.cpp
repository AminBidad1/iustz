#include "GameManager.hpp"

Value* ValueController::createValue(ValueType type)
{
    if (type == ValueType::HP)
    {
        HP hp = HP(100);
        return &hp;
    }
    else if (type == ValueType::Stamina)
    {
        Stamina stamina = Stamina(100);
        return &stamina;
    }
    else if (type == ValueType::XP)
    {
        XP xp = XP(1);
        return &xp;
    }
    else if (type == ValueType::Money)
    {
        Money money = Money(100);
        return &money;
    }
    return nullptr;
}

Character* CharacterController::createCharacter(CharacterType type)
{
    if (type == CharacterType::Human)
    {
        vector<InventoryItem*> items;
        
        vector<Skill*> skills;
        Human human = Human(
            "player", 18, "man", (HP*)ValueController::createValue(ValueType::HP),
            (Money*)ValueController::createValue(ValueType::Money), 
            (Stamina*)ValueController::createValue(ValueType::Stamina),
            (XP*)ValueController::createValue(ValueType::XP), skills, items
        );

    }
}