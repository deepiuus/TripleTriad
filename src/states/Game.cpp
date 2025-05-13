/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** Game
*/

#include "Game.hpp"

namespace triad
{
    Game::Game(StateManager &stateManager) : _stateManager(stateManager)
    {
    }

    Game::~Game()
    {
    }

    void Game::Init()
    {
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
        _stateManager.GetWindow().clear(sf::Color::Blue);
        _stateManager.GetWindow().display();
    }

    void Game::Destroy()
    {
    }
}
