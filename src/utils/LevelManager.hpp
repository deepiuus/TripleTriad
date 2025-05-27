/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** LevelManager
*/

#ifndef LEVELMANAGER_HPP_
#define LEVELMANAGER_HPP_

#include <fstream>
#include "../IGames.hpp"
#include "Error.hpp"

namespace triad
{
    enum class TLevel {
        LEVEL1,
        LEVEL2,
        LEVEL3,
        LEVEL4,
        LEVEL5,
    };
    class LevelManager {
        public:
            LevelManager();
            ~LevelManager();
            void LoadLevel();
            TLevel GetLevel() const;
            const std::vector<std::vector<char>> &GetMap() const;
            void ResetLevel();
        private:
            TLevel _currentLevel;
            std::vector<std::vector<char>> _map;
    };
}

#endif /* !LEVELMANAGER_HPP_ */
