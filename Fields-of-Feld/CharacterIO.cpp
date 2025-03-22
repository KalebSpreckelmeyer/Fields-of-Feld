#include <fstream>
#include <nlohmann/json.hpp>
#include "Character.h"

void saveCharacters(const std::vector<std::shared_ptr<Character>>& characters, const std::string& file) {
    nlohmann::json j;
    for (const auto& c : characters)
        j["characters"].push_back(c->toJson());
    std::ofstream out(file);
    out << j.dump(4);
}

std::vector<std::shared_ptr<Character>> loadCharacters(const std::string& file) {
    std::ifstream in(file);
    nlohmann::json j;
    in >> j;

    std::vector<std::shared_ptr<Character>> result;
    for (const auto& cj : j["characters"])
        result.push_back(Character::fromJson(cj));
    return result;
}