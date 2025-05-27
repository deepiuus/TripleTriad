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

    void Arena::SetupCards(int cardSpacing, int cardY)
    {
        sf::Sprite sprite1;
        sf::Sprite sprite2;

        _player1Deck = {
            &CardManager::GetInstance().GetCard(21),
            &CardManager::GetInstance().GetCard(21),
            &CardManager::GetInstance().GetCard(21),
            &CardManager::GetInstance().GetCard(21),
            &CardManager::GetInstance().GetCard(21),
        };
        _player2Deck = {
            &CardManager::GetInstance().GetCard(21),
            &CardManager::GetInstance().GetCard(21),
            &CardManager::GetInstance().GetCard(21),
            &CardManager::GetInstance().GetCard(21),
            &CardManager::GetInstance().GetCard(21),
        };
        _player1Cards.clear();
        _player2Cards.clear();
        for (int i = 0; i < 5; i++) {
            sprite1.setTexture(_player1Deck[i]->GetTexture());
            sprite1.setPosition(30, cardY + i * (60 + cardSpacing));
            _player1Cards.push_back(sprite1);
            sprite2.setTexture(_player2Deck[i]->GetTexture());
            sprite2.setPosition(
                width - 30 - sprite2.getTexture()->getSize().x,
                cardY + i * (60 + cardSpacing));
            _player2Cards.push_back(sprite2);
        }
    }

    void Arena::SetupBoard(float cellSize, float cellGap, float gridStartX, float gridStartY)
    {
        if (!_texture.loadFromFile("assets/sprites/Board.png")) {
            throw Error("Failed to load texture");
        }
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

   void Arena::Init()
    {
        int cardSpacing = 30;
        int cardY = height / 2 - (5 * 60 + 4 * cardSpacing) / 2;
        float cellSize = 120;
        float cellGap = 5;
        float gridWidth = 3 * cellSize + 2 * cellGap;
        float gridHeight = 3 * cellSize + 2 * cellGap;
        float gridStartX = width / 2 - gridWidth / 2;
        float gridStartY = height / 2 - gridHeight / 2;

        SetupBoard(cellSize, cellGap, gridStartX, gridStartY);
        SetupCards(cardSpacing, cardY);
    }

    void Arena::ResetCard()
    {
        int cardSpacing = 30;
        int cardY = height / 2 - (5 * 60 + 4 * cardSpacing) / 2;

        if (_draggedCard.x == 0)
            _player1Cards[_draggedCard.y].setPosition(30,
                cardY + _draggedCard.y * (60 + cardSpacing));
        else if (_draggedCard.x == 1)
            _player2Cards[_draggedCard.y].setPosition(
                width - 30 - _player2Cards[_draggedCard.y].getTexture()->getSize().x,
                cardY + _draggedCard.y * (60 + cardSpacing));
    }

    void Arena::CaptureCard(int x, int y)
    {
        int playerCount = 0;
        int ennemyCount = 0;
        int currentPlayer = _boardOccupancy[y][x].first;
        int currentIndex = _boardOccupancy[y][x].second;
        const Card *currentCard = (currentPlayer == 0)
            ? _player1Deck[currentIndex]
            : _player2Deck[currentIndex];
        int adjPlayer = 0;
        int adjIndex = 0;
        const Card *adjCard = nullptr;

        if (y > 0) {
            adjPlayer = _boardOccupancy[y - 1][x].first;
            adjIndex = _boardOccupancy[y - 1][x].second;
            if (adjPlayer != -1 && adjPlayer != currentPlayer) {
                adjCard = (adjPlayer == 0)
                    ? _player1Deck[adjIndex]
                    : _player2Deck[adjIndex];
                if (currentCard->GetTop() > adjCard->GetBottom()) {
                    _boardOccupancy[y - 1][x].first = currentPlayer;
                    printf("%s captured with %s the card %s from the top!\n",
                        currentPlayer == 0 ? "Player" : "Ennemy",
                        currentCard->GetName().c_str(),
                        adjCard->GetName().c_str());
                }
            }
        }
        if (y < 2) {
            adjPlayer = _boardOccupancy[y + 1][x].first;
            adjIndex = _boardOccupancy[y + 1][x].second;
            if (adjPlayer != -1 && adjPlayer != currentPlayer) {
                adjCard = (adjPlayer == 0)
                    ? _player1Deck[adjIndex]
                    : _player2Deck[adjIndex];
                if (currentCard->GetBottom() > adjCard->GetTop()) {
                    _boardOccupancy[y + 1][x].first = currentPlayer;
                    printf("%s captured with %s the card %s from the bottom!\n",
                        currentPlayer == 0 ? "Player" : "Ennemy",
                        currentCard->GetName().c_str(),
                        adjCard->GetName().c_str());
                }
            }
        }
        if (x > 0) {
            adjPlayer = _boardOccupancy[y][x - 1].first;
            adjIndex = _boardOccupancy[y][x - 1].second;
            if (adjPlayer != -1 && adjPlayer != currentPlayer) {
                adjCard = (adjPlayer == 0)
                    ? _player1Deck[adjIndex]
                    : _player2Deck[adjIndex];
                if (currentCard->GetLeft() > adjCard->GetRight()) {
                    _boardOccupancy[y][x - 1].first = currentPlayer;
                    printf("%s captured with %s the card %s from the left!\n",
                        currentPlayer == 0 ? "Player" : "Ennemy",
                        currentCard->GetName().c_str(),
                        adjCard->GetName().c_str());
                }
            }
        }
        if (x < 2) {
            adjPlayer = _boardOccupancy[y][x + 1].first;
            adjIndex = _boardOccupancy[y][x + 1].second;
            if (adjPlayer != -1 && adjPlayer != currentPlayer) {
                adjCard = (adjPlayer == 0)
                    ? _player1Deck[adjIndex]
                    : _player2Deck[adjIndex];
                if (currentCard->GetRight() > adjCard->GetLeft()) {
                    _boardOccupancy[y][x + 1].first = currentPlayer;
                    printf("%s captured with %s the card %s from the right!\n",
                        currentPlayer == 0 ? "Player" : "Ennemy",
                        currentCard->GetName().c_str(),
                        adjCard->GetName().c_str());
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (_boardOccupancy[i][j].first == 0)
                    playerCount++;
                else if (_boardOccupancy[i][j].first == 1)
                    ennemyCount++;
            }
        }
        printf("Player has %d cards, Ennemy has %d cards\n", playerCount, ennemyCount);
    }

    void Arena::PlaceCard(int x, int y)
    {
        sf::Vector2f cellCenter = {
            _boardGrid[y][x].left + _boardGrid[y][x].width / 2.f,
            _boardGrid[y][x].top + _boardGrid[y][x].height / 2.f
        };

        if (_draggedCard.x == 0)
            _player1Cards[_draggedCard.y].setPosition(
                cellCenter.x - _player1Cards[_draggedCard.y].getTexture()->getSize().x / 2.f,
                cellCenter.y - _player1Cards[_draggedCard.y].getTexture()->getSize().y / 2.f
            );
        else
            _player2Cards[_draggedCard.y].setPosition(
                cellCenter.x - _player2Cards[_draggedCard.y].getTexture()->getSize().x / 2.f,
                cellCenter.y - _player2Cards[_draggedCard.y].getTexture()->getSize().y / 2.f
            );
        _boardOccupancy[y][x] = { _draggedCard.x, _draggedCard.y };
    }

    void Arena::OccupyCell()
    {
        int foundX = -1;
        int foundY = -1;

        if (_draggedCard.x < 0 || _draggedCard.y < 0 ||
            _draggedCard.x > 1 || _draggedCard.y >= 5)
            return;
        sf::FloatRect bounds = (_draggedCard.x == 0)
            ? _player1Cards[_draggedCard.y].getGlobalBounds()
            : _player2Cards[_draggedCard.y].getGlobalBounds();

        if (!_dragging)
            return;
        for (int y = 0; y < 3; y++)
            for (int x = 0; x < 3; x++)
                if (_boardGrid[y][x].intersects(bounds) && _boardOccupancy[y][x].first == -1) {
                    foundX = x;
                    foundY = y;
                }
        if (foundX != -1 && foundY != -1) {
            PlaceCard(foundX, foundY);
            CaptureCard(foundX, foundY);
        } else {
            ResetCard();
        }
        _dragging = false;
        _draggedCard = {-1, -1};
    }

    void Arena::DraggingCard()
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(_window);

        for (size_t i = 0; i < _player1Cards.size(); i++) {
            if (_player1Cards[i].getGlobalBounds().contains(
                static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                _dragging = true;
                _draggedCard = {0, static_cast<int>(i)};
                _dragOffset = _player1Cards[i].getPosition() - sf::Vector2f(mousePos);
                break;
            }
        }
        for (size_t i = 0; i < _player2Cards.size(); i++) {
            if (_player2Cards[i].getGlobalBounds().contains(
                static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                _dragging = true;
                _draggedCard = {1, static_cast<int>(i)};
                _dragOffset = _player2Cards[i].getPosition() - sf::Vector2f(mousePos);
                break;
            }
        }
    }

    void Arena::SetKey(TKey key)
    {
        if (key == TKey::LCLICK) {
            DraggingCard();
        }
        if (key == TKey::ESCAPE) {
            _stateManager.RequestStateChange(std::make_unique<Menu>(_stateManager));
        }
        if (key == TKey::NONE) {
            OccupyCell();
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
