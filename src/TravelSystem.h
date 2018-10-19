#pragma once

class Hero;
class DungeonLayer;

class TravelSystem {
    TravelSystem() = default;
    TravelSystem(const TravelSystem&) = default; // Copy constructor
    TravelSystem(TravelSystem&&) = default; // Move constructor
    TravelSystem& operator=(const TravelSystem&) = default; // Copy assignment operator
    TravelSystem& operator=(TravelSystem&&) = default; // Move assignment operator
    virtual ~TravelSystem() = default; // Destructor

public:
    static TravelSystem& instance();
    bool travel(char direction, Hero& hero, DungeonLayer& layer);
};
