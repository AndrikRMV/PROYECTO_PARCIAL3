#ifndef RPG_CHARACTER_H
#define RPG_CHARACTER_H

#include <string>
#include <cstring>
#include <vector>
#include "../Combat/Action.h"

class Character {
protected:
    char name[40];
    int health;
    int maxHealth;
    int attack;
    int defense;
    int speed;
    bool isPlayer;
    bool isDefending = false;

public:
    Character(const char _name[], int _health, int _attack, int _defense, int _speed, bool _isPlayer);
    virtual ~Character() {}

    virtual void doAttack(Character *target) = 0;
    virtual void takeDamage(int damage);
    virtual Action takeAction(std::vector<Character*> enemies) = 0;

    std::string getName();
    int getHealth();
    int getAttack();
    int getDefense();
    int getSpeed();
    bool getIsPlayer();
    void heal(int amount);
    virtual std::string toString();

    void defend(bool state);
};

#endif // RPG_CHARACTER_H
