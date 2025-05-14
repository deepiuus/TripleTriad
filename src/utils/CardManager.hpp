/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** CardManager
*/

#ifndef CARDMANAGER_HPP_
#define CARDMANAGER_HPP_

#include <unordered_map>
#include "../IGames.hpp"
#include "../utils/StateManager.hpp"
#include "../utils/Error.hpp"

namespace triad
{
    class Card {
        public:
            Card(int id, const std::string &name, const std::string &description);
            int GetId() const;
            const std::string &GetName() const;
            const std::string &GetDescription() const;
            bool LoadTexture(const std::string &path);
            const sf::Texture &GetTexture() const;

        private:
            int _id;
            std::string _name;
            std::string _description;
            sf::Texture _texture;
    };

    class CardManager {
        public:
            static CardManager &GetInstance();
            const Card &GetCard(int id) const;
            void LoadCards();

        private:
            CardManager();
            std::unordered_map<int, std::unique_ptr<Card>> _cards;
    };
}

#endif /* !CARDMANAGER_HPP_ */
