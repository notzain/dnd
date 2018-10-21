#pragma once

class Hero;

class HeroFactory {
public:
    Hero* makeFromFile(const char* filename) const;
    Hero* makeDefaultHero() const;
};


