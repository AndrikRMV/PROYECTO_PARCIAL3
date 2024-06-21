#pragma once
#include "Item.h"
#include <vector>
#include "../Character/Character.h"  // Incluir Character.h

class Inventory {
private:
    std::vector<Item> items;

public:
    void addItem(const Item& item);
    void removeItem(int index);  // Método para remover ítem del inventario
    void useItem(int index, Character* character);
    void displayInventory() const;

    int size() const { return items.size(); }
    Item getItem(int index) const { return items[index]; }
};
