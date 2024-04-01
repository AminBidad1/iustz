#include "views.hpp"


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


void CharacterView::showAttack(Character* character , Character* enemy)
{
    cout << character->get_name() << " : I damaged to " << enemy->get_name() << endl;
}

void CharacterView::showTakeDamage(Character* character)
{
    cout << character->get_name() << " : AAKH! This hurts me" << endl;
}

void CharacterView::showWasKilled(Character* character)
{
    cout << character->get_name() << " Was Killed" << endl;
}

void HumanView::showUseItem(Human* human, Item* item)
{
    cout << human->get_name() << " : I used " << item->getName() << " item" << endl;
}

void HumanView::showAppendHP(int value , Human* human)
{
    cout << human->get_name() << " : YOOHO! I got " << value << " HP" << endl;
}

void HumanView::showAppendStamina(int value , Human* human)
{
    cout << human->get_name() << " : Eyval! I got " << value << " Stamina" << endl;
}

void HumanView::showStatus(Human* human)
{
    cout << "Your HP: " << human->hp->getValue() << endl
    << "Your Stamina: " << human->stamina->getValue() << endl
    << "Your Money: " << human->money->getValue() << endl
    << "Your XP: " << human->getXp()->getValue() << endl;
}

InventoryItem HumanView::selecetItem()
{
    cout << "Items: " << endl
    << "1. Kitchen Knife" << endl
    << "2. Grande" << endl
    << "3. Molotove" << endl
    << "4. Bristle" << endl
    << "5. Firearms" << endl
    << "6. StaminaBooster" << endl
    << "7. Food" << endl
    << "8. Beverage" << endl;
    cout << "Please choose a item: ";
    int index;
    cin >> index;
    int count;
    cout << "How many? ";
    cin >> count;
    InventoryItem inventoryItem;
    inventoryItem.count = count;
    switch (index)
    {
    case 1:
        inventoryItem.type = ItemType::KitchenKnife;
        break;
    case 2:
        inventoryItem.type = ItemType::Grande;
        break;
    case 3:
        inventoryItem.type = ItemType::Molotov;
        break;
    case 4:
        inventoryItem.type = ItemType::Bristle;
        break;
    case 5:
        inventoryItem.type = ItemType::Firearms;
        break;
    case 6:
        inventoryItem.type = ItemType::StaminaBooster;
        break;
    case 7:
        inventoryItem.type = ItemType::Food;
        break;
    case 8:
        inventoryItem.type = ItemType::Beverage;
        break;
    default:
        break;
    }
    return inventoryItem;
}

void HumanView::successBuy()
{
    cout << "Successful transaction. The item added to inventory" << endl;
}

void HumanView::failedBuy()
{
    cout << "Unsuccessful transaction. You cant this item." << endl;
}

void ZombieView::showAttack(Character* character , Zombie* zombie)
{
    cout << zombie->get_name() << " : HaHa! I damaged to you! you can't beat me " <<
    character->get_name() << "!" << endl;
}

bool ShopView::stay()
{
    cout << "if you want to stay in shop please press Enter. else press Escape" << endl;
    getch();
    int input = getch();
    if (input == ESCAPE_KEY)
        return false;
    else if (input == ENTER_KEY)
        return true;
    return false;
}
