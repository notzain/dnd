#include "MonsterReader.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>

MonsterReader::MonsterReader()
    : m_monsters(new MonsterArray)
{
}

MonsterArray* MonsterReader::createFromFile(const char* filename)
{
    std::ifstream fileStream(filename);
    if (!fileStream.is_open())
        throw std::runtime_error("Could not read file.");

    m_monsters->length = static_cast<size_t>(std::count(
        std::istreambuf_iterator<char>(fileStream),
        std::istreambuf_iterator<char>(), '\n'));
    fileStream.clear();
    fileStream.seekg(0);

    m_monsters->array = new Monster*[m_monsters->length];

    for (int i = 0; i < m_monsters->length; ++i) {
        char line[256];
        fileStream.getline(line, 256);

        if (line[0] == '[' && (line[strlen(line) - 2] == ']' || line[strlen(line) - 1] == ']')) {
            char name[32];
            char level[8];
            AttackProbability attackProbability{};
            Damage damage;
            int defencePercentage;
            int hitpoints;

            sscanf(line, "[%[^;];%[^;];%dx%d;%d-%d;%d;%d]\r",
                name, level, &attackProbability.hitPercentage, &attackProbability.hitRepeats,
                &damage.minimum, &damage.maximum, &defencePercentage, &hitpoints);

            m_monsters->array[i] = new Monster(name, stringToLevel(level), attackProbability, damage, defencePercentage, hitpoints);
        } else {
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
