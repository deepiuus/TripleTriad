/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** Menu
*/

#include "Menu.hpp"
#include "Game.hpp"
#include "Settings.hpp"

namespace triad
{
    Menu::Menu(StateManager &stateManager) 
        : _stateManager(stateManager), width(800), height(600), _selectedOption(0), _optionSelected(false)
    {
        _options = {"Game", "Settings", "Quit"};
    }

    Menu::~Menu()
    {
    }

    void Menu::Init()
    {
       try {
            window.create(sf::VideoMode(width, height), "Triple Triad");
            if (!font.loadFromFile("assets/fonts/upheavtt.ttf")) {
                throw Error("Failed to load font");
            }
        } catch (const Error &e) {
            window.close();
            throw;
        }
    }

    void Menu::SetKey(TKey key)
    {
        switch (key) {
            case TKey::UP:
                _selectedOption = (_selectedOption - 1 + _options.size()) % _options.size();
                break;
            case TKey::DOWN:
                _selectedOption = (_selectedOption + 1) % _options.size();
                break;
            case TKey::ENTER:
                _optionSelected = true;
                break;
            default:
                break;
        }
    }

    int Menu::GetSelectedOption() const
    {
        return _selectedOption;
    }

    bool Menu::IsOptionSelected() const
    {
        return _optionSelected;
    }

    void Menu::Update()
    {
        if (!window.isOpen()) {
            _stateManager.RequestStateChange(nullptr);
            return;
        }
        if (_optionSelected) {
            switch (_selectedOption) {
                case 0:
                    _stateManager.RequestStateChange(std::make_unique<Game>(_stateManager));
                    break;
                case 1:
                    _stateManager.RequestStateChange(std::make_unique<Settings>(_stateManager));
                    break;
                case 2:
                    _stateManager.RequestStateChange(nullptr);
                    break;
            }
            _optionSelected = false;
        }
    }

    void Menu::Display()
    {
        const float spacing = 50.0f;

        window.clear(sf::Color::Black);
        for (size_t i = 0; i < _options.size(); ++i) {
            text.setFont(font);
            text.setString(_options[i]);
            text.setCharacterSize(40);
            text.setFillColor(i == _selectedOption ? sf::Color::Red : sf::Color::White);
            text.setPosition(width / 2 - text.getGlobalBounds().width / 2,
                            height / 2 - (_options.size() * spacing) / 2 + i * spacing);
            window.draw(text);
        }
        window.display();
    }

    void Menu::Destroy()
    {
        texture = sf::Texture();
        sprite = sf::Sprite();
        font = sf::Font();
        text = sf::Text();
        sound = sf::Sound();
        buffer = sf::SoundBuffer();
    }
}
