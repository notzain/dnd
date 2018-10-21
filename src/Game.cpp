#include "Game.h"
#include "InventorySystem.h"
#include "RestSystem.h"
#include "SaveSystem.h"
#include "TravelSystem.h"
#include <iostream>

Game::Game(Dungeon& dungeon, Hero& hero)
    : m_dungeon(dungeon)
    , m_hero(hero)
{
    m_hero.setX(0);
    m_hero.setY(0);
    m_dungeon.activeLayer().visitables()[0][0]->setAsStart();
}

void Game::play()
{
    bool quit = false;
    while (!quit) {
        std::cout << "Options:\n"
                  << "q : Quit\n"
                  << "m : Show map\n"
                  << "r : Rest\n"
                  << "i : Inventory\n"
                  << "w/a/s/d : Move\n";

        char input;
        std::cin >> input;
        std::cin.ignore(10000, '\n');

        switch (input) {
        case 'q':
            quit = true;
        case 'm': {
            system("cls");
            m_dungeon.activeLayer().print();

            std::cout << "Legenda:\n"
                      << "N - Room\n"
                      << "H - Stair up\n"
                      << "L - Stair down\n"
                      << "B - Boss\n"
                      << ". - Unknown\n";
        } break;
        case 'r': {
            RestSystem::instance().rest(m_hero, m_dungeon.activeLayer());
        } break;
        case 'p': {
            system("cls");
            std::cout
                << "Name: " << m_hero.name() << "\n"
                << "HP: " << m_hero.hitpoints() << "\n"
                << "Level: " << m_hero.level() << "\n"
                << "Exp: " << m_hero.exp() << "\n"
                << "Attack: " << m_hero.attack() << "\n"
                << "Defence: " << m_hero.defence() << "\n";
        } break;
        case 'i': {
            InventorySystem::instance().use(m_hero);
        } break;
        case 'x': {
            TravelSystem::instance().shuffle(m_dungeon.activeLayer());
        } break;
        case 'w':
        case 'a':
        case 's':
        case 'd': {
            system("cls");
            TravelSystem::instance().travel(input, m_hero, m_dungeon.activeLayer());
        } break;
        default: {
            std::cout << "Unknown input.\n";
        } break;
        }

        std::cout << '\n';

        if (m_hero.hitpoints() <= 0) {
            std::cout << "You've died.\n";
            quit = true;
        }

        if (m_dungeon.isCleared()) {
            std::cout << "You cleared the dungeon!\n";
            quit = true;
        }
    }

    std::cout << "\n\nDo you want to save your hero? (y/n) ";
    char save = 0;
    while (!(save == 'y' || save == 'n')) {
        std::cin >> save;
        std::cin.ignore(1000, '\n');
    }

    if (save == 'y') {
        SaveSystem::instance().save(m_hero, "../hero.txt");
    }
}
