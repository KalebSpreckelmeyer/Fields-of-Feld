#pragma once
#include "PhysicalDamageType.h"
#include "DamageTypes.h"
#include "StatScaling.h"
#include <string>
#include "Weapon.h"
#include "Defense.h"
#include "Armor.h"
#include "Trinket.h"
#include "Human.h"

//FROM JSON HELPERS
DamageTypes stringToDamageTypes(const std::string& str);

Defense stringToDefense(const std::string& str);

StatScaling stringToStatScaling(const std::string& str);

Weapon::WeaponType stringToWeaponType(const std::string& str);

Item::EquipSlots stringToEquipSlot(const std::string& str);

Potion::PotionEffect stringToPotionEffect(const std::string& str);

Armor::ArmorDescriptor stringToArmorDescriptor(const std::string& str);

Ammunition::AmmoType stringToAmmoType(const std::string& str);

Trinket::TrinketType stringToTrinketType(const std::string& str);

Human::Personality stringToPersonality(const std::string& str);

Character::CombatFlags stringToCombatFlag(const std::string& str);

std::unordered_map<int, float> positionFromJson(const nlohmann::json& j);

//TO JSON HELPERS
std::string damageTypesToString(DamageTypes type);

std::string statScalingToString(StatScaling type);

std::string defenseToString(Defense type);

std::string weaponTypeToString(Weapon::WeaponType type);

std::string equipSlotToString(Item::EquipSlots slot);

std::string armorDescriptorToString(Armor::ArmorDescriptor desc);

std::string ammoTypeToString(Ammunition::AmmoType type);

std::string potionEffectToString(Potion::PotionEffect effect);

std::string trinketTypeToString(Trinket::TrinketType type);

std::string personalityToString(Human::Personality p);

std::string combatFlagToString(Character::CombatFlags flag);

nlohmann::json positionToJson(const std::unordered_map<int, float>& positionMap);

//General Helpers

int validateInput(int min, int max);
