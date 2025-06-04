/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** IGames
*/

#ifndef IGAMES_HPP_
#define IGAMES_HPP_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

namespace triad
{
    enum class TKey {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ENTER,
        SPACE,
        ESCAPE,
        LCLICK,
        RCLICK,
        NONE
    };

    class IGames {
        public:
            virtual ~IGames() = default;
            virtual void Init() = 0;
            virtual void SetKey(TKey key) = 0;
            virtual void Update() = 0;
            virtual void Display() = 0;
            virtual void Destroy() = 0;
    };
}

#endif /* !IGAMES_HPP_ */
