/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** Visual
*/

#include "Visual.hpp"

namespace triad
{
    Visual::Visual(StateManager &stateManager)
        : _stateManager(stateManager), _levelManager(stateManager.GetLevelManager())
    {
    }

    Visual::~Visual()
    {
    }

    void Visual::Init()
    {
        MusicManager::GetInstance().Play("assets/sounds/Variation-on-Egmont.ogg");
        if (!_font.loadFromFile("assets/fonts/upheavtt.ttf")) {
            throw Error("Failed to load font");
        }
        _levelManager.StartDialogue();
        _text.setFont(_font);
        _text.setCharacterSize(24);
        _text.setFillColor(sf::Color::White);
    }

    void Visual::SetKey(TKey key)
    {
        switch (key) {
            case TKey::ESCAPE:
                _levelManager.ResetLevel();
                _stateManager.RequestStateChange(std::make_unique<Menu>(_stateManager));
                return;
            case TKey::ENTER:
            case TKey::SPACE:
            case TKey::LCLICK:
                if (!_levelManager.IsDialogueFinished()) {
                    _levelManager.NextDialogue();
                } else {
                    _stateManager.RequestStateChange(std::make_unique<Arena>(_stateManager));
                    return;
                }
                break;
            default:
                break;
        }
    }

    void Visual::Update()
    {
    }

    void Visual::Display()
    {
        if (!_stateManager.GetWindow().isOpen()) {
            return;
        }
        _stateManager.GetWindow().clear(sf::Color::Black);
        if (!_levelManager.IsDialogueFinished()) {
            _text.setString(_levelManager.GetDialogue());
            _text.setPosition(10, 10);
            _stateManager.GetWindow().draw(_text);
        }
    }

    void Visual::Destroy()
    {
        _text = sf::Text();
        _font = sf::Font();
    }
}
