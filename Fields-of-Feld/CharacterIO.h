#ifndef CHARACTERIO_H
#define CHARACTERIO_H
#include <fstream>
#include <nlohmann/json.hpp>
#include "Character.h"

void saveCharacters(const std::vector<std::shared_ptr<Character>>& characters, const std::string& file);
std::vector<std::shared_ptr<Character>> loadCharacters(const std::string& file);

#endif // !CHARACTERIO_H
