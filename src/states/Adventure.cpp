/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** Adventure
*/

#include "Adventure.hpp"

namespace triad
{
    Adventure::Adventure(StateManager &stateManager) : _stateManager(stateManager),
        _levelManager(), _map(nullptr), _rocks(), _playerPos(0, 0), _tileSize(64)
    {
    }

    Adventure::~Adventure()
    {
    }

    void Adventure::Init()
    {
        try {
            _levelManager.LoadLevel();
            _map = &_levelManager.GetMap();
            _rocks.clear();
            for (size_t y = 0; y < _map->size(); y++) {
                for (size_t x = 0; x < (*_map)[y].size(); x++) {
                    if ((*_map)[y][x] == 'P') {
                        _playerPos = sf::Vector2i(x, y);
                    }
                    if ((*_map)[y][x] == 'X') {
                        _rocks.push_back(sf::Vector2i(x, y));
                    }
                }
            }
        } catch (const Error &e) {
            _stateManager.GetWindow().close();
            throw Error("Failed to load level: " + std::string(e.what()));
        }
    }

    bool Adventure::isCellFree(int x, int y) const
    {
        char cell = (*_map)[y][x];
        if ((cell == ' ' || cell == 'W' || cell == 'P') && !isRockAt(x, y))
            return true;
        if (cell == 'X' && !isRockAt(x, y))
            return true;
        return false;
    }

    bool Adventure::isRockAt(int x, int y) const
    {
        for (const auto& rock : _rocks) {
            if (rock.x == x && rock.y == y) {
                return true;
            }
        }
        return false;
    }

    void Adventure::SetKey(TKey key)
    {
        int dx = 0;
        int dy = 0;
        switch (key) {
            case TKey::ESCAPE:
                _stateManager.RequestStateChange(std::make_unique<Menu>(_stateManager));
                break;
            case TKey::UP:
                dy = -1;
                break;
            case TKey::DOWN:
                dy = 1;
                break;
            case TKey::LEFT:
                dx = -1;
                break;
            case TKey::RIGHT:
                dx = 1;
                break;
            default:
                return;
        }
        if (_map) {
            int newX = _playerPos.x + dx;
            int newY = _playerPos.y + dy;
            if (newY >= 0 && newY < static_cast<int>(_map->size()) &&
                newX >= 0 && newX < static_cast<int>((*_map)[newY].size())) {
                if (isRockAt(newX, newY)) {
                    int rockX = newX + dx;
                    int rockY = newY + dy;
                    if (rockY >= 0 && rockY < static_cast<int>(_map->size()) &&
                        rockX >= 0 && rockX < static_cast<int>((*_map)[rockY].size()) &&
                        isCellFree(rockX, rockY) && ((*_map)[rockY][rockX] != 'W')) {
                        for (auto& rock : _rocks) {
                            if (rock.x == newX && rock.y == newY) {
                                rock.x = rockX;
                                rock.y = rockY;
                                break;
                            }
                        }
                        _playerPos.x = newX;
                        _playerPos.y = newY;
                    }
                } else if (isCellFree(newX, newY)) {
                    _playerPos.x = newX;
                    _playerPos.y = newY;
                }
            }
        }
    }

    void Adventure::Update()
    {
    }

    void Adventure::Display()
    {
        sf::Vector2f offset(
            (_stateManager.GetWindow().getSize().x - _map->at(0).size() * _tileSize) / 2,
            (_stateManager.GetWindow().getSize().y - _map->size() * _tileSize) / 2
        );
        sf::Texture floorTexture;
        if (!floorTexture.loadFromFile("assets/sprites/floor.png")) {
            throw Error("Failed to load floor texture");
        }
        sf::Texture wallTexture;
        _stateManager.GetWindow().clear(sf::Color::Yellow);
        if (!wallTexture.loadFromFile("assets/sprites/wall.png")) {
            throw Error("Failed to load wall texture");
        }
        sf::Texture rockTexture;
        if (!rockTexture.loadFromFile("assets/sprites/rock.png")) {
            throw Error("Failed to load rock texture");
        }
        sf::Texture waifuTexture;
        if (!waifuTexture.loadFromFile("assets/sprites/WaifuChibi.png")) {
            throw Error("Failed to load waifu texture");
        }
        sf::Texture chadTexture;
        if (!chadTexture.loadFromFile("assets/sprites/ChadChibi.png")) {
            throw Error("Failed to load chad texture");
        }
        sf::Sprite chadSprite(chadTexture);
        sf::Sprite waifuSprite(waifuTexture);
        sf::Sprite floorSprite(floorTexture);
        sf::Sprite wallSprite(wallTexture);
        sf::Sprite rockSprite(rockTexture);
        for (size_t y = 0; y < _map->size(); y++) {
            for (size_t x = 0; x < (*_map)[y].size(); x++) {
                floorSprite.setScale(4.0f, 4.0f);
                floorSprite.setPosition(offset.x + x * _tileSize, offset.y + y * _tileSize);
                _stateManager.GetWindow().draw(floorSprite);
                if (x == _playerPos.x && y == _playerPos.y) {
                    chadSprite.setScale(1.0f, 1.0f);
                    chadSprite.setPosition(offset.x + x * _tileSize, offset.y + y * _tileSize);
                    _stateManager.GetWindow().draw(chadSprite);
                }
                switch ((*_map)[y][x]) {
                    case ' ':
                        break;
                    case '#':
                        wallSprite.setScale(4.0f, 4.0f);
                        wallSprite.setPosition(offset.x + x * _tileSize, offset.y + y * _tileSize);
                        _stateManager.GetWindow().draw(wallSprite);
                        break;
                    case 'X':
                        break;
                    case 'W':
                        waifuSprite.setScale(1.0f, 1.0f);
                        waifuSprite.setPosition(offset.x + x * _tileSize, offset.y + y * _tileSize);
                        _stateManager.GetWindow().draw(waifuSprite);
                        break;
                    default:
                        break;
                }
            }
        }
        for (const auto& rock : _rocks) {
            rockSprite.setScale(4.0f, 4.0f);
            rockSprite.setPosition(offset.x + rock.x * _tileSize, offset.y + rock.y * _tileSize);
            _stateManager.GetWindow().draw(rockSprite);
        }
        _stateManager.GetWindow().display();
    }

    void Adventure::Destroy()
    {
    }
}
