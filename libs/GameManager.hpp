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
    static int player_index;
public:
    static const int DEFAULT_DAMAGE = 10;
    static Character* createCharacter(CharacterType type);
    static Human* createCustomHuman(string name, int age, string gender,
                                    vector<Skill*> skills, Money* money, double damage);
    static Zombie* createZombie(int level);
};

class GameManager
{
private:
    vector<Human*> players;
    Character* enemy;
    int round_index = 0;
    int level = 0;
    PlayerState state = PlayerState::Shop;
public:
    GameManager() = default;
    GameManager(vector<Human*> players, Character* enemy, int round_index, int level, PlayerState state);
    void attack();
    void goShop();
    PlayerState getNextState();
    void startRound();
    void increasePrice(ItemType type, int count);
};
