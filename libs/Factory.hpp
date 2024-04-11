#include "Character.hpp"
#include "ConsumableItem.hpp"

class ValueFactory
{
public:
    static Value* createValue(ValueType type);
    static Value* createCustomValue(ValueType type, int valueAmount);
};

class ItemFactory
{
public:
    static Item* createItem(ItemType type);
};

class CharacterFactory
{
private:
    static int player_index;
public:
    static const int DEFAULT_DAMAGE = 10;
    static Character* createCharacter(PlayerType type);
    static Human* createCustomHuman(string name, int age, string gender,
                                    vector<Skill*> skills, Money* money, double damage);
    static Zombie* createZombie(int level);
    static HumanEnemy* createHumanEnemy(int level);
    static VampireZombie* createVampireZombie(int level);
    static UltraZombie* createUltraZombie(int level);
    static UltraVampireZombie* createUltraVampireZombie(int level);
};
