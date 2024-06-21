#include "Character.h"
#include <iostream>

Character::Character(const char _name[], int _health, int _attack, int _defense, int _speed, bool _isPlayer)
        : health(_health), attack(_attack), defense(_defense), speed(_speed), isPlayer(_isPlayer) {
    std::strcpy(name, _name);
    maxHealth = _health; // Asignación de la salud máxima
}

std::string Character::getName() {
    return name;
}

int Character::getHealth() {
    return health;
}

int Character::getAttack() {
    return attack;
}

int Character::getDefense() {
    return defense;
}

int Character::getSpeed() {
    return speed;
}

bool Character::getIsPlayer() {
    return isPlayer;
}

std::string Character::toString() {
    std::string aux = "Name: ";
    aux.append(name).append("\nHealth: " + std::to_string(health) + "\nAttack: " + std::to_string(attack) + "\nDefense: " + std::to_string(defense) + "\nSpeed: " + std::to_string(speed));
    return aux;
}

void Character::defend(bool state) {
    isDefending = state;
}

void Character::takeDamage(int damage) {
    if (isDefending) {
        damage /= 2; // Reduce el daño a la mitad si está defendiendo
    }
    health -= damage;
    std::cout << name << " took " << damage << " damage!" << std::endl;
}

void Character::heal(int amount) {
    health += amount;
    if (health > maxHealth) {
        health = maxHealth;
    }
    std::cout << name << " healed for " << amount << " health!" << std::endl;
}
