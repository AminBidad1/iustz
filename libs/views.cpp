#include "views.hpp"

void CharacterView::showAttack(Character* character , Character* enemy)
{
    cout << character->get_name() << " : I damaged to " << enemy->get_name() << endl;
}

void CharacterView::showTakeDamage(Character* character)
{
    cout << character->get_name() << " : AAKH! This hurts me" << endl;
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

 void ZombieView::showAttack(Character* character , Zombie* zombie)
{
    cout <<zombie->get_name() << " : HaHa! I damaged to you! you can't beat me " <<
    character->get_name() << "!" << endl;
}
