#pragma once

class Hero;
class Monster;

class ExperienceSystem {
    ExperienceSystem() = default;
    ExperienceSystem(const ExperienceSystem&) = default; // Copy constructor
    ExperienceSystem(ExperienceSystem&&) = default; // Move constructor
    ExperienceSystem& operator=(const ExperienceSystem&) = default; // Copy assignment operator
    ExperienceSystem& operator=(ExperienceSystem&&) = default; // Move assignment operator
    virtual ~ExperienceSystem() = default; // Destructor

public:
    static ExperienceSystem& instance();
    void addExperience(Hero& hero, Monster& monster);
};
