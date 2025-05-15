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
        const Card &card = CardManager::GetInstance().GetCard(2);
        _cardSprite.setTexture(card.GetTexture());
        _cardSprite.setPosition(width / 2 - card.GetTexture().getSize().x / 2,
                                height / 2 - card.GetTexture().getSize().y / 2);
    }

    void Arena::SetKey(TKey key)
    {
        switch (key) {
            case TKey::LCLICK: {
                sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
                sf::FloatRect bounds = _cardSprite.getGlobalBounds();
                if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    _dragging = true;
                    _dragOffset = _cardSprite.getPosition() - sf::Vector2f(mousePos);
                }
                break;
            }
            case TKey::RCLICK:
            case TKey::ENTER:
                break;
            case TKey::ESCAPE:
                _stateManager.RequestStateChange(std::make_unique<Menu>(_stateManager));
                break;
            case TKey::NONE:
                _dragging = false;
                break;
            default:
                break;
        }
    }

    void Arena::Update()
    {
        if (_dragging) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
            _cardSprite.setPosition(sf::Vector2f(mousePos) + _dragOffset);
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
        _window.draw(_cardSprite);
    }

    void Arena::Destroy()
    {
    }
}
