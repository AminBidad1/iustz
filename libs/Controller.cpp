#include "Controller.hpp"

Human *PlayerController::getModel()
{
    return this->model;
}

void PlayerController::setModel(Human *model)
{
    this->model = model;
}

int PlayerController::useItem()
{
    // Use item from inventory
    int choice;

    while (true)
    {
        choice = HumanView::selectInventoryItem(model->items);
        if (choice == model->items.size())
        {
            break;
        }
        else if (model->items[choice]->fatherType == ItemType::ConsumableItem)
        {
            if (model->items[choice]->count > 0)
            {
                model->useItem(choice);
                HumanView::showUseItem(model->getItem(choice)->item);
            }
            else
            {
                HumanView::failedUseItem(model->getItem(choice)->item);
            }
        }
        else
        {
            if (model->items[choice]->count > 0)
            {
                model->useItem(choice);
                HumanView::showUseItem(model->getItem(choice)->item);
                return choice;
            }
            else
            {
                HumanView::failedUseItem(model->getItem(choice)->item);
            }
        }
    }
    return choice;
}

bool HumanController::work(Character *enemy, vector<PlayerController *> players)
{
    // Check stamina
    Human *_model = (Human *)getModel();
    if (_model->stamina->getValue() <= 10)
    {
        HumanView::showLowStamina(_model->get_name());
        _model->stamina->regenerateStamina(3);
    }
    else
    {
        int index = useItem();
        _model->setDamage(_model->stamina->getValue() * _model->getDamage() / 50);

        // Attack from _model
        if (_model->attack(enemy, _model->getDamage())) // kill enemy
        {
            HumanView::showAttack(_model, enemy);
            CharacterView::showWasKilled(enemy);
            HumanView::congratulations(enemy->get_name());
            // Levelup Skill
            if (index != _model->items.size())
            {
                _model->skills[index]->levelup(2);
                HumanView::levelupSkill(_model->items[index]);
            }
            _model->money->append(enemy->money->getValue());
            _model->setDamage(_model->DEFAULT_DAMAGE);
            return true;
        }
        else
        {
            HumanView::showAttack(_model, enemy);
            CharacterView::showTakeDamage(enemy);
            // Levelup Skill
            if (index != _model->items.size())
            {
                _model->skills[index]->levelup(1);
                HumanView::levelupSkill(_model->items[index]);
            }
            _model->stamina->useStamina(8);
        }
    }
    return false;
}

bool AttackerController::work(Character *enemy, vector<PlayerController *> players)
{
    // Check stamina
    Attacker *_model = (Attacker *)getModel();
    if (_model->stamina->getValue() <= 5)
    {
        HumanView::showLowStamina(_model->get_name());
        // _model->stamina->regenerateStamina(3);
    }
    else
    {
        int index = useItem();
        _model->setDamage(_model->stamina->getValue() * _model->getDamage() / 50);

        // Attack from _model
        if (_model->attack(enemy, _model->getDamage())) // kill enemy
        {
            HumanView::showAttack(_model, enemy);
            CharacterView::showWasKilled(enemy);
            HumanView::congratulations(enemy->get_name());
            _model->money->append(enemy->money->getValue());
            // Levelup Skill
            if (index != _model->items.size())
            {
                _model->skills[index]->levelup(4);
                HumanView::levelupSkill(_model->items[index]);
            }
            _model->setDamage(_model->DEFAULT_DAMAGE);
            return true;
        }
        else
        {
            HumanView::showAttack(_model, enemy);
            CharacterView::showTakeDamage(enemy);
            // Levelup Skill
            if (index != _model->items.size())
            {
                _model->skills[index]->levelup(2);
                HumanView::levelupSkill(_model->items[index]);
            }
            _model->stamina->useStamina(3);
        }
    }
    return false;
}

bool TankController::work(Character *enemy, vector<PlayerController *> players)
{
    // Check stamina
    Tank *_model = (Tank *)getModel();
    if (_model->stamina->getValue() <= 10)
    {
        HumanView::showLowStamina(_model->get_name());
        _model->stamina->regenerateStamina(3);
    }
    else
    {
        int index = useItem();
        _model->setDamage(_model->stamina->getValue() * _model->getDamage() / 50);

        // Attack from _model
        if (_model->attack(enemy, _model->getDamage())) // kill enemy
        {
            HumanView::showAttack(_model, enemy);
            CharacterView::showWasKilled(enemy);
            HumanView::congratulations(enemy->get_name());
            _model->money->append(enemy->money->getValue());
            // Levelup Skill
            if (index != _model->items.size())
            {
                _model->skills[index]->levelup(2);
                HumanView::levelupSkill(_model->items[index]);
            }
            _model->setDamage(_model->DEFAULT_DAMAGE);
            return true;
        }
        else
        {
            HumanView::showAttack(_model, enemy);
            CharacterView::showTakeDamage(enemy);
            // Levelup Skill
            if (index != _model->items.size())
            {
                _model->skills[index]->levelup(1);
                HumanView::levelupSkill(_model->items[index]);
            }
            _model->stamina->useStamina(8);
        }
    }
    return false;
}

bool HealerController::work(Character *enemy, vector<PlayerController *> players)
{
    // Check stamina
    Healer *_model = (Healer *)getModel();
    if (_model->stamina->getValue() <= 10)
    {
        HumanView::showLowStamina(_model->get_name());
        _model->stamina->regenerateStamina(3);
    }
    else
    {
        int index = useItem();
        _model->setDamage(_model->stamina->getValue() * _model->getDamage() / 50);

        // Heal the players
        for (int i = 0; i < players.size(); i++)
        {
            players[i]->getModel()->hp->heal(20);
            players[i]->getModel()->stamina->regenerateStamina(5);
        }

        // Attack from _model
        if (_model->attack(enemy, _model->getDamage())) // kill enemy
        {
            HumanView::showAttack(_model, enemy);
            CharacterView::showWasKilled(enemy);
            HumanView::congratulations(enemy->get_name());
            _model->money->append(enemy->money->getValue());
            // Levelup Skill
            if (index != _model->items.size())
            {
                _model->skills[index]->levelup(2);
                HumanView::levelupSkill(_model->items[index]);
            }
            _model->setDamage(_model->DEFAULT_DAMAGE);
            return true;
        }
        else
        {
            HumanView::showAttack(_model, enemy);
            CharacterView::showTakeDamage(enemy);
            // Levelup Skill
            if (index != _model->items.size())
            {
                _model->skills[index]->levelup(1);
                HumanView::levelupSkill(_model->items[index]);
            }
            _model->stamina->useStamina(8);
        }
    }
    return false;
}

Character *EnemyController::getModel()
{
    return this->model;
}

void EnemyController::setModel(Character *model)
{
    this->model = model;
}

State EnemyController::getCurrentState()
{
    return this->currentState;
}

void EnemyController::setCurrentState(State state)
{
    this->currentState = state;
}

State ZombieController::getNextState()
{
    this->currentState = State::Attack;
    return this->currentState;
}

bool ZombieController::work(Character *character, vector<PlayerController *> players)
{
    Zombie *_model = (Zombie *)getModel();
    if (getCurrentState() == State::Attack)
    {
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i]->type == PlayerType::Tank && players[i]->isAlive)
            {
                if (_model->attack(character, _model->getDamage() / 2))
                {
                    HumanView::showWasKilled(players[i]->getModel());
                    players[i]->isAlive = false;
                }
                else
                {
                    HumanView::showTakeDamage(players[i]->getModel());
                }
                if (_model->attack(character, _model->getDamage() / 2))
                {
                    return true;
                }
                return false;
            }
        }
        if (_model->attack(character, _model->getDamage()))
        {
            return true;
        }
        return false;
    }
    return false;
}

State HumanEnemyController::getNextState()
{
    HumanEnemy *_model = (HumanEnemy *)getModel();
    if (_model->hp->getValue() < _model->defaultHp / 2 && _model->haveItem(ItemType::Food))
    {
        currentState = State::LowHP;
        return State::LowHP;
    }
    else if (_model->stamina->getValue() < _model->defaultStamina / 2 && _model->haveItem(ItemType::StaminaBooster))
    {
        currentState = State::LowStamina;
        return State::LowStamina;
    }
    else
    {
        currentState = State::Attack;
        return State::Attack;
    }
}

bool HumanEnemyController::work(Character *character, vector<PlayerController *> players)
{
    HumanEnemy *_model = (HumanEnemy *)getModel();
    switch (getCurrentState())
    {
    case State::LowHP:
        for (int i = 0; i < _model->items.size(); i++)
        {
            if (_model->items[i]->type == ItemType::Food)
            {
                if (_model->items[i]->count > 0)
                    _model->useItem(i);
            }
        }
        break;
    case State::LowStamina:
        for (int i = 0; i < _model->items.size(); i++)
        {
            if (_model->items[i]->type == ItemType::StaminaBooster)
            {
                if (_model->items[i]->count > 0)
                    _model->useItem(i);
            }
        }
        break;
    case State::Attack:
        if (_model->stamina->getValue() > 10)
        {
            // TODO: levelup skill
            for (int i = 0; i < _model->items.size(); i++)
            {
                if (_model->items[i]->fatherType == ItemType::ThrowableItem)
                {
                    if (_model->items[i]->count > 0)
                    {
                        _model->useItem(i);
                        break;
                    }
                }
            }
            _model->setDamage(_model->stamina->getValue() * _model->getDamage() / 50);
            _model->stamina->useStamina(8);

            for (int i = 0; i < players.size(); i++)
            {
                if (players[i]->type == PlayerType::Tank && players[i]->isAlive)
                {
                    if (_model->attack(character, _model->getDamage() / 2))
                    {
                        HumanView::showWasKilled(players[i]->getModel());
                        players[i]->isAlive = false;
                    }
                    else
                    {
                        HumanView::showTakeDamage(players[i]->getModel());
                    }
                    if (_model->attack(character, _model->getDamage() / 2))
                    {
                        return true;
                    }
                    return false;
                }
            }
            if (_model->attack(character, _model->getDamage()))
            {
                return true;
            }
        }
        else
        {
            _model->stamina->regenerateStamina(3);
        }
        break;
    default:
        break;
    }
    return false;
}

State VampireZombieController::getNextState()
{
    this->currentState = State::Attack;
    return this->currentState;
}

bool VampireZombieController::work(Character *character, vector<PlayerController *> players)
{
    VampireZombie *_model = (VampireZombie *)getModel();
    if (getCurrentState() == State::Attack)
    {
        _model->hp->heal(_model->getDamage() / 2);
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i]->type == PlayerType::Tank && players[i]->isAlive)
            {
                if (_model->attack(character, _model->getDamage() / 2))
                {
                    HumanView::showWasKilled(players[i]->getModel());
                    players[i]->isAlive = false;
                }
                else
                {
                    HumanView::showTakeDamage(players[i]->getModel());
                }
                if (_model->attack(character, _model->getDamage() / 2))
                {
                    return true;
                }
                return false;
            }
        }
        if (_model->attack(character, _model->getDamage()))
        {
            return true;
        }
        return false;
    }
    return false;
}

State UltraZombieController::getNextState()
{
    this->currentState = State::Attack;
    return this->currentState;
}

bool UltraZombieController::work(Character *character, vector<PlayerController *> players)
{
    UltraZombie *_model = (UltraZombie *)getModel();
    if (getCurrentState() == State::Attack)
    {
        if (_model->attack(character, _model->getDamage()))
        {
            return true;
        }
        return false;
    }
    return false;
}

State UltraVampireZombieController::getNextState()
{
    UltraVampireZombie *_model = (UltraVampireZombie *)getModel();
    if (_model->hp->getValue() < _model->defaultHp / 2 && _model->haveItem(ItemType::Food))
    {
        currentState = State::LowHP;
        return State::LowHP;
    }
    else if (_model->stamina->getValue() < _model->defaultStamina / 2 && _model->haveItem(ItemType::StaminaBooster))
    {
        currentState = State::LowStamina;
        return State::LowStamina;
    }
    else
    {
        currentState = State::Attack;
        return State::Attack;
    }
}

bool UltraVampireZombieController::work(Character *character, vector<PlayerController *> players)
{
    UltraVampireZombie *_model = (UltraVampireZombie *)getModel();
    switch (getCurrentState())
    {
    case State::LowHP:
        for (int i = 0; i < _model->items.size(); i++)
        {
            if (_model->items[i]->type == ItemType::Food)
            {
                if (_model->items[i]->count > 0)
                    _model->useItem(i);
            }
        }
        break;
    case State::LowStamina:
        for (int i = 0; i < _model->items.size(); i++)
        {
            if (_model->items[i]->type == ItemType::StaminaBooster)
            {
                if (_model->items[i]->count > 0)
                    _model->useItem(i);
            }
        }
        break;
    case State::Attack:
        if (_model->stamina->getValue() > 5)
        {
            // TODO: levelup skill

            for (int i = 0; i < _model->items.size(); i++)
            {
                if (_model->items[i]->fatherType == ItemType::ThrowableItem)
                {
                    if (_model->items[i]->count > 0)
                    {
                        _model->useItem(i);
                        break;
                    }
                }
            }
            _model->setDamage(_model->stamina->getValue() * _model->getDamage() / 50);
            _model->stamina->useStamina(5);
            _model->hp->heal(_model->getDamage() / 2);

            for (int i = 0; i < players.size(); i++)
            {
                if (players[i]->type == PlayerType::Tank && players[i]->isAlive)
                {
                    if (_model->attack(character, _model->getDamage() / 2))
                    {
                        HumanView::showWasKilled(players[i]->getModel());
                        players[i]->isAlive = false;
                    }
                    else
                    {
                        HumanView::showTakeDamage(players[i]->getModel());
                    }
                    if (_model->attack(character, _model->getDamage() / 2))
                    {
                        return true;
                    }
                    return false;
                }
            }
            if (_model->attack(character, _model->getDamage()))
            {
                return true;
            }
        }

        else
        {
            _model->stamina->regenerateStamina(3);
        }
        break;
    default:
        break;
    }
    return false;
}
