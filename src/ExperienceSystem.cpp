#include "ExperienceSystem.h"
#include "Hero.h"
#include "Monster.h"
#include <iostream>

const static int EXP_TILL_NEXT_LEVEL[] = {
    10,
    100,
    200,
    500
};

const static int MONSTER_LEVEL_TO_EXP(const Level& level)
{
    switch (level) {
    case Level::ONE:
        return 2;
    case Level::TWO:
        return 4;
    case Level::THREE:
        return 6;
    case Level::FOUR:
        return 10;
    case Level::FIVE:
        return 15;
    case Level::SIX:
        return 25;
    case Level::SEVEN:
        return 40;
    case Level::EIGHT:
        return 60;
    case Level::NINE:
        return 85;
    case Level::TEN:
        return 120;
    case Level::BOSS:
        return 200;
    }
}

ExperienceSystem& ExperienceSystem::instance()
{
    static ExperienceSystem experienceSystem;
    return experienceSystem;
}

void ExperienceSystem::addExperience(Hero& hero, Monster& monster)
{
    // find how many exp a monster should give, based on its level
    const int expToGain = MONSTER_LEVEL_TO_EXP(monster.level());
    std::cout << "You've gained " << expToGain << " exp.\n";
    const int prevHeroExp = hero.exp();
    hero.setExp(prevHeroExp + expToGain);

    int level = hero.level();
    // max level is 5
    if (level > 5)
        return;
    // if hero has crossed the treshold for exp -> level, he has increased a lvl
    if (prevHeroExp < EXP_TILL_NEXT_LEVEL[level - 1] && hero.exp() >= EXP_TILL_NEXT_LEVEL[level - 1]) {
        hero.setLevel(hero.level() + 1);
        std::cout << "You've leveled up! You can increase a stat by 2:\n"
                  << "1) HP " << "(currently " << hero.hitpoints() << ")\n"
                  << "2) Attack "<< "(currently " << hero.attack() << ")\n"
                  << "3) Defence " << "(currently " << hero.defence() << ")\n";

        char input = 0;
        while (input < '1' || input > '3') {
            std::cin >> input;
            std::cin.ignore(1000, '\n');
        }

        switch (input) {
        case '1': {
            hero.setHitpoints(hero.hitpoints() + 2);
        } break;
        case '2': {
            hero.setAttack(hero.attack() + 2);
        } break;
        case '3': {
            hero.setDefence(hero.defence() + 2);
        } break;
        }
    }
}
