#include "Inventory.h"
#include <iostream>

void Inventory::addItem(const Item& item) {
    items.push_back(item);
}

void Inventory::removeItem(int index) {
    if (index >= 0 && index < items.size()) {
        items.erase(items.begin() + index);
    }
}

void Inventory::useItem(int index, Character* character) {
    if (index >= 0 && index < items.size()) {
        Item item = items[index];
        item.use(character);
        items.erase(items.begin() + index);
        std::cout << character->getName() << " used " << item.getName() << " and restored " << item.getEffectValue() << " health points." << std::endl;
    } else {
        std::cout << "Invalid item index." << std::endl;
    }
}

void Inventory::displayInventory() const {
    for (int i = 0; i < items.size(); ++i) {
        std::cout << i << ". " << items[i].getName() << " (Effect Value: " << items[i].getEffectValue() << ")" << std::endl;
    }
}
