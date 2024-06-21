#include "Warrior.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Action.h"
#include <iostream>

Warrior::Warrior(const char _name[], int _health, int _attack, int _defense, int _speed)
        : Player(_name, _health, _attack, _defense, _speed) {}

void Warrior::powerAttack(Character *target) {
    // Implementación de ataque poderoso del guerrero
}

void Warrior::doAttack(Character *target) {
    // Implementación de ataque del guerrero
    int damage = getAttack(); // Usar directamente getAttack para obtener el valor del ataque
    target->takeDamage(damage);
    std::cout << getName() << " swings their sword at " << target->getName() << " for " << damage << " damage!" << std::endl;
}

Action Warrior::takeAction(std::vector<Character*> enemies) {
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

std::string Warrior::toString() {
    return Player::toString() + "\nClass: Warrior";
}
