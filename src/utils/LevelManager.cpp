/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** LevelManager
*/

#include "LevelManager.hpp"

namespace triad
{
    LevelManager::LevelManager(StateManager &stateManager)
        : _currentLevel(TLevel::LEVEL1), _map(), _stateManager(stateManager)
    {
    }

    LevelManager::~LevelManager()
    {
    }

    void LevelManager::LoadLevel()
    {
        std::ifstream mapFile;
        std::string line;
        std::string fileName;

        switch (_currentLevel) {
            case TLevel::LEVEL1: fileName = "maps/level_1.txt"; break;
            case TLevel::LEVEL2: fileName = "maps/level_2.txt"; break;
            case TLevel::LEVEL3: fileName = "maps/level_3.txt"; break;
            case TLevel::LEVEL4: fileName = "maps/level_4.txt"; break;
            case TLevel::LEVEL5: fileName = "maps/level_5.txt"; break;
            default: throw Error("Unknown level");
        }
        _map.clear();
        mapFile.open(fileName);
        if (!mapFile.is_open()) {
            throw Error("Failed to open level file: " + fileName);
        }
        while (std::getline(mapFile, line)) {
            std::vector<char> row(line.begin(), line.end());
            _map.push_back(row);
        }
        mapFile.close();
    }

    void LevelManager::NextLevel()
    {
        switch (_currentLevel) {
            case TLevel::LEVEL1:
                _currentLevel = TLevel::LEVEL2;
                break;
            case TLevel::LEVEL2:
                _currentLevel = TLevel::LEVEL3;
                break;
            case TLevel::LEVEL3:
                _currentLevel = TLevel::LEVEL4;
                break;
            case TLevel::LEVEL4:
                _currentLevel = TLevel::LEVEL5;
                break;
            case TLevel::LEVEL5:
                _stateManager.RequestStateChange(std::make_unique<Menu>(_stateManager));
                break;
            default: break;
        }
        LoadLevel();
    }

    TLevel LevelManager::GetLevel() const
    {
        return _currentLevel;
    }

    const std::vector<std::vector<char>> &LevelManager::GetMap() const
    {
        return _map;
    }

    void LevelManager::ResetLevel()
    {
    }
}
