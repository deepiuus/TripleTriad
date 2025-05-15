/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** Adventure
*/

#include "Adventure.hpp"

namespace triad
{
    Adventure::Adventure(StateManager &stateManager) : _stateManager(stateManager)
    {
    }

    Adventure::~Adventure()
    {
    }

    void Adventure::Init()
    {
    }

    void Adventure::SetKey(TKey key)
    {
        switch (key) {
            case TKey::ESCAPE:
                _stateManager.RequestStateChange(std::make_unique<Menu>(_stateManager));
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
        _stateManager.GetWindow().clear(sf::Color::Yellow);
        _stateManager.GetWindow().display();
    }

    void Adventure::Destroy()
    {
    }
}
