#include "Game.h"
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
    std::cout << '\n';
    while (true) {
        char input;
        std::cin >> input;
        std::cin.ignore(10000, '\n');

        switch (input) {
        case 'q':
            return;
        case 'd': {
            if (m_hero.y() + 1 > m_layer.config().height - 1) {
                std::cout << "You have hit a wall.";
            } else {
                m_hero.setY(m_hero.y() + 1);
            }
        } break;
        case 'w': {
            if (m_hero.x() - 1 < 0) {
                std::cout << "You have hit a wall.";
            } else {
                m_hero.setX(m_hero.x() - 1);
            }
        } break;
        case 'a': {
            if (m_hero.y() - 1 < 0) {
                std::cout << "You have hit a wall.";
            } else {
                m_hero.setY(m_hero.y() - 1);
            }

        } break;
        case 's': {
            if (m_hero.x() + 1 > m_layer.config().width - 1) {
                std::cout << "You have hit a wall.";
            } else {
                m_hero.setX(m_hero.x() + 1);
            }
        } break;
        }
        m_layer.visit(m_hero.x(), m_hero.y());

        std::cout << '\n';
        m_layer.print();
        system("cls");
    }
}
