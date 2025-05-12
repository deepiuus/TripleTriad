/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "../IGames.hpp"
#include "../utils/StateManager.hpp"

namespace triad
{
    class Game : public IGames {
        public:
            Game(StateManager &stateManager);
            ~Game() override;
            void Init() override;
            void SetKey(TKey key) override;
            void Update() override;
            void Display() override;
            void Destroy() override;

        private:
            StateManager &_stateManager;
    };
}

#endif /* !GAME_HPP_ */
