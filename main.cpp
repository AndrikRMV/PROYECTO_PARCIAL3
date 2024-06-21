#include <iostream>
#include "Player/Player.h"
#include "Player/Mage.h"
#include "Player/Warrior.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"
#include "Utils/Item.h"
#include <fstream>
#include <vector>
#include <algorithm>

// Verifica si el archivo de guardado existe
bool fileExists(const std::string &filename = "data.dat") {
    std::ifstream file(filename);
    return file.good();
}

// Lee el jugador desde el archivo de guardado
Player *readPlayerFromFile() {
    char buffer[Player::BUFFER_SIZE];
    std::ifstream readStream;
    readStream.open("data.dat", std::ios::binary);
    readStream.read(buffer, Player::BUFFER_SIZE);
    readStream.close();
    return Player::unserialize(buffer);
}

// Escribe el jugador en el archivo de guardado
void writeToFile(char buffer[], unsigned int bufferSize) {
    std::ofstream writeStream;
    writeStream.open("data.dat", std::ios::binary);
    writeStream.write(buffer, bufferSize);
    writeStream.close();
}

// Crea un nuevo jugador basado en la selección de clase
Player *createNewPlayer() {
    int classChoice;
    std::cout << "Elige tu clase:\n1. Mago\n2. Guerrero" << std::endl;
    std::cin >> classChoice;

    switch (classChoice) {
        case 1:
            return new Mage("Victor", 100, 15, 4, 3);
        case 2:
            return new Warrior("Victor", 100, 20, 5, 2);
        default:
            std::cout << "Opción inválida, se asignará Guerrero por defecto." << std::endl;
            return new Warrior("Victor", 100, 20, 5, 2);
    }
}

int main() {
    std::string resp = "";
    do {
        Player *player;
        if (fileExists()) {
            std::cout << "¡Juego guardado detectado!\n ¿Cargar? Y(sí) | cualquier otra tecla(no)" << std::endl;
            std::cin >> resp;
            if (resp == "Y" || resp == "y") {
                player = readPlayerFromFile();
                std::cout << "Jugador cargado exitosamente:\n" << player->toString() << std::endl;
            } else {
                player = createNewPlayer();
            }
        } else {
            player = createNewPlayer();
        }

        // Añadir ítems al inventario del jugador
        player->addItemToInventory(Item("Poción de salud", 50));
        player->addItemToInventory(Item("Poción de maná", 30));

        // Crear enemigos
        Enemy *enemy = new Enemy("Goblin", 60, 7, 3, 3, 120);
        Enemy *enemy2 = new Enemy("Orco", 50, 6, 2, 5, 100);

        // Añadir enemigos a los participantes
        std::vector<Character *> participants;
        participants.push_back(player);
        participants.push_back(enemy);
        participants.push_back(enemy2);

        Combat *combat = new Combat(participants);
        std::cout << "Inicio del combate" << std::endl;

        bool continueCombat = true;
        while (continueCombat) {
            // Turno del jugador
            std::cout << "Elige una acción:\n1. Atacar\n2. Defender\n3. Usar ítem\n4. Escapar" << std::endl;
            int action;
            std::cin >> action;

            switch (action) {
                case 1: {
                    // Atacar
                    std::cout << "Elige un objetivo:\n1. Goblin\n2. Orco" << std::endl;
                    int target;
                    std::cin >> target;
                    Character *enemyTarget = (target == 1) ? enemy : enemy2;
                    player->doAttack(enemyTarget);
                    if (enemyTarget->getHealth() <= 0) {
                        std::cout << enemyTarget->getName() << " ha sido derrotado!" << std::endl;
                        participants.erase(std::remove(participants.begin(), participants.end(), enemyTarget), participants.end());
                        delete enemyTarget;
                    }
                    break;
                }
                case 2:
                    // Defender
                    player->defend(true);
                    break;
                case 3:
                    // Usar ítem
                    player->displayInventory();
                    std::cout << "Elige el ítem a usar: ";
                    int itemIndex;
                    std::cin >> itemIndex;
                    player->useItemFromInventory(itemIndex, player);
                    break;
                case 4:
                    // Escapar
                    std::cout << "Intentas escapar..." << std::endl;
                    continueCombat = false;
                    break;
                default:
                    std::cout << "Acción inválida." << std::endl;
                    continue;
            }

            // Turno de los enemigos
            if (continueCombat) {
                for (auto &enemyParticipant : participants) {
                    if (!enemyParticipant->getIsPlayer()) {
                        enemyParticipant->doAttack(player);
                        if (player->getHealth() <= 0) {
                            std::cout << "¡Has sido derrotado!" << std::endl;
                            continueCombat = false;
                            break;
                        }
                    }
                }
            }

            // Desactivar defensa después del turno
            player->defend(false);

            if (participants.size() == 1) {
                continueCombat = false;
                break;
            }
        }

        // Verificar si el jugador está vivo y preguntar si quiere guardar el juego
        if (player->getHealth() > 0) {
            std::cout << "¿Quieres guardar el juego? Y(sí) | Otra tecla(no)" << std::endl;
            std::cin >> resp;
            if (resp == "Y" || resp == "y") {
                char buffer[Player::BUFFER_SIZE];
                player->serialize(buffer);
                writeToFile(buffer, Player::BUFFER_SIZE);
            }
        }

        // Liberar memoria
        delete player;
        delete combat;

        // Preguntar si el jugador quiere continuar el juego
        std::cout << "¿Quieres continuar? Y(sí) | Cualquier letra(no)" << std::endl;
        std::cin >> resp;
    } while (resp == "Y" || resp == "y");

    return 0;
}
