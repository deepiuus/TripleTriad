/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** Main
*/

#include "IGames.hpp"
#include "utils/StateManager.hpp"
#include "utils/Error.hpp"
#include "states/Menu.hpp"

int main(void)
{
    try {
        triad::StateManager stateManager;
        stateManager.SetState(std::make_unique<triad::Menu>(stateManager));
        while (stateManager.IsWindowOpen()) {
            stateManager.HandleInput();
            stateManager.Update();
            stateManager.ProcessStateChange();
            stateManager.Display();
        }
    } catch (const triad::Error &e) {
        std::cerr << "Game: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}
