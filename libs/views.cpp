#include "views.hpp"
void gotoxy(int x, int y)
{
    cout << "\033[" << y << ";" << x << "H";
}
void ClearTerminal()
{
    for (int j = 20; j < 50; j++)
    {
        gotoxy(0, j);
        cout << operator_space(" ", 80);
    }

    gotoxy(0, 20);
}

string operator_space(string str, int count)
{
    string result = "";
    for (int i = 0; i < count; i++)
    {
        result += str;
    }
    return result;
}

void ClearEnemyStatus()
{
    gotoxy(88, 2);
    cout << operator_space(" ", 28);
    for (int i = 4; i < 9; i++)
    {
        gotoxy(71, i);
        cout << operator_space(" ", 49);
    }
    for (int i = 10; i <= 17; i++)
    {
        gotoxy(71, i);
        cout << operator_space(" ", 49);
    }
}
void WeaponTableStatus()
{
    for (int i = 90; i <= 140; i++)
    {
        gotoxy(i, 20);
        cout << "-";
        gotoxy(i, 40);
        cout << "-";
        gotoxy(i, 22);
        cout << "-";
    }
    for (int j = 20; j <= 40; j++)
    {
        gotoxy(90, j);
        cout << "|";
        gotoxy(140, j);
        cout << "|";
    }
}
// void ClearWeaponTableStatus()
// {
//     for (int i = 20; i < 22; i++)
//     {
//         gotoxy(90, i);
//         cout << operator_space(" ", 48);
//     }
//     for (int i = 23; i < 40; i++)
//     {
//         gotoxy(90,i);
//         cout<<operator_space(" ",48);
//     }
// }
void TableSection()
{
    gotoxy(2, 7);
    cout << "XP";
    gotoxy(2, 8);
    cout << "Att Dmg";
    gotoxy(2, 5);
    cout << color::rize("Stamina", "Blue", "");
    gotoxy(2, 6);
    cout << "Money";
    gotoxy(2, 4);
    cout << color::rize("HP", "Green", "");
    gotoxy(2, 10);
    cout << "List of";
    gotoxy(2, 11);
    cout << "items";
    gotoxy(18, 6);
    cout << '-';
    gotoxy(18, 7);
    cout << '-';
    gotoxy(18, 8);
    cout << '-';
    for (int i = 0; i < 140; i++)
    {
        gotoxy(i, 0);
        cout << "-";
        gotoxy(i, 9);
        cout << "-";
    }
    for (int i = 2; i < 19; i++)
    {
        gotoxy(70, i);
        cout << "|";
        gotoxy(0, i);
        cout << "|";
        gotoxy(140, i);
        cout << "|";
    }
    for (int i = 0; i < 140; i++)
    {
        gotoxy(i, 18);
        cout << "-";
        gotoxy(i, 3);
        cout << "-";
    }
    gotoxy(0, 3);
    cout << "|";
    gotoxy(70, 3);
    cout << "|";
    gotoxy(140, 3);
    cout << "|";
    for (int i = 4; i < 18; i++)
    {
        gotoxy(10, i);
        cout << "|";
    }
}
void ShowValueCharacter(int value, int row, int column, bool flag_1, int defaultValue)
{

    int citeron = defaultValue / 10;
    bool flag_2 = false;
    if (value < citeron)
    {
        gotoxy(row, column);
        cout << operator_space(" ", 25);
        gotoxy(row, column);
        cout << color::rize("[!.........]", "Red", "");
        flag_2 = true;
    }
    if (!flag_2)
    {
        gotoxy(row, column);
        cout << operator_space(" ", 25);
        gotoxy(row, column);
        cout << "[";
        for (int i = 0; i < (value / citeron); i++)
        {
            gotoxy(row + 1 + i, column);
            cout << color::rize(" ", "", "Blue");
        }
        int counter = 0;
        for (int i = 0; i < 10 - (value / citeron); i++)
        {
            counter++;
            gotoxy(row + 1 + (value / citeron) + i, column);
            cout << color::rize(" ", "", "Red");
        }
        gotoxy(row + 1 + (value / citeron) + counter, column);
        cout << "]";
        if (flag_1)
        {
            gotoxy((row * 2) + 1, column);
            cout << operator_space(" ", 23);
            gotoxy((row * 2) + 1, column);
            cout << operator_space(" ", 13) << value << " %";
        }
    }
    if (!flag_1)
    {
        gotoxy(78, 6);
        cout << '-';
        gotoxy(78, 7);
        cout << '-';
        gotoxy(78, 8);
        cout << '-';
        gotoxy(96, 6);
        cout << '-';
        gotoxy(96, 7);
        cout << '-';
    }
}
void ClearPlayerItems()
{
    for (int i = 10; i < 18; i++)
    {
        gotoxy(12, i);
        cout << operator_space(" ", 57);
    }
}
void ShowWeaponStatus(vector<InventoryItem *> items, int index)
{
    int start = (28 - items[index]->item->getName().size()) / 2;
    gotoxy(91, 21);
    for (int i = 91; i <= 91 + start; i++)
    {
        cout << ' ';
    }
    cout << items[index]->item->getName();
    for (int i = 91 + start + items[index]->item->getName().size(); i < 118; i++)
    {
        cout << ' ';
    }
    if (items[index]->fatherType == ItemType::ConsumableItem)
    {
        ConsumableItem *consumableItem = (ConsumableItem *)items[index]->item;
        gotoxy(91, 23);
        cout << "Booster: " << consumableItem->getValue() << "       ";
        gotoxy(91, 24);
        cout << "                   ";
    }
    if (items[index]->fatherType == ItemType::ThrowableItem)
    {
        ThrowableItem *throwableItem = (ThrowableItem *)items[index]->item;
        gotoxy(91, 23);
        cout << "Damage: " << throwableItem->getDamage() << "       ";
        gotoxy(91, 24);
        cout << "Miss Percent : " << throwableItem->getMiss_percent() << "%      ";
    }
    gotoxy(0, 22 + index);
    // if(items[index]->fatherType==ItemType::ThrowableItem)
}
void PrintByColorItem(int target, vector<InventoryItem *> items)
{
    for (int i = 0; i < items.size(); i++)
    {
        gotoxy(0, 21 + i);
        if (items[i]->count != 0)
        {
            if (i == target)
            {
                cout << color::rize(items[i]->item->getName(), "", "Red") << endl;
                ShowWeaponStatus(items, i);
            }
            else
            {
                cout << color::rize(items[i]->item->getName(), "", "Default") << endl;
            }
        }
    }
}
#if defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}
#endif

void CharacterView::showAttack(Character *character, Character *enemy)
{
    // cout << character->get_name() << " : I damaged to " << enemy->get_name() << endl;
}

void CharacterView::showTakeDamage(Character *character)
{
    // cout << character->get_name() << " : AAKH! This hurts me" << endl;
}

void CharacterView::showWasKilled(Character *character)
{
    ClearEnemyStatus();
    // cout << character->get_name() << " Was Killed" << endl;
}

void CharacterView::showStatus(Character *character, EnemyType type)
{
    gotoxy(88, 2);
    cout << "Enemy :" << character->get_name();
    gotoxy(96, 4);
    cout << operator_space(" ", 11);
    ShowValueCharacter(character->hp->getValue(), 72, 4, false, character->hp->MAX_VALUE);
    gotoxy(96, 4);
    cout << character->hp->getValue();
    gotoxy(96, 5);
    cout << operator_space(" ", 12);
    gotoxy(96, 8);
    cout << character->getDamage();
    if (type == EnemyType::HumanEnemy)
    {
        HumanEnemy *human = (HumanEnemy *)character;
        bool flag = false;
        static int increase = 0;
        ShowValueCharacter(human->stamina->getValue(), 72, 5, false, human->stamina->MAX_VALUE);
        gotoxy(96, 5);
        cout << human->stamina->getValue();
        string str = "";
        for (int i = 0; i < human->items.size(); i++)
        {
            str += to_string(human->items[i]->count) + " * " + human->items[i]->item->getName() + ",";
            for (int j = 0; j < str.size(); j++)
            {
                if (j < 48)
                {
                    gotoxy(72 + j, 10 + increase);
                    cout << str[j];
                }
                else
                {
                    str.erase(0, 47);
                    increase++;
                }
                if (i == human->items.size() - 1)
                {
                    gotoxy(72 + j, 10 + increase);
                    cout << str[j];
                }
            }
        }
        increase = 0;
        cout << endl;
    }
    else
    {
        gotoxy(96, 13);
        cout << "-";
    }
}

void HumanView::showUseItem(Item *item)
{
    // cout << "You successfully used " << item->getName() << " item" << endl;
}

void HumanView::failedUseItem(Item *item)
{
    // cout << "You can't use " << item->getName() << ". because you don't have it" << endl;
}

void HumanView::showAppendHP(int value, Human *human)
{
    // cout << human->get_name() << " : YOOHO! I got " << value << " HP" << endl;
}

void HumanView::showAppendStamina(int value, Human *human)
{
    // cout << human->get_name() << " : Eyval! I got " << value << " Stamina" << endl;
}

void HumanView::showStatus(Human *human)
{
    WeaponTableStatus();
    HumanView::showInventory(human->items);
    gotoxy(32, 2);
    cout << operator_space(" ", 20);
    gotoxy(32, 2);
    cout << human->get_name() << " : ";
    ShowValueCharacter(human->hp->getValue(), 12, 4, true, human->hp->MAX_VALUE);
    ShowValueCharacter(human->stamina->getValue(), 12, 5, true, human->stamina->MAX_VALUE);
    gotoxy(38, 6);
    cout << operator_space(" ", 11);
    gotoxy(38, 6);
    cout << human->money->getValue();
    gotoxy(38, 7);
    cout << operator_space(" ", 11);
    gotoxy(38, 7);
    cout << human->getXp()->getValue();
    gotoxy(38, 8);
    cout << human->getDamage();
    gotoxy(0, 20);
}

InventoryItem *HumanView::selecetItem()
{
    int target = 3;
    ClearTerminal();
    bool shouldExit = false;
    for (int i = MIN_ITEM_INDEX; i <= MAX_ITEM_INDEX; i++)
    {
        if (target==i)
            cout << operator_space(" ", 5) << color::rize(to_string(target-2) + ". " + itemTypeMap(ItemType(target)), "", "Red") << endl;
        else
            cout << operator_space(" ", 5) << i - MIN_ITEM_INDEX + 1 << ". " << itemTypeMap(ItemType(i)) << endl;
    }
    while (!shouldExit)
    {
        char choice = getch();
        switch (choice)
        {
        case UP_KEY:
            gotoxy(0, 20);
            if (target == 3)
                target = 9;
            else
                target--;
            for (int i = MIN_ITEM_INDEX; i <= MAX_ITEM_INDEX; i++)
            {
                if (i == target)
                    cout << operator_space(" ", 5) << color::rize(to_string(target-2) + ". " + itemTypeMap(ItemType(target)), "", "Red") << endl;
                else
                    cout << operator_space(" ", 5) << i - MIN_ITEM_INDEX + 1 << ". " << itemTypeMap(ItemType(i)) << endl;
            }
            break;
        case DOWN_KEY:
            gotoxy(0, 20);
            if (target == 9)
                target = 3;
            else
                target++;
            for (int i = MIN_ITEM_INDEX; i <= MAX_ITEM_INDEX; i++)
            {
                if (i == target)
                    cout << operator_space(" ", 5) << color::rize(to_string(target-2) + ". " + itemTypeMap(ItemType(target)), "", "Red") << endl;
                else
                    cout << operator_space(" ", 5) << i - MIN_ITEM_INDEX + 1 << ". " << itemTypeMap(ItemType(i)) << endl;
            }
            break;
        case ENTER_KEY:
            shouldExit = true;
            break;
        default:
            break;
        }
    }
    int choice;
    choice = target -2;
    int count;
    cout << "How many? ";
    cin >> count;
    InventoryItem *inventoryItem = new InventoryItem();
    inventoryItem->count = count;
    int index = choice + MIN_ITEM_INDEX - 1;
    inventoryItem->type = ItemType(index);
    if (MIN_THROWABLE_ITEM_INDEX <= index && index <= MAX_THROWABLE_ITEM_INDEX)
    {
        inventoryItem->fatherType = ItemType::ThrowableItem;
    }
    else if (MIN_CONSUMABLE_ITEM_INDEX <= index && index <= MAX_CONSUMABLE_ITEM_INDEX)
    {
        inventoryItem->fatherType = ItemType::ConsumableItem;
    }

    return inventoryItem;
}

void HumanView::successBuy()
{
    ClearTerminal();
    cout << "Successful transaction. The item added to inventory" << endl;
}

void HumanView::failedBuy()
{
    ClearTerminal();
    cout << "Unsuccessful transaction. You can't buy this item." << endl;
}

void HumanView::showInventory(vector<InventoryItem *> items)
{
    ClearPlayerItems();
    // ClearTerminal();
    // cout << "Inventory items: " << endl;
    string str = "";
    int counter = 0;
    int increase = 0;
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->count > 0)
            str += to_string(i + 1) + " - " + items[i]->item->getName() + " : " + to_string(items[i]->count) + ", ";
        for (int j = 0; j < str.size(); j++)
        {
            if (j <= 56)
            {
                gotoxy(12 + j, 10 + increase);
                cout << str[j];
            }
            if (str.size() != 0 && i != 0 && i == items.size() - 1 && j > 56)
            {
                gotoxy(12 + counter, 11 + increase);
                cout << str[j];
                counter++;
            }
            if (j > 56)
            {
                str.erase(0, 56);
                increase++;
            }
        }
    }
    increase = 0;
}

int HumanView::selectInventoryItem(vector<InventoryItem *> items)
{
    ClearTerminal();
    int input = 0;
    // if (items[0]->count != 0)
    //     input = 0;
    // else
    //     input = 1;
    while (items.size() != 0 && items[input]->count == 0 && input != items.size() - 1)
    {
        input++;
    }
    PrintByColorItem(input, items);
    bool shouldEXIT = false;
    while (!shouldEXIT)
    {
        char choice = _getch();
        switch (choice)
        {
        case UP_KEY:
            if (input == 0)
            {
                input = items.size() - 1;
                while (items[input]->count == 0 && input != 0)
                {
                    input--;
                }
            }
            else
            {
                int FirstInput = input;
                input--;
                while (items[input]->count == 0 && input != FirstInput)
                {
                    if (input != 0)
                        input--;
                    else
                        input = items.size() - 1;
                }
            }
            PrintByColorItem(input, items);
            break;

        case DOWN_KEY:
            if (input == items.size() - 1)
            {
                input = 0;
                while (items[input]->count == 0 && input != items.size() - 1)
                {
                    input++;
                }
            }
            else
            {
                int FirstInput = input;
                input++;
                while (items[input]->count == 0 && input != FirstInput)
                {
                    if (input != items.size() - 1)
                        input++;
                    else
                        input = 0;
                }
            }
            PrintByColorItem(input, items);
            break;

        case 'p':
            input = items.size();
            shouldEXIT = true;
            break;

        default:
            continue;

        case ENTER_KEY:
            shouldEXIT = true;
            break;
        }
    }
    showInventory(items);
    ClearTerminal();
    return input;
}

void HumanView::showLowStamina(string name)
{
    gotoxy(0, 23);
    cout << name << "! Your Stamina is very low and you can't damage to your enemy" << endl;
}

void HumanView::congratulations(string enemy_name)
{
    // cout << "Congratulations! you Kill " << enemy_name << ". A stronger enemy is coming" << endl;
}

void HumanView::levelupSkill(InventoryItem *inventoryItem)
{
    AttackingItem *item = (AttackingItem *)inventoryItem->item;
    // cout << "Your  " << item->getName() << " skill has improved. "
    //  << "miss percent of " << item->getName() << " : " << item->getMiss_percent() << endl;
}

void ZombieView::showAttack(Character *character, Zombie *zombie)
{
    // cout << zombie->get_name() << " : HaHa! I damaged to you! you can't beat me " << character->get_name() << "!" << endl;
}

void ZombieView::showStatus(Zombie *zombie)
{
    gotoxy(45, 2);
    cout << zombie->get_name() << " ::  ";
    gotoxy(45, 3);
    cout << zombie->hp->getValue() << "hp  ";
    gotoxy(45, 4);
    cout << zombie->getDamage() << "dg";
    // cout << zombie->get_name() << " ::  " << zombie->hp->getValue() << "hp  "
    //      << zombie->getDamage() << "dg" << endl;
}

bool ShopView::stay()
{
    cout << "if you want to stay in shop please press Enter. else press Escape" << endl;
    getch();
    int input = getch();
    if (input == ESCAPE_KEY)
    {
        ClearTerminal();
        return false;
    }
    else if (input == ENTER_KEY)
    {
        ClearTerminal();
        return true;
    }
    return false;
}

ShopSection ShopView::buySection()
{

    gotoxy(0, 20);
    while (true)
    {
        cout << "Shop sections: (Toggle the number on your keyboard to go on the section)" << endl
             << "1. Buy new items" << endl
             << "2. Sell your stuff" << endl
             << "3. Leave" << endl;
        char choice = _getch();
        if (choice == '1')
            return ShopSection::Buy;
        if (choice == '2')
            return ShopSection::Sell;
        if (choice == '3')
        {
            gotoxy(18, 19);
            cout << "        ";
            return ShopSection::Leave;
        }
        cout << endl
             << "Enter a valid input!" << endl;
    }
}

int ShopView::sellItems(Human *player)
{
    int input;
    while (true)
    {
        HumanView::showInventory(player->items);
        gotoxy(0, 20);
        cout << "Choose items to sell or enter (" << player->items.size() + 1 << ") to leave: ";
        cin >> input;
        if (input > 0 && input <= player->items.size() + 1)
        {
            break;
        }
        cout << endl
             << "Enter a valid input!" << endl;
    }
    input--;
    if (input == player->items.size())
        return -1;
    else
    {
        return input;
    }
}