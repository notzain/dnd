#pragma once

class Hero;
class DungeonLayer;

class RestSystem {
    RestSystem() = default;
    RestSystem(const RestSystem&) = default; // Copy constructor
    RestSystem(RestSystem&&) = default; // Move constructor
    RestSystem& operator=(const RestSystem&) = default; // Copy assignment operator
    RestSystem& operator=(RestSystem&&) = default; // Move assignment operator
    virtual ~RestSystem() = default; // Destructor

public:
    static RestSystem& instance();
    void rest(Hero& hero, DungeonLayer& layer);
};


