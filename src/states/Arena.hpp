/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** Arena
*/

#ifndef ARENA_HPP_
#define ARENA_HPP_

#include "../IGames.hpp"
#include "../utils/StateManager.hpp"
#include "../utils/CardManager.hpp"
#include "Menu.hpp"

namespace triad
{
    class Arena : public IGames {
        public:
            Arena(StateManager &stateManager);
            ~Arena() override;
            void Init() override;
            void SetKey(TKey key) override;
            void Update() override;
            void Display() override;
            void Destroy() override;

        private:
            int width;
            int height;
            sf::RenderWindow &_window;
            sf::Sprite _sprite;
            sf::Texture _texture;
            sf::Sprite _cardSprite;
            StateManager &_stateManager;
            bool _dragging;
            sf::Vector2f _dragOffset;
    };
}

#endif /* !ARENA_HPP_ */
