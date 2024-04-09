#include "Value.hpp"
#include "Item.hpp"
#include "ConsumableItem.hpp"
#include "Character.hpp"
#include "views.hpp"
#include "utils.hpp"

class ValueFactory;
class ItemFactory;
class CharacterFactory;
class GameManager;
class EnemyController;
class ZombieController;
class HumanEnemyController;

// TODO: Use this contollers to save data

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
    static Character* createCharacter(CharacterType type);
    static Human* createCustomHuman(string name, int age, string gender,
                                    vector<Skill*> skills, Money* money, double damage);
    static Zombie* createZombie(int level);
    static HumanEnemy* createHumanEnemy(int level);
};

class EnemyController
{
private:
    Character* model;
protected:
    State currentState = State::Start;
public:
    EnemyType type;
    EnemyController() = default;
    Character* getModel();
    void setModel(Character* model);
    State getCurrentState();
    virtual State getNextState() = 0;
    virtual bool work(Character* character) = 0;
};

class ZombieController : public EnemyController
{
private:
    Zombie* model;
public:
    ZombieController() = default;
    virtual State getNextState() override;
    virtual bool work(Character* character) override;
};

class HumanEnemyController : public EnemyController
{
private:
    HumanEnemy* model;
public:
    HumanEnemyController() = default;
    virtual State getNextState() override;
    virtual bool work(Character* character) override;
};

class GameManager
{
private:
    vector<Human*> players;
    EnemyController* enemyController;
    int round_index = 0;
    int level = 0;
    PlayerState state = PlayerState::Shop;
    void _changeEnemyController();
public:
    GameManager() = default;
    GameManager(vector<Human*> players, EnemyController* enemyController, int round_index, int level, PlayerState state);
    void attack();
    void goShop();
    PlayerState getNextState();
    void startRound();
    void increasePrice(ItemType type, int count);
};
