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
#include "../utils/LevelManager.hpp"
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
            bool isCellFree(int x, int y) const;
            bool isRockAt(int x, int y) const;
            StateManager &_stateManager;
            LevelManager _levelManager;
            const std::vector<std::vector<char>> *_map;
            std::vector<sf::Vector2i> _rocks;
            sf::Vector2i _playerPos;
            int _tileSize;
    };
}

#endif /* !SETTINGS_HPP_ */
