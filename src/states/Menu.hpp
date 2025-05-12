/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <vector>
#include "../IGames.hpp"
#include "../utils/StateManager.hpp"
#include "../utils/Error.hpp"

namespace triad
{
    class Menu : public IGames {
        public:
            Menu(StateManager &stateManager);
            ~Menu() override;
            void Init() override;
            void SetKey(TKey key);
            int GetSelectedOption() const;
            bool IsOptionSelected() const;
            void Update() override;
            void Display() override;
            void Destroy() override;

        private:
            int width;
            int height;
            sf::RenderWindow window;
            sf::Event event;
            sf::Texture texture;
            sf::Sprite sprite;
            sf::Font font;
            sf::Text text;
            sf::SoundBuffer buffer;
            sf::Sound sound;
            int _selectedOption;
            bool _optionSelected;
            std::vector<std::string> _options;
            StateManager &_stateManager;
    };
}

#endif /* !MENU_HPP_ */
