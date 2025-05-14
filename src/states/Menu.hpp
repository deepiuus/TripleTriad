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
            sf::Event event;
            sf::Font font;
            sf::Text text;
            sf::SoundBuffer buffer;
            sf::Sound sound;
            int _selectedOption;
            int _hoveredOption;
            bool _optionSelected;
            std::vector<std::string> _options;
            StateManager &_stateManager;
            sf::RenderWindow &_window;
    };
}

#endif /* !MENU_HPP_ */
