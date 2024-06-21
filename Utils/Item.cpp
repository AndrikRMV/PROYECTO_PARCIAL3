#include "Item.h"
#include "../Character/Character.h"  // Incluye la clase Character

Item::Item(std::string name, int effectValue)
        : name(name), effectValue(effectValue) {}

std::string Item::getName() const {
    return name;
}

int Item::getEffectValue() const {
    return effectValue;
}

void Item::use(Character* character) {
    // Aplica el efecto del ítem (por ejemplo, curar al personaje)
    character->heal(effectValue);  // Asume que Character tiene un método heal()
}
