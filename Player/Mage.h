#pragma once
#include "Player.h"

class Mage : public Player {
public:
    Mage(const char _name[], int _health, int _attack, int _defense, int _speed);
    void castSpell(Character *target);
    void doAttack(Character *target) override;
    Action takeAction(std::vector<Character*> enemies) override;
    std::string toString() override;
};
