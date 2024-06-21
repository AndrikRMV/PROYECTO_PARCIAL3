#pragma once
#include "../Character/Character.h"
#include "../Utils/Inventory.h"  // +
#include <vector>

class Enemy; //

class Player : public Character {
private:
    int level;
    int experience;
    Inventory inventory;

    void levelUp();

public:
    Player(const char _name[], int _health, int _attack, int _defense, int _speed);
    virtual void doAttack(Character *target) override;
    virtual Action takeAction(std::vector<Character*> enemies) override;
    std::string toString() override;

    void takeDamage(int damage) override;
    Character *selectTarget(std::vector<Enemy *> possibleTargets);
    void gainExperience(int exp);

    void addItemToInventory(const Item& item);
    void useItemFromInventory(int index, Character* character);
    void displayInventory() const;

    void serialize(char buffer[]);
    static Player* unserialize(char buffer[]);
    static const unsigned int BUFFER_SIZE = sizeof(level) + sizeof(experience) + sizeof(name) + sizeof(health) + sizeof(attack) + sizeof(defense) + sizeof(speed) + sizeof(isPlayer) + sizeof(isDefending);
};
