#ifndef RPG_ACTION_H
#define RPG_ACTION_H

#include <functional>

class Character;
using namespace std;

class Action {
public:
    int speed = 0;  // velocidad de quien realiza la accion
    Character* target = nullptr;  // Quien recibe la accion
    Character* subscriber = nullptr;  // Quien realiza la accion
    function<void(void)> action = nullptr;  // Puntero a una función que no recibe parámetros y no devuelve nada

    Action(int _speed, function<void(void)> _action, Character* _subscriber, Character* _target);
    Action();

    bool operator<(const Action& other) const;
};

#endif //RPG_ACTION_H
