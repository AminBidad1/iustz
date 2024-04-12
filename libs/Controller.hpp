#include "Character.hpp"
#include "views.hpp"

class PlayerController
{
private:
    Human *model;

public:
    bool isAlive = true;
    PlayerType type;
    PlayerController() = default;
    Human *getModel();
    void setModel(Human *model);
    int useItem();
    virtual bool work(Character *character, vector<PlayerController *> players) = 0;
};

class HumanController : public PlayerController
{
private:
    Human *model;

public:
    HumanController() = default;
    virtual bool work(Character *character, vector<PlayerController *> players) override;
};

class AttackerController : public PlayerController
{
private:
    Attacker *model;

public:
    AttackerController() = default;
    virtual bool work(Character *character, vector<PlayerController *> players) override;
};

class TankController : public PlayerController
{
private:
    Tank *model;

public:
    TankController() = default;
    virtual bool work(Character *character, vector<PlayerController *> players) override;
};

class HealerController : public PlayerController
{
private:
    Healer *model;

public:
    HealerController() = default;
    virtual bool work(Character *character, vector<PlayerController *> players) override;
};

class EnemyController
{
private:
    Character *model;

protected:
    State currentState = State::Start;

public:
    double DEFAULT_DAMAGE;
    EnemyType type;
    EnemyController() = default;
    Character *getModel();
    void setModel(Character *model);
    State getCurrentState();
    virtual State getNextState() = 0;
    virtual bool work(Character *character, vector<PlayerController *> players) = 0;
};

class ZombieController : public EnemyController
{
private:
    Zombie *model;

public:
    ZombieController() = default;
    virtual State getNextState() override;
    virtual bool work(Character *character, vector<PlayerController *> players) override;
};

class HumanEnemyController : public EnemyController
{
private:
    HumanEnemy *model;

public:
    HumanEnemyController() = default;
    virtual State getNextState() override;
    virtual bool work(Character *character, vector<PlayerController *> players) override;
};

class VampireZombieController : public EnemyController
{
private:
    VampireZombie *model;

public:
    VampireZombieController() = default;
    virtual State getNextState() override;
    virtual bool work(Character *character, vector<PlayerController *> players) override;
};

class UltraZombieController : public EnemyController
{
private:
    UltraZombie *model;

public:
    UltraZombieController() = default;
    virtual State getNextState() override;
    virtual bool work(Character *character, vector<PlayerController *> players) override;
};

class UltraVampireZombieController : public EnemyController
{
private:
    UltraVampireZombie *model;

public:
    UltraVampireZombieController() = default;
    virtual State getNextState() override;
    virtual bool work(Character *character, vector<PlayerController *> players) override;
};
