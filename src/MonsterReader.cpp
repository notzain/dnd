#include "MonsterReader.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>

MonsterReader::MonsterReader()
{
}

MonsterArray* MonsterReader::createFromFile(const char* filename)
{
    std::ifstream fileStream;
    fileStream.exceptions(std::ifstream::failbit);
    try {
        fileStream.open(filename);
    } catch (const std::exception& e) {
        std::cerr << "Could not open file " << filename << "\n";
        throw e;
    }

    m_monsters = new MonsterArray;

    // find length of file
    m_monsters->length = static_cast<size_t>(std::count(
        std::istreambuf_iterator<char>(fileStream),
        std::istreambuf_iterator<char>(), '\n'));
    fileStream.clear();
    fileStream.seekg(0);

    m_monsters->array = new Monster*[m_monsters->length];

    for (int i = 0; i < m_monsters->length; ++i) {
        char line[256];
        fileStream.getline(line, 256);

        // check if line is correctly formatted
        if (line[0] == '[' && (line[strlen(line) - 2] == ']' || line[strlen(line) - 1] == ']')) {
            char name[32];
            char level[8];
            AttackProbability attackProbability{};
            Damage damage{};
            int defencePercentage;
            int hitpoints;

            // read the line and set the correct variables
            sscanf(line, "[%[^;];%[^;];%dx%d;%d-%d;%d;%d]\r",
                name, level, &attackProbability.hitPercentage, &attackProbability.hitRepeats,
                &damage.minimum, &damage.maximum, &defencePercentage, &hitpoints);

            m_monsters->array[i] = new Monster(name, stringToLevel(level), attackProbability, damage, defencePercentage, hitpoints);
        } else {
            delete m_monsters;
            throw std::runtime_error("Error parsing file.");
        }
    }

    return m_monsters;
}

Level MonsterReader::stringToLevel(const char *level) const
{
    if (strcmp(level, "1") == 0) {
        return Level::ONE;
    }
    if (strcmp(level, "2") == 0) {
        return Level::TWO;
    }
    if (strcmp(level, "3") == 0) {
        return Level::THREE;
    }
    if (strcmp(level, "4") == 0) {
        return Level::FOUR;
    }
    if (strcmp(level, "5") == 0) {
        return Level::FIVE;
    }
    if (strcmp(level, "6") == 0) {
        return Level::SIX;
    }
    if (strcmp(level, "7") == 0) {
        return Level::SEVEN;
    }
    if (strcmp(level, "8") == 0) {
        return Level::EIGHT;
    }
    if (strcmp(level, "9") == 0) {
        return Level::NINE;
    }
    if (strcmp(level, "10") == 0) {
        return Level::TEN;
    }
    if (strcmp(level, "BAAS") == 0) {
        return Level::BOSS;
    }
}
