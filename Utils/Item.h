#pragma once
#include <string>

class Character;  // Forward declaration

class Item {
private:
    std::string name;
    int effectValue;  // Valor del efecto del ítem (e.g., cantidad de curación)

public:
    Item(std::string name, int effectValue);
    std::string getName() const;
    int getEffectValue() const;
    void use(Character* character);  // Método para usar el ítem
};
