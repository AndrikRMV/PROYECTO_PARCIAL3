#pragma once
#include "Player.h"

class Warrior : public Player {
public:
    Warrior(const char _name[], int _health, int _attack, int _defense, int _speed);
    void powerAttack(Character *target);
    void doAttack(Character *target) override;
    Action takeAction(std::vector<Character*> enemies) override;
    std::string toString() override;
};
