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
        _levelManager(), tileSize(64)
    {
    }

    Adventure::~Adventure()
    {
    }

    void Adventure::Init()
    {
        try {
            _levelManager.LoadLevel();
        } catch (const Error &e) {
            _stateManager.GetWindow().close();
            throw Error("Failed to load level: " + std::string(e.what()));
        }
    }

    void Adventure::SetKey(TKey key)
    {
        switch (key) {
            case TKey::ESCAPE:
                _stateManager.RequestStateChange(std::make_unique<Menu>(_stateManager));
                break;
            case TKey::UP:
//              MovePlayer(0, -1);
                break;
            case TKey::DOWN:
//              MovePlayer(0, 1);
                break;
            case TKey::LEFT:
//              MovePlayer(-1, 0);
                break;
            case TKey::RIGHT:
//              MovePlayer(1, 0);
                break;
            default:
                break;
        }
    }

    void Adventure::Update()
    {
    }

    void Adventure::Display()
    {
        const std::vector<std::vector<char>> &_map = _levelManager.GetMap();
        sf::Vector2f offset(
            (_stateManager.GetWindow().getSize().x - _map[0].size() * tileSize) / 2,
            (_stateManager.GetWindow().getSize().y - _map.size() * tileSize) / 2
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
        if (!_levelManager.GetMap().empty()) {
            for (size_t y = 0; y < _levelManager.GetMap().size(); y++) {
                for (size_t x = 0; x < _levelManager.GetMap()[y].size(); x++) {
                    floorSprite.setScale(4.0f, 4.0f);
                    floorSprite.setPosition(offset.x + x * tileSize, offset.y + y * tileSize);
                    _stateManager.GetWindow().draw(floorSprite);
                    switch (_levelManager.GetMap()[y][x]) {
                        case ' ':
                            break;
                        case '#':
                            wallSprite.setScale(4.0f, 4.0f);
                            wallSprite.setPosition(offset.x + x * tileSize, offset.y + y * tileSize);
                            _stateManager.GetWindow().draw(wallSprite);
                            break;
                        case 'X':
                            rockSprite.setScale(4.0f, 4.0f);
                            rockSprite.setPosition(offset.x + x * tileSize, offset.y + y * tileSize);
                            _stateManager.GetWindow().draw(rockSprite);
                            break;
                        case 'P':
                            chadSprite.setScale(1.0f, 1.0f);
                            chadSprite.setPosition(offset.x + x * tileSize, offset.y + y * tileSize);
                            _stateManager.GetWindow().draw(chadSprite);
                            break;
                        case 'W':
                            waifuSprite.setScale(1.0f, 1.0f);
                            waifuSprite.setPosition(offset.x + x * tileSize, offset.y + y * tileSize);
                            _stateManager.GetWindow().draw(waifuSprite);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        _stateManager.GetWindow().display();
    }

    void Adventure::Destroy()
    {
    }
}
