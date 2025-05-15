/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** Arena
*/

#include "Arena.hpp"

namespace triad
{
    Arena::Arena(StateManager &stateManager)
        : _stateManager(stateManager), _window(stateManager.GetWindow()), width(800), height(600)
    {
    }

    Arena::~Arena()
    {
    }

   void Arena::Init()
    {
        if (!_texture.loadFromFile("assets/sprites/Board.png")) {
            throw Error("Failed to load texture");
        }

        _player1Deck = {
            &CardManager::GetInstance().GetCard(1),
            &CardManager::GetInstance().GetCard(2),
            &CardManager::GetInstance().GetCard(3),
            &CardManager::GetInstance().GetCard(4),
            &CardManager::GetInstance().GetCard(5),
        };
        _player2Deck = {
            &CardManager::GetInstance().GetCard(6),
            &CardManager::GetInstance().GetCard(7),
            &CardManager::GetInstance().GetCard(8),
            &CardManager::GetInstance().GetCard(9),
            &CardManager::GetInstance().GetCard(10),
        };
        _player1Cards.clear();
        _player2Cards.clear();
        int cardSpacing = 30;
        int cardY = height / 2 - (5 * 60 + 4 * cardSpacing) / 2;
        for (int i = 0; i < 5; i++) {
            sf::Sprite sprite1, sprite2;
            sprite1.setTexture(_player1Deck[i]->GetTexture());
            sprite1.setPosition(30, cardY + i * (60 + cardSpacing));
            _player1Cards.push_back(sprite1);

            sprite2.setTexture(_player2Deck[i]->GetTexture());
            sprite2.setPosition(width - 30 - sprite2.getTexture()->getSize().x, cardY + i * (60 + cardSpacing));
            _player2Cards.push_back(sprite2);
        }
        float cellSize = 120;
        float cellGap = 5;
        float gridWidth = 3 * cellSize + 2 * cellGap;
        float gridHeight = 3 * cellSize + 2 * cellGap;
        float gridStartX = width / 2 - gridWidth / 2;
        float gridStartY = height / 2 - gridHeight / 2;
        for (int y = 0; y < 3; y++)
            for (int x = 0; x < 3; x++)
                _boardGrid[y][x] = sf::FloatRect(
                    gridStartX + x * (cellSize + cellGap),
                    gridStartY + y * (cellSize + cellGap),
                    cellSize,
                    cellSize
                );
        for (int y = 0; y < 3; y++)
            for (int x = 0; x < 3; x++)
                _boardOccupancy[y][x] = {-1, -1};
    }

    void Arena::SetKey(TKey key)
    {
        if (key == TKey::LCLICK) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
            for (size_t i = 0; i < _player1Cards.size(); i++) {
                if (_player1Cards[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    _dragging = true;
                    _draggedCard = {0, static_cast<int>(i)};
                    _dragOffset = _player1Cards[i].getPosition() - sf::Vector2f(mousePos);
                    break;
                }
            }
            for (size_t i = 0; i < _player2Cards.size(); i++) {
                if (_player2Cards[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    _dragging = true;
                    _draggedCard = {1, static_cast<int>(i)};
                    _dragOffset = _player2Cards[i].getPosition() - sf::Vector2f(mousePos);
                    break;
                }
            }
        }
        if (key == TKey::ESCAPE) {
            _stateManager.RequestStateChange(std::make_unique<Menu>(_stateManager));
        }
        if (key == TKey::NONE) {
            if (_dragging) {
                int foundX = -1, foundY = -1;
                sf::FloatRect bounds;
                if (_draggedCard.x == 0)
                    bounds = _player1Cards[_draggedCard.y].getGlobalBounds();
                else
                    bounds = _player2Cards[_draggedCard.y].getGlobalBounds();

                for (int y = 0; y < 3; y++)
                    for (int x = 0; x < 3; x++)
                        if (_boardGrid[y][x].intersects(bounds) && _boardOccupancy[y][x].first == -1) {
                            foundX = x;
                            foundY = y;
                        }

                if (foundX != -1 && foundY != -1) {
                    sf::Vector2f cellCenter(
                        _boardGrid[foundY][foundX].left + _boardGrid[foundY][foundX].width / 2.f,
                        _boardGrid[foundY][foundX].top + _boardGrid[foundY][foundX].height / 2.f
                    );
                    if (_draggedCard.x == 0) {
                        _player1Cards[_draggedCard.y].setPosition(
                            cellCenter.x - _player1Cards[_draggedCard.y].getTexture()->getSize().x / 2.f,
                            cellCenter.y - _player1Cards[_draggedCard.y].getTexture()->getSize().y / 2.f
                        );
                    } else {
                        _player2Cards[_draggedCard.y].setPosition(
                            cellCenter.x - _player2Cards[_draggedCard.y].getTexture()->getSize().x / 2.f,
                            cellCenter.y - _player2Cards[_draggedCard.y].getTexture()->getSize().y / 2.f
                        );
                    }
                    _boardOccupancy[foundY][foundX] = { _draggedCard.x, _draggedCard.y };
                } else {
                    if (_draggedCard.x == 0)
                        _player1Cards[_draggedCard.y].setPosition(30,
                            height / 2 - (5 * 60 + 4 * 30) / 2 + _draggedCard.y * (60 + 30));
                    else if (_draggedCard.x == 1)
                        _player2Cards[_draggedCard.y].setPosition(
                            width - 30 - _player2Cards[_draggedCard.y].getTexture()->getSize().x,
                            height / 2 - (5 * 60 + 4 * 30) / 2 + _draggedCard.y * (60 + 30));
                }
                _dragging = false;
                _draggedCard = {-1, -1};
            }
        }
    }

    void Arena::Update()
    {
        if (_dragging) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
            if (_draggedCard.x == 0)
                _player1Cards[_draggedCard.y].setPosition(sf::Vector2f(mousePos) + _dragOffset);
            else if (_draggedCard.x == 1)
                _player2Cards[_draggedCard.y].setPosition(sf::Vector2f(mousePos) + _dragOffset);
        }
    }

    void Arena::Display()
    {
        _window.clear(sf::Color::Blue);
        _sprite.setTexture(_texture);
        _sprite.setPosition(width / 2 - _texture.getSize().x / 2,
                            height / 2 - _texture.getSize().y / 2);
        _sprite.setScale(1.0f, 1.0f);
        _window.draw(_sprite);

        for (auto &sprite : _player1Cards)
            _window.draw(sprite);
        for (auto &sprite : _player2Cards)
            _window.draw(sprite);
    }

    void Arena::Destroy()
    {
    }
}
