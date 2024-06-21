#include "Mage.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Action.h"
#include <iostream>

Mage::Mage(const char _name[], int _health, int _attack, int _defense, int _speed)
        : Player(_name, _health, _attack, _defense, _speed) {}

void Mage::castSpell(Character *target) {
    // Implementación de lanzamiento de hechizo
}

void Mage::doAttack(Character *target) {
    // Implementación de ataque del mago
    int damage = getAttack(); // Usar directamente getAttack para obtener el valor del ataque
    target->takeDamage(damage);
    std::cout << getName() << " casts a spell on " << target->getName() << " for " << damage << " damage!" << std::endl;
}

Action Mage::takeAction(std::vector<Character*> enemies) {
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

std::string Mage::toString() {
    return Player::toString() + "\nClass: Mage";
}
