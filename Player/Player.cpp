#include "Player.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Action.h"
#include <iostream>



//Le sufri demasiado con esta parte
Player::Player(const char _name[], int _health, int _attack, int _defense, int _speed)
        : Character(_name, _health, _attack, _defense, _speed, true), level(1), experience(0) {}

void Player::doAttack(Character *target) {
    int damage = getAttack();
    target->takeDamage(damage);
    std::cout << name << " attacks " << target->getName() << " for " << damage << " damage!" << std::endl;
}

Action Player::takeAction(std::vector<Character*> enemies) {
    Action currentAction;
    std::vector<Enemy*> enemyTargets;
    for (auto character : enemies) {
        enemyTargets.push_back(dynamic_cast<Enemy*>(character));
    }
    Character *target = selectTarget(enemyTargets);
    currentAction.target = target;
    currentAction.action = [this, target]() {
        doAttack(target);
        if (target->getHealth() <= 0) {
            gainExperience(dynamic_cast<Enemy*>(target)->getExperience());
        }
    };
    currentAction.speed = getSpeed();
    return currentAction;
}

std::string Player::toString() {
    return Character::toString() + "\nLevel: " + std::to_string(level);
}

void Player::takeDamage(int damage) {
    Character::takeDamage(damage);
}

Character *Player::selectTarget(std::vector<Enemy *> possibleTargets) {
    // Lógica para seleccionar un objetivo
    return possibleTargets.front();  // Ejemplo: selecciona el primer objetivo
}

void Player::gainExperience(int exp) {
    experience += exp;
}

void Player::addItemToInventory(const Item& item) {
    inventory.addItem(item);
}

void Player::useItemFromInventory(int index, Character* character) {
    inventory.useItem(index, character);
}

void Player::displayInventory() const {
    inventory.displayInventory();
}

void Player::serialize(char buffer[]) {
    // Implementación de la serialización
}

Player* Player::unserialize(char buffer[]) {
    // Implementación de la deserialización
    return nullptr; // Ejemplo: devuelve nullptr
}
