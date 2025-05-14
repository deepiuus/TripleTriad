/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** StateManager
*/

#ifndef STATEMANAGER_HPP_
#define STATEMANAGER_HPP_

#include <memory>
#include "../IGames.hpp"

namespace triad
{
    class StateManager {
        public:
            StateManager();
            bool IsWindowOpen() const;
            void HandleInput();
            IGames *GetCurrentState() const;
            sf::RenderWindow &GetWindow();
            void SetState(std::unique_ptr<IGames> state);
            void RequestStateChange(std::unique_ptr<IGames> nextState);
            void ProcessStateChange();
            void Update();
            void Display();
        private:
            std::unique_ptr<IGames> _currentState;
            std::unique_ptr<IGames> _nextState;
            sf::RenderWindow _window;
    };
}

#endif /* !STATEMANAGER_HPP_ */
