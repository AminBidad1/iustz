#include "Value.hpp"
#include "Item.hpp"
#include "ConsumableItem.hpp"
#include "Character.hpp"
#include "views.hpp"
#include "utils.hpp"
#include "Factory.hpp"
#include "Controller.hpp"

class GameManager
{
private:
    vector<PlayerController*> players;
    EnemyController* enemyController;
    int round_index = 0;
    int level = 0;
    PlayerState state = PlayerState::Shop;
    void _changeEnemyController();
public:
    GameManager() = default;
    GameManager(vector<PlayerController*> players, EnemyController* enemyController, int round_index, int level, PlayerState state);
    void attack();
    void goShop();
    PlayerState getNextState();
    void startRound();
    void increasePrice(ItemType type, int count);
};
