#include "Value.hpp"
#include "Item.hpp"
#include "ConsumableItem.hpp"
#include "Character.hpp"
#include "views.hpp"
#include "utils.hpp"

class ValueController;
class ItemController;
class ConsumableItemController;
class CharacterController;
class GameManager;

// TODO: Use this contollers to save data

class ValueController
{
public:
    static Value* createValue(ValueType type);
    static Value* createCustomValue(ValueType type, int valueAmount);
};

class ItemController
{
public:
    static Item* createItem(ItemType type);
};

class ConsumableItemController : public ItemController
{};

class CharacterController
{
private:
    static const int DEFAULT_DAMAGE = 5; 
public:
    static Character* createCharacter(CharacterType type);
    static Human* createCustomHuman(string name, int age, string gender,
                                    vector<Skill*> skills, Money* money, int damage);
    static Zombie* createZombie(int level);
};
