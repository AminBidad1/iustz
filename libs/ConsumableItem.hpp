#include <iostream>
using namespace std;
class ConsumableItem
{
private:
    string name;
    int value;
    int price;

public:
    ConsumableItem();
    ConsumableItem(string name, int price);

    void setName(string name);
    string getName() const;

    void setValue(int value);
    int getValue() const;

    void setPrice(int price);
    int getPrice() const;

    virtual void consume();
};

class ManaBooster : public ConsumableItem
{
public:
    void consume();
};

class Food : public ConsumableItem
{
public:
    void consume();
};

class Beverage : public ConsumableItem
{
public:
    void consume();
};