#include "GameManager.hpp"


GameManager::GameManager(vector<PlayerController*> players, EnemyController* enemyController, int round_index, int level, PlayerState state)
{
    this->players = players;
    this->enemyController = enemyController;
    this->round_index = round_index;
    this->level = level;
    this->state = state;
}

PlayerState GameManager::getNextState()
{
    int random_number = rand() % 100;
    if (random_number >= 70)
    {
        return PlayerState::Attack;
    }
    return PlayerState::Shop;
}

void GameManager::attack()
{
    Character* enemy = enemyController->getModel();
    PlayerController* playerController = players[round_index % players.size()];
    Human* player = playerController->getModel();
    int choice;
    int players_size = players.size();
    bool endGame = false;
    while (true)
    {
        HumanView::showStatus(player);
        CharacterView::showStatus(enemy, enemyController->type);

        // Attack from player
        if (playerController->work(enemy, players)) // Kill enemy
        {
            level++;
            player->getXp()->gainXP(level);
            return;
        }


        // Attack from enemy
        while (enemyController->getNextState() != State::Attack)
        {
            enemyController->work(player, players);
        }

        if (enemyController->work(player, players)) // Kill player
        {
            CharacterView::showAttack(player, enemy);
            CharacterView::showWasKilled(player);
            players_size = players.size();
            playerController->isAlive = false;

            // Check end game
            endGame = true;
            for (int i=0; i < players.size(); i++)
            {
                if (players[i]->isAlive)
                {
                    endGame = false;
                    break;
                }
            }
            if (endGame)
            {
                cout << "YOU LOST!" << endl;
                exit(0);
            }
        }
        else 
        {
            CharacterView::showAttack(enemy, player);
            HumanView::showTakeDamage(player);
        }

        // Restore
        player->setDamage(player->DEFAULT_DAMAGE);
        enemyController->getModel()->setDamage(enemyController->DEFAULT_DAMAGE);

        // Turn round
        while (true)
        {
            round_index++;
            playerController = players[round_index % players.size()];
            if (playerController->isAlive)
            {
                break;
            }
        }
        player = playerController->getModel();
    }
}

void GameManager::goShop()
{
    Human* player = players[round_index % players.size()]->getModel();
    InventoryItem* inventoryItem;
    Item* item;
    while(true)
    {
        HumanView::showStatus(player);
        if(ShopView::buySection())
        {
            inventoryItem = HumanView::selecetItem();
            item = ItemFactory::createItem(inventoryItem->type, level);
            inventoryItem->item = item;
            if (player->buyItem(inventoryItem, item->getPrice(), 0))
            {
                HumanView::successBuy();
                GameManager::increasePrice(inventoryItem->type, inventoryItem->count);
            }
            else 
            {
                HumanView::failedBuy();
            }
        }
        else
        {
            int index = ShopView::sellItems(player);
            if (index != -1)
            {
                // Selling price is 10% less than real price
                player->money->setValue(player->money->getValue() + (player->items[index]->item->getPrice()) - (player->items[index]->item->getPrice())/10);
                player->removeItem(index, 1);
            }
        }
        if (!ShopView::stay())
            break;
    }
}

void GameManager::startRound()
{
    PlayerController* playerController = players[round_index % players.size()];
    while (true)
    {
        state = getNextState();
        if (state == PlayerState::Shop)
        {
            for (int i=0; i < players.size(); i++)
            {
                playerController = players[round_index % players.size()];
                if (playerController->isAlive)
                {
                    goShop();
                }
                round_index++;
            }
            while (true)
            {
                playerController = players[round_index % players.size()];
                if (playerController->isAlive)
                {
                    break;
                }
                round_index++;
            }
            attack();
        }
        else if (state == PlayerState::Attack)
        {
            while (true)
            {
                playerController = players[round_index % players.size()];
                if (playerController->isAlive)
                {
                    break;
                }
                round_index++;
            }
            attack();
        }
        _changeEnemyController();
    }
}

void GameManager::_changeEnemyController()
{
    delete enemyController->getModel();
    delete enemyController;
    int random_number = rand() % ENEMY_COUNT;
    if ((level+1) % 5 == 0)
    {
        UltraVampireZombie* enemy = CharacterFactory::createUltraVampireZombie(level);
        enemyController = new UltraVampireZombieController();
        enemyController->setModel(enemy);
        enemyController->type = EnemyType::Zombie;
        enemyController->DEFAULT_DAMAGE = enemy->getDamage();
    }
    else 
    {
        if (EnemyType(random_number) == EnemyType::Zombie)
        {
            Zombie* enemy = CharacterFactory::createZombie(level);
            enemyController = new ZombieController();
            enemyController->setModel(enemy);
            enemyController->type = EnemyType::Zombie;
            enemyController->DEFAULT_DAMAGE = enemy->getDamage();
        }
        else if (EnemyType(random_number) == EnemyType::HumanEnemy)
        {
            HumanEnemy* enemy = CharacterFactory::createHumanEnemy(level);
            enemyController = new HumanEnemyController();
            enemyController->setModel(enemy);
            enemyController->type = EnemyType::HumanEnemy;
            enemyController->DEFAULT_DAMAGE = enemy->getDamage();
        }
        else if (EnemyType(random_number) == EnemyType::VampireZombie)
        {
            VampireZombie* enemy = CharacterFactory::createVampireZombie(level);
            enemyController = new VampireZombieController();
            enemyController->setModel(enemy);
            enemyController->type = EnemyType::VampireZombie;
            enemyController->DEFAULT_DAMAGE = enemy->getDamage();
        }
        else if (EnemyType(random_number) == EnemyType::UltraZombie)
        {
            UltraZombie* enemy = CharacterFactory::createUltraZombie(level);
            enemyController = new UltraZombieController();
            enemyController->setModel(enemy);
            enemyController->type = EnemyType::UltraZombie;
            enemyController->DEFAULT_DAMAGE = enemy->getDamage();
        }
    }
}

void GameManager::increasePrice(ItemType type, int count)
{
    if (type == ItemType::Food)
    {
        for (int i = 0; i < count; i++)
        {
            Store::FoodPrice += Store::FoodPrice/10;
        }
    }
    else if (type == ItemType::StaminaBooster)
    {
        for (int i = 0; i < count; i++)
        {
            Store::StaminaBoosterPrice += Store::StaminaBoosterPrice/10;
        }
    }
    else if (type == ItemType::Beverage)
    {
        for (int i = 0; i < count; i++)
        {
            Store::BeveragePrice += Store::BeveragePrice/10;
        }
    }
    else if (type == ItemType::KitchenKnife)
    {
        for (int i = 0; i < count; i++)
        {
            Store::KitchenKnifePrice += Store::KitchenKnifePrice/10;
        }
    }
    else if (type == ItemType::Bomb)
    {
        for (int i = 0; i < count; i++)
        {
            Store::BombPrice += Store::BombPrice/10;
        }
    }
    else if (type == ItemType::Molotov)
    {
        for (int i = 0; i < count; i++)
        {
            Store::MolotovPrice += Store::MolotovPrice/10;
        }
    }
    else if (type == ItemType::Bristle)
    {
        for (int i = 0; i < count; i++)
        {
            Store::BristlePrice += Store::BristlePrice/10;
        }
    }
    else if (type == ItemType::Colt)
    {
        for (int i=0; i < count; i++)
        {
            Store::ColtPrice += Store::ColtPrice/10;
        }
    }
    else if (type == ItemType::Kelash)
    {
        for (int i=0; i < count; i++)
        {
            Store::KelashPrice += Store::KelashPrice/10;
        }
    }
    else if (type == ItemType::FlatLine)
    {
        for (int i=0; i < count; i++)
        {
            Store::FlatLinePrice += Store::FlatLinePrice/10;
        }
    }
    else if (type == ItemType::Sword)
    {
        for (int i=0; i < count; i++)
        {
            Store::SwordPrice += Store::SwordPrice/10;
        }
    }
    else if (type == ItemType::Stick)
    {
        for (int i=0; i < count; i++)
        {
            Store::StickPrice += Store::StickPrice/10;
        }
    }
    else if (type == ItemType::Knuckles)
    {
        for (int i=0; i < count; i++)
        {
            Store::KnucklesPrice += Store::KnucklesPrice/10;
        }
    }
}
