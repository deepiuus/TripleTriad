/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** Settings
*/

#include "Settings.hpp"

namespace triad
{
    Settings::Settings(StateManager &stateManager) : _stateManager(stateManager)
    {
    }

    Settings::~Settings()
    {
    }

    void Settings::Init()
    {
    }

    void Settings::SetKey(TKey key)
    {
        switch (key) {
            case TKey::ESCAPE:
                _stateManager.RequestStateChange(std::make_unique<Menu>(_stateManager));
                break;
            default:
                break;
        }
    }

    void Settings::Update()
    {
    }

    void Settings::Display()
    {
        _stateManager.GetWindow().clear(sf::Color::Green);
        _stateManager.GetWindow().display();
    }

    void Settings::Destroy()
    {
    }
}
