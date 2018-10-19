#include "Game.h"
#include "TravelSystem.h"
#include <iostream>

Game::Game(DungeonLayer& layer, Hero& hero)
    : m_layer(layer)
    , m_hero(hero)
{
    m_hero.setX(0);
    m_hero.setY(0);
}

void Game::play()
{
    while (true) {
        m_layer.print();
        std::cout << '\n';

        char input;
        std::cin >> input;
        std::cin.ignore(10000, '\n');

        if (input == 'q') {
            return;
        } else {
            TravelSystem::instance().travel(input, m_hero, m_layer);
        }

        std::cout << '\n';
        system("cls");

        if (m_hero.hitpoints() <= 0) {
            std::cout << "You've died.\n";
            return;
        }
    }
}
