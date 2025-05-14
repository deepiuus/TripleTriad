/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** Game
*/

#include "Game.hpp"

namespace triad
{
    Game::Game(StateManager &stateManager)
        : _stateManager(stateManager), _window(stateManager.GetWindow()), width(800), height(600)
    {
    }

    Game::~Game()
    {
    }

   void Game::Init()
    {
        if (!_texture.loadFromFile("assets/sprites/Board.png")) {
            throw Error("Failed to load texture");
        }
        const Card &card = CardManager::GetInstance().GetCard(2);
        _cardSprite.setTexture(card.GetTexture());
        _cardSprite.setPosition(width / 2 - card.GetTexture().getSize().x / 2,
                                height / 2 - card.GetTexture().getSize().y / 2);
    }

    void Game::SetKey(TKey key)
    {
        switch (key) {
            case TKey::ESCAPE:
                _stateManager.RequestStateChange(std::make_unique<Menu>(_stateManager));
                break;
            default:
                break;
        }
    }

    void Game::Update()
    {
    }

    void Game::Display()
    {
        _window.clear(sf::Color::Blue);
        _sprite.setTexture(_texture);
        _sprite.setPosition(width / 2 - _texture.getSize().x / 2,
                            height / 2 - _texture.getSize().y / 2);
        _sprite.setScale(1.0f, 1.0f);
        _window.draw(_sprite);
        _window.draw(_cardSprite);
    }

    void Game::Destroy()
    {
    }
}
