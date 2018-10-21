#pragma once

class Hero;
class SaveSystem {
    SaveSystem() = default;
    SaveSystem(const SaveSystem&) = default; // Copy constructor
    SaveSystem(SaveSystem&&) = default; // Move constructor
    SaveSystem& operator=(const SaveSystem&) = default; // Copy assignment operator
    SaveSystem& operator=(SaveSystem&&) = default; // Move assignment operator
    virtual ~SaveSystem() = default; // Destructor

public:
    static SaveSystem& instance();
    bool prompt() const;
    void save(Hero& hero, const char* filename);
    void load(Hero& hero, const char* filename);
};
