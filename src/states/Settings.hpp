/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include "../IGames.hpp"
#include "../utils/StateManager.hpp"

namespace triad
{
    class Settings : public IGames {
        public:
            Settings(StateManager &stateManager);
            ~Settings() override;
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
