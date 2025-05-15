/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** Adventure
*/

#ifndef ADVENTURE_HPP_
#define ADVENTURE_HPP_

#include "../IGames.hpp"
#include "../utils/StateManager.hpp"
#include "Menu.hpp"

namespace triad
{
    class Adventure : public IGames {
        public:
            Adventure(StateManager &stateManager);
            ~Adventure() override;
            void Init() override;
            void SetKey(TKey key) override;
            void Update() override;
            void Display() override;
            void Destroy() override;

        private:
            StateManager &_stateManager;
    };
}

#endif /* !SETTINGS_HPP_ */
