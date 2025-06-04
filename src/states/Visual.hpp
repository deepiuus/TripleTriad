/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** Visual
*/

#ifndef VISUAL_HPP_
#define VISUAL_HPP_

#include "../IGames.hpp"
#include "../utils/StateManager.hpp"
#include "../utils/LevelManager.hpp"
#include "Menu.hpp"
#include "Adventure.hpp"

namespace triad
{
    class Visual : public IGames {
        public:
            Visual(StateManager &stateManager);
            ~Visual() override;
            void Init() override;
            void SetKey(TKey key) override;
            void Update() override;
            void Display() override;
            void Destroy() override;

        private:
            StateManager &_stateManager;
            LevelManager &_levelManager;
            sf::Font _font;
            sf::Text _text;
    };
}

#endif /* !VISUAL_HPP_ */
