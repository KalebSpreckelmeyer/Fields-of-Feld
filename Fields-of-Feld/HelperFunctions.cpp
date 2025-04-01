#include "HelperFunctions.h"
#include <stdexcept>
#include "Trinket.h"
#include "Human.h"
#include <iostream>
#include "Character.h"
//FROM JSON HELPERS
DamageTypes stringToDamageTypes(const std::string& str) {
	if (str == "NONE") return DamageTypes::NONE;
    if (str == "SLASH") return DamageTypes::SLASH;
    if (str == "PIERCE") return DamageTypes::PIERCE;
    if (str == "BLUNT") return DamageTypes::BLUNT;
	if (str == "CHOP") return DamageTypes::CHOP;
    if (str == "MAGIC") return DamageTypes::MAGIC;
    if (str == "FIRE") return DamageTypes::FIRE;
    if (str == "FROST") return DamageTypes::FROST;
    if (str == "SHOCK") return DamageTypes::SHOCK;
    if (str == "WIND") return DamageTypes::WIND;
    if (str == "POISON") return DamageTypes::POISON;
    if (str == "BLEED") return DamageTypes::BLEED;
    if (str == "SLEEP") return DamageTypes::SLEEP;
    if (str == "DARK") return DamageTypes::DARK;
    if (str == "HOLY") return DamageTypes::HOLY;
    throw std::invalid_argument("Invalid PhysicalDamageType string: " + str);
}

StatScaling stringToStatScaling(const std::string& str) {
	if (str == "NONE") return StatScaling::NONE;
	if (str == "STRENGTH") return StatScaling::STRENGTH;
	if (str == "AGILITY") return StatScaling::AGILITY;
	if (str == "CHARISMA") return StatScaling::CHARISMA;
	if (str == "INTELLIGENCE") return StatScaling::INTELLIGENCE;
	if (str == "ARCANE") return StatScaling::ARCANE;
	if (str == "FAITH") return StatScaling::FAITH;
	if (str == "LUCK") return StatScaling::LUCK;
}

Defense stringToDefense(const std::string& str) {
	if (str == "NONE") return Defense::NONE;
	if (str == "SLASH") return Defense::SLASH;
	if (str == "BLUNT") return Defense::BLUNT;
	if (str == "PIERCE") return Defense::PIERCE;
	if (str == "CHOP") return Defense::CHOP;
	if (str == "MAGIC") return Defense::MAGIC;
	if (str == "FIRE") return Defense::FIRE;
	if (str == "FROST") return Defense::FROST;
	if (str == "SHOCK") return Defense::SHOCK;
	if (str == "WIND") return Defense::WIND;
	if (str == "POISON") return Defense::POISON;
	if (str == "BLEED") return Defense::BLEED;
	if (str == "SLEEP") return Defense::SLEEP;
	if (str == "DARK") return Defense::DARK;
	if (str == "HOLY") return Defense::HOLY;
	throw std::invalid_argument("Invalid Defense string: " + str);
}

Weapon::WeaponType stringToWeaponType(const std::string& str) {
    if (str == "DAGGER") return Weapon::WeaponType::DAGGER;
    if (str == "STRAIGHTSWORD") return Weapon::WeaponType::STRAIGHTSWORD;
    if (str == "GREATSWORD") return Weapon::WeaponType::GREATSWORD;
    if (str == "FIST") return Weapon::WeaponType::FIST;
    if (str == "MACE") return Weapon::WeaponType::MACE;
    if (str == "GREATMACE") return Weapon::WeaponType::GREATMACE;
    if (str == "HATCHET") return Weapon::WeaponType::HATCHET;
    if (str == "AXE") return Weapon::WeaponType::AXE;
    if (str == "GREATAXE") return Weapon::WeaponType::GREATAXE;
    if (str == "THRUSTINGSWORD") return Weapon::WeaponType::THRUSTINGSWORD;
    if (str == "SPEAR") return Weapon::WeaponType::SPEAR;
    if (str == "GREATSPEAR") return Weapon::WeaponType::GREATSPEAR;
    if (str == "HALBERD") return Weapon::WeaponType::HALBERD;
    if (str == "POLEHAMMER") return Weapon::WeaponType::POLEHAMMER;
    if (str == "PARRYSHIELD") return Weapon::WeaponType::PARRYSHIELD;
    if (str == "MEDIUMSHIELD") return Weapon::WeaponType::MEDIUMSHIELD;
    if (str == "GREATSHIELD") return Weapon::WeaponType::GREATSHIELD;
    if (str == "LONGBOW") return Weapon::WeaponType::LONGBOW;
    if (str == "COMPOUNDBOW") return Weapon::WeaponType::COMPOUNDBOW;
    if (str == "GREATBOW") return Weapon::WeaponType::GREATBOW;
    if (str == "MINICROSSBOW") return Weapon::WeaponType::MINICROSSBOW;
    if (str == "CROSSBOW") return Weapon::WeaponType::CROSSBOW;
    if (str == "BALLISTA") return Weapon::WeaponType::BALLISTA;
    if (str == "WAND") return Weapon::WeaponType::WAND;
    if (str == "STAFF") return Weapon::WeaponType::STAFF;
	if (str == "INSTRUMENT") return Weapon::WeaponType::INSTRUMENT;
    throw std::invalid_argument("Invalid WeaponType string: " + str);
}


Potion::PotionEffect stringToPotionEffect(const std::string& str) {
    if (str == "NONE") return Potion::NONE;
    if (str == "HEALING") return Potion::HEALING;
    if (str == "FATIGUE") return Potion::FATIGUE;
    if (str == "MAXHEALTH") return Potion::MAXHEALTH;
    if (str == "MAXFATIGUE") return Potion::MAXFATIGUE;
    if (str == "HEALTHREGEN") return Potion::HEALTHREGEN;
    if (str == "FATIGUEREGEN") return Potion::FATIGUEREGEN;
    if (str == "ATTACKSPEED") return Potion::ATTACKSPEED;
    if (str == "CASTSPEED") return Potion::CASTSPEED;
    if (str == "SPEED") return Potion::SPEED;
    if (str == "PHYSICALRESISTANCE") return Potion::PHYSICALRESISTANCE;
    if (str == "MAGICRESISTANCE") return Potion::MAGICRESISTANCE;
    if (str == "FIRERESISTANCE") return Potion::FIRERESISTANCE;
    if (str == "FROSTRESISTANCE") return Potion::FROSTRESISTANCE;
    if (str == "LIGHTNINGRESISTANCE") return Potion::LIGHTNINGRESISTANCE;
    if (str == "DARKRESISTANCE") return Potion::DARKRESISTANCE;
    if (str == "HOLYRESISTANCE") return Potion::HOLYRESISTANCE;
    if (str == "WINDRESISTANCE") return Potion::WINDRESISTANCE;
    if (str == "BLEEDRESISTANCE") return Potion::BLEEDRESISTANCE;
    if (str == "POISONRESISTANCE") return Potion::POISONRESISTANCE;
    if (str == "SLEEPRESISTANCE") return Potion::SLEEPRESISTANCE;
    if (str == "ALLRESISTANCE") return Potion::ALLRESISTANCE;
    if (str == "BLOCKCHANCE") return Potion::BLOCKCHANCE;
    if (str == "DODGECHANCE") return Potion::DODGECHANCE;
    if (str == "CRITCHANCE") return Potion::CRITCHANCE;
    if (str == "ESCAPE") return Potion::ESCAPE;
    if (str == "STRENGTH") return Potion::STRENGTH;
    if (str == "AGILITY") return Potion::AGILITY;
    if (str == "INTELLIGENCE") return Potion::INTELLIGENCE;
    if (str == "CHARISMA") return Potion::CHARISMA;
    if (str == "ARCANE") return Potion::ARCANE;
    if (str == "FAITH") return Potion::FAITH;
    if (str == "LUCK") return Potion::LUCK;
    if (str == "TELEPORT") return Potion::TELEPORT;
    if (str == "RESURRECT") return Potion::RESURRECT;
    if (str == "RANDOM") return Potion::RANDOM;
    throw std::invalid_argument("Invalid PotionEffect string: " + str);
}

Armor::ArmorDescriptor stringToArmorDescriptor(const std::string& str) {
	if (str == "CLOTH") return Armor::ArmorDescriptor::CLOTH;
    if (str == "LEATHER") return Armor::ArmorDescriptor::LEATHER;
    if (str == "PADDED") return Armor::ArmorDescriptor::PADDED;
    if (str == "STUDDEDLEATHER") return Armor::ArmorDescriptor::STUDDEDLEATHER;
    if (str == "CHAIN") return Armor::ArmorDescriptor::CHAIN;
    if (str == "LAMELLAR") return Armor::ArmorDescriptor::LAMELLAR;
    if (str == "SCALE") return Armor::ArmorDescriptor::SCALE;
    if (str == "CHAINPLATE") return Armor::ArmorDescriptor::CHAINPLATE;
    if (str == "BEASTSCALE") return Armor::ArmorDescriptor::BEASTSCALE;
    if (str == "FULLPLATE") return Armor::ArmorDescriptor::FULLPLATE;

    throw std::invalid_argument("Invalid ArmorDescriptor string: " + str);
}

Ammunition::AmmoType stringToAmmoType(const std::string& str) {
    if (str == "ARROW") return Ammunition::AmmoType::ARROW;
    if (str == "GREATARROW") return Ammunition::AmmoType::GREATARROW;
    if (str == "MINIBOLT") return Ammunition::AmmoType::MINIBOLT;
    if (str == "BOLT") return Ammunition::AmmoType::BOLT;
    if (str == "BALLISTABOLT") return Ammunition::AmmoType::BALLISTABOLT;
    if (str == "CANNONSHELL") return Ammunition::AmmoType::CANNONSHELL;

    throw std::invalid_argument("Invalid AmmoType string: " + str);
}

Trinket::TrinketType stringToTrinketType(const std::string& str) {
    if (str == "AMULET") return Trinket::TrinketType::AMULET;
    if (str == "RING")   return Trinket::TrinketType::RING;
    if (str == "MISC")   return Trinket::TrinketType::MISC;

    throw std::invalid_argument("Invalid TrinketType string: " + str);
}

Human::Personality stringToPersonality(const std::string& str) {
    if (str == "GENERIC") return Human::GENERIC;
    if (str == "COWARDLY") return Human::COWARDLY;
    if (str == "BRAVE") return Human::BRAVE;
    if (str == "EAGER") return Human::EAGER;
    if (str == "CRUEL") return Human::CRUEL;
    if (str == "BRUTE") return Human::BRUTE;
    if (str == "ROYAL") return Human::ROYAL;
    if (str == "PEASANT") return Human::PEASANT;
    if (str == "YOUNG") return Human::YOUNG;
    if (str == "OLD") return Human::OLD;

    throw std::invalid_argument("Invalid Personality string: " + str);
}

Item::EquipSlots stringToEquipSlot(const std::string& str)
{
	if (str == "HEAD") return Item::EquipSlots::HEAD;
	if (str == "CHEST") return Item::EquipSlots::CHEST;
	if (str == "ARMS") return Item::EquipSlots::ARMS;
	if (str == "LEGS") return Item::EquipSlots::LEGS;
	if (str == "AMULET") return Item::EquipSlots::AMULET;
	if (str == "RING1") return Item::EquipSlots::RING1;
	if (str == "RING2") return Item::EquipSlots::RING2;
	if (str == "MAINHAND") return Item::EquipSlots::MAINHAND;
	if (str == "OFFHAND") return Item::EquipSlots::OFFHAND;
	if (str == "RESERVE1") return Item::EquipSlots::RESERVE1;
	if (str == "RESERVE2") return Item::EquipSlots::RESERVE2;
	if (str == "MISC") return Item::EquipSlots::MISC;
	if (str == "BACKPACK") return Item::EquipSlots::BACKPACK;
	if (str == "QUIVER1") return Item::EquipSlots::QUIVER1;
	if (str == "QUIVER2") return Item::EquipSlots::QUIVER2;
	if (str == "QUIVER3") return Item::EquipSlots::QUIVER3;
	if (str == "QUIVER4") return Item::EquipSlots::QUIVER4;
	throw std::invalid_argument("Invalid EquipSlot string: " + str);
}

Character::CombatFlags stringToCombatFlag(const std::string& str) {
    if (str == "NEUTRAL") return Character::CombatFlags::NEUTRAL;
    if (str == "BLEEDING") return Character::CombatFlags::BLEEDING;
    if (str == "BURNING") return Character::CombatFlags::BURNING;
    if (str == "FROSTBITTEN") return Character::CombatFlags::FROSTBITTEN;
    if (str == "POISONED") return Character::CombatFlags::POISONED;
    if (str == "SHOCKED") return Character::CombatFlags::SHOCKED;
    if (str == "SLEEPY") return Character::CombatFlags::SLEEPY;
    if (str == "FEAR") return Character::CombatFlags::FEAR;
    if (str == "FRENZY") return Character::CombatFlags::FRENZY;
    if (str == "FROZEN") return Character::CombatFlags::FROZEN;
    if (str == "HEALING") return Character::CombatFlags::HEALING;
    if (str == "ENHANCEDARMOR") return Character::CombatFlags::ENHANCEDARMOR;
    if (str == "CANESCAPE") return Character::CombatFlags::CANESCAPE;
    if (str == "RESURRECTED") return Character::CombatFlags::RESURRECTED;
    if (str == "STUNNED") return Character::CombatFlags::STUNNED;
    throw std::invalid_argument("Invalid CombatFlag string: " + str);
}

std::unordered_map<int, float> positionFromJson(const nlohmann::json& j) {
    std::unordered_map<int, float> positionMap;
    for (auto it = j.begin(); it != j.end(); ++it) {
        int id = std::stoi(it.key());
        float dist = it.value();
        positionMap[id] = dist;
    }
    return positionMap;
}

//TO JSON HELPERS
std::string damageTypesToString(DamageTypes type) {
    switch (type) {
    case DamageTypes::NONE: return "NONE";
    case DamageTypes::SLASH: return "SLASH";
    case DamageTypes::PIERCE: return "PIERCE";
    case DamageTypes::BLUNT: return "BLUNT";
    case DamageTypes::CHOP: return "CHOP";
    case DamageTypes::MAGIC: return "MAGIC";
    case DamageTypes::FIRE: return "FIRE";
    case DamageTypes::FROST: return "FROST";
    case DamageTypes::SHOCK: return "SHOCK";
    case DamageTypes::WIND: return "WIND";
    case DamageTypes::POISON: return "POISON";
    case DamageTypes::BLEED: return "BLEED";
    case DamageTypes::SLEEP: return "SLEEP";
    case DamageTypes::DARK: return "DARK";
    case DamageTypes::HOLY: return "HOLY";
    default: throw std::invalid_argument("Invalid PhysicalDamageType enum");
    }
}

std::string DamageTypesToString(DamageTypes type) {
    switch (type) {

    default: throw std::invalid_argument("Invalid DamageTypes enum");
    }
}

std::string statScalingToString(StatScaling type) {
    switch (type) {
    case StatScaling::NONE: return "NONE";
    case StatScaling::STRENGTH: return "STRENGTH";
    case StatScaling::AGILITY: return "AGILITY";
    case StatScaling::CHARISMA: return "CHARISMA";
    case StatScaling::INTELLIGENCE: return "INTELLIGENCE";
    case StatScaling::ARCANE: return "ARCANE";
    case StatScaling::FAITH: return "FAITH";
    case StatScaling::LUCK: return "LUCK";
    default: throw std::invalid_argument("Invalid StatScaling enum");
    }
}

std::string defenseToString(Defense type) {
    switch (type) {
    case Defense::NONE: return "NONE";
    case Defense::SLASH: return "SLASH";
    case Defense::BLUNT: return "BLUNT";
    case Defense::PIERCE: return "PIERCE";
    case Defense::CHOP: return "CHOP";
    case Defense::MAGIC: return "MAGIC";
    case Defense::FIRE: return "FIRE";
    case Defense::FROST: return "FROST";
    case Defense::SHOCK: return "SHOCK";
    case Defense::WIND: return "WIND";
    case Defense::POISON: return "POISON";
    case Defense::BLEED: return "BLEED";
    case Defense::SLEEP: return "SLEEP";
    case Defense::DARK: return "DARK";
    case Defense::HOLY: return "HOLY";
    default: throw std::invalid_argument("Invalid Defense enum");
    }
}

std::string weaponTypeToString(Weapon::WeaponType type) {
    switch (type) {
    case Weapon::WeaponType::DAGGER: return "DAGGER";
    case Weapon::WeaponType::STRAIGHTSWORD: return "STRAIGHTSWORD";
    case Weapon::WeaponType::GREATSWORD: return "GREATSWORD";
    case Weapon::WeaponType::FIST: return "FIST";
    case Weapon::WeaponType::MACE: return "MACE";
    case Weapon::WeaponType::GREATMACE: return "GREATMACE";
    case Weapon::WeaponType::HATCHET: return "HATCHET";
    case Weapon::WeaponType::AXE: return "AXE";
    case Weapon::WeaponType::GREATAXE: return "GREATAXE";
    case Weapon::WeaponType::THRUSTINGSWORD: return "THRUSTINGSWORD";
    case Weapon::WeaponType::SPEAR: return "SPEAR";
    case Weapon::WeaponType::GREATSPEAR: return "GREATSPEAR";
    case Weapon::WeaponType::HALBERD: return "HALBERD";
    case Weapon::WeaponType::POLEHAMMER: return "POLEHAMMER";
    case Weapon::WeaponType::PARRYSHIELD: return "PARRYSHIELD";
    case Weapon::WeaponType::MEDIUMSHIELD: return "MEDIUMSHIELD";
    case Weapon::WeaponType::GREATSHIELD: return "GREATSHIELD";
    case Weapon::WeaponType::LONGBOW: return "LONGBOW";
    case Weapon::WeaponType::COMPOUNDBOW: return "COMPOUNDBOW";
    case Weapon::WeaponType::GREATBOW: return "GREATBOW";
    case Weapon::WeaponType::MINICROSSBOW: return "MINICROSSBOW";
    case Weapon::WeaponType::CROSSBOW: return "CROSSBOW";
    case Weapon::WeaponType::BALLISTA: return "BALLISTA";
    case Weapon::WeaponType::WAND: return "WAND";
    case Weapon::WeaponType::STAFF: return "STAFF";
	case Weapon::WeaponType::INSTRUMENT: return "INSTRUMENT";
    default: throw std::invalid_argument("Invalid WeaponType enum");
    }
}


std::string equipSlotToString(Item::EquipSlots slot) {
    switch (slot) {
    case Item::EquipSlots::HEAD: return "HEAD";
    case Item::EquipSlots::CHEST: return "CHEST";
    case Item::EquipSlots::ARMS: return "ARMS";
    case Item::EquipSlots::LEGS: return "LEGS";
    case Item::EquipSlots::AMULET: return "AMULET";
    case Item::EquipSlots::RING1: return "RING1";
    case Item::EquipSlots::RING2: return "RING2";
    case Item::EquipSlots::MAINHAND: return "MAINHAND";
    case Item::EquipSlots::OFFHAND: return "OFFHAND";
    case Item::EquipSlots::RESERVE1: return "RESERVE1";
    case Item::EquipSlots::RESERVE2: return "RESERVE2";
    case Item::EquipSlots::MISC: return "MISC";
    case Item::EquipSlots::BACKPACK: return "BACKPACK";
    case Item::EquipSlots::QUIVER1: return "QUIVER1";
    case Item::EquipSlots::QUIVER2: return "QUIVER2";
    case Item::EquipSlots::QUIVER3: return "QUIVER3";
    case Item::EquipSlots::QUIVER4: return "QUIVER4";
    default: throw std::invalid_argument("Invalid EquipSlot enum");
    }
}

std::string armorDescriptorToString(Armor::ArmorDescriptor desc) {
    switch (desc) {
	case Armor::ArmorDescriptor::CLOTH: return "CLOTH";
    case Armor::ArmorDescriptor::LEATHER: return "LEATHER";
	case Armor::ArmorDescriptor::PADDED: return "PADDED";
	case Armor::ArmorDescriptor::STUDDEDLEATHER: return "STUDDEDLEATHER";
	case Armor::ArmorDescriptor::CHAIN: return "CHAIN";
	case Armor::ArmorDescriptor::LAMELLAR: return "LAMELLAR";
	case Armor::ArmorDescriptor::SCALE: return "SCALE";
	case Armor::ArmorDescriptor::CHAINPLATE: return "CHAINPLATE";
	case Armor::ArmorDescriptor::BEASTSCALE: return "BEASTSCALE";
	case Armor::ArmorDescriptor::FULLPLATE: return "FULLPLATE";
    default: return "UNKNOWN";
    }
}

std::string ammoTypeToString(Ammunition::AmmoType type) {
    switch (type) {
    case Ammunition::AmmoType::ARROW: return "ARROW";
	case Ammunition::AmmoType::GREATARROW: return "GREATARROW";
    case Ammunition::AmmoType::MINIBOLT: return "MINIBOLT";
    case Ammunition::AmmoType::BOLT: return "BOLT";
    case Ammunition::AmmoType::BALLISTABOLT: return "BALLISTABOLT";
    case Ammunition::AmmoType::CANNONSHELL: return "CANNONSHELL";
    default: return "UNKNOWN";
    }
}

std::string potionEffectToString(Potion::PotionEffect effect) {
    switch (effect) {
    case Potion::NONE: return "NONE";
    case Potion::HEALING: return "HEALING";
    case Potion::FATIGUE: return "FATIGUE";
    case Potion::MAXHEALTH: return "MAXHEALTH";
    case Potion::MAXFATIGUE: return "MAXFATIGUE";
    case Potion::HEALTHREGEN: return "HEALTHREGEN";
    case Potion::FATIGUEREGEN: return "FATIGUEREGEN";
    case Potion::ATTACKSPEED: return "ATTACKSPEED";
    case Potion::CASTSPEED: return "CASTSPEED";
    case Potion::SPEED: return "SPEED";
    case Potion::PHYSICALRESISTANCE: return "PHYSICALRESISTANCE";
    case Potion::MAGICRESISTANCE: return "MAGICRESISTANCE";
    case Potion::FIRERESISTANCE: return "FIRERESISTANCE";
    case Potion::FROSTRESISTANCE: return "FROSTRESISTANCE";
    case Potion::LIGHTNINGRESISTANCE: return "LIGHTNINGRESISTANCE";
    case Potion::DARKRESISTANCE: return "DARKRESISTANCE";
    case Potion::HOLYRESISTANCE: return "HOLYRESISTANCE";
    case Potion::WINDRESISTANCE: return "WINDRESISTANCE";
    case Potion::BLEEDRESISTANCE: return "BLEEDRESISTANCE";
    case Potion::POISONRESISTANCE: return "POISONRESISTANCE";
    case Potion::SLEEPRESISTANCE: return "SLEEPRESISTANCE";
    case Potion::ALLRESISTANCE: return "ALLRESISTANCE";
    case Potion::BLOCKCHANCE: return "BLOCKCHANCE";
    case Potion::DODGECHANCE: return "DODGECHANCE";
    case Potion::CRITCHANCE: return "CRITCHANCE";
    case Potion::ESCAPE: return "ESCAPE";
    case Potion::STRENGTH: return "STRENGTH";
    case Potion::AGILITY: return "AGILITY";
    case Potion::INTELLIGENCE: return "INTELLIGENCE";
    case Potion::CHARISMA: return "CHARISMA";
    case Potion::ARCANE: return "ARCANE";
    case Potion::FAITH: return "FAITH";
    case Potion::LUCK: return "LUCK";
    case Potion::TELEPORT: return "TELEPORT";
    case Potion::RESURRECT: return "RESURRECT";
    case Potion::RANDOM: return "RANDOM";
    default: return "UNKNOWN";
    }
}

std::string trinketTypeToString(Trinket::TrinketType type) {
    switch (type) {
    case Trinket::TrinketType::AMULET: return "AMULET";
    case Trinket::TrinketType::RING:   return "RING";
    case Trinket::TrinketType::MISC:   return "MISC";
    default: return "UNKNOWN";
    }
}

std::string personalityToString(Human::Personality p) {
    switch (p) {
    case Human::GENERIC: return "GENERIC";
    case Human::COWARDLY: return "COWARDLY";
    case Human::BRAVE: return "BRAVE";
    case Human::EAGER: return "EAGER";
    case Human::CRUEL: return "CRUEL";
    case Human::BRUTE: return "BRUTE";
    case Human::ROYAL: return "ROYAL";
    case Human::PEASANT: return "PEASANT";
    case Human::YOUNG: return "YOUNG";
    case Human::OLD: return "OLD";
    default: return "UNKNOWN";
    }
}

std::string combatFlagToString(Character::CombatFlags flag) {
    switch (flag) {
    case Character::CombatFlags::NEUTRAL: return "NEUTRAL";
    case Character::CombatFlags::BLEEDING: return "BLEEDING";
    case Character::CombatFlags::BURNING: return "BURNING";
    case Character::CombatFlags::FROSTBITTEN: return "FROSTBITTEN";
    case Character::CombatFlags::POISONED: return "POISONED";
    case Character::CombatFlags::SHOCKED: return "SHOCKED";
    case Character::CombatFlags::SLEEPY: return "SLEEPY";
    case Character::CombatFlags::FEAR: return "FEAR";
    case Character::CombatFlags::FRENZY: return "FRENZY";
    case Character::CombatFlags::FROZEN: return "FROZEN";
    case Character::CombatFlags::HEALING: return "HEALING";
    case Character::CombatFlags::ENHANCEDARMOR: return "ENHANCEDARMOR";
    case Character::CombatFlags::CANESCAPE: return "CANESCAPE";
    case Character::CombatFlags::RESURRECTED: return "RESURRECTED";
    case Character::CombatFlags::STUNNED: return "STUNNED";
    default: return "UNKNOWN";
    }
}

nlohmann::json positionToJson(const std::unordered_map<int, float>& positionMap) {
    nlohmann::json j;
    for (const auto& [id, dist] : positionMap) {
        j[std::to_string(id)] = dist;
    }
    return j;
}

//General Helpers

int validateInput(int min, int max)
{
    int choice;
    do
    {
        std::cout << "\n=--->\n" << std::endl;
        std::cout << ">> ";
        std::cin >> choice;
        if (std::cin.fail() || choice > max || choice < min)
        {
            std::cout << "Enter a number from " << min << " - " << max << std::endl;
        }
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    } while (std::cin.fail() || choice > max || choice < min);
    return choice;
}