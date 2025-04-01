#ifndef Character_h
#define Character_h

#include <string>
#include <vector>
#include "Inventory.h"
#include "Item.h"
#include <functional>
#include "Ammunition.h"
#include "ThrownConsumable.h"
#include "optional"
#include "Defense.h"
#include <unordered_map>
#include "IDManager.h"

//forward declaration to avoid circular dependency
class Human;
class Creature;
class Effect;
class Spell;
class Weapon;
class Ammunition;
class ThrownConsumable;
class Character : public std::enable_shared_from_this<Character>
{
public:
	int id;

	//Base defensive values for those that don't wear armor or for hardier creatures
	std::unordered_map<Defense, float> defenseValues;
	Defense defenseType = Defense::NONE;

	bool isAlly = false;
	bool namedCharacter = false;
	bool isAlive = true;
	bool active = true;
	bool alert = false;
	std::string name = "CHARACTER NAME PLS CHANGE";
	std::string description = "DESCRIPTION PLS CHANGE";
	float confidenceLevel = 100.0f;
	float healthPoints = 100.0f;
	float maxHealthPoints = 100.0f;
	float fatiguePoints = 50.0f;
	float maxFatiguePoints = 50.0f;
	float speed = 100.0f;
	float critChance = 0.0f;
	float dodgeChance = 0.0f;
	float blockChance = 0.0f;
	//Status effect variables
	float bleedPoints = 100.0f;
	float maxBleedPoints = 100.0f;
	float burnPoints = 100.0f;
	float maxBurnPoints = 100.0f;
	float poisonPoints = 100.0f;
	float maxPoisonPoints = 100.0f;
	float frostPoints = 100.0f;
	float maxFrostPoints = 100.0f;
	float shockPoints = 100.0f;
	float maxShockPoints = 100.0f;
	float sleepPoints = 100.0f;
	float maxSleepPoints = 100.0f;
	std::unordered_map<int, float> position;
	float level = 1.0f;

	//Flags for combat scenarios
	enum class CombatFlags { 
		NEUTRAL, 
		BLEEDING, 
		BURNING, 
		FROSTBITTEN, 
		POISONED, 
		SHOCKED, 
		SLEEPY, 
		FEAR, 
		FRENZY, 
		FROZEN, 
		HEALING, 
		ENHANCEDARMOR, 
		CANESCAPE,
		RESURRECTED,
		STUNNED
	};
	CombatFlags combatFlag = CombatFlags::NEUTRAL;
	std::vector<CombatFlags> combatFlags;

	Inventory inventory;

	//must be a pointer because of *polymorphism*
	std::vector < std::shared_ptr<Effect>> effects; //Enchantments that are currently affecting the character
	
	//vector of spells they can cast
	std::vector < std::shared_ptr<Spell>> attunedSpells;

	//vector of spells they know but can't cast
	std::vector < std::shared_ptr<Spell>> knownSpells;
	
	//Vector of human allies 
	std::vector < std::shared_ptr<Character>> allies;

	//Tages for dialogue responses/conditions
	std::vector < std::shared_ptr<std::string>> tags;

	void addTag(std::string& tag);

	//Getters and setters for defense values
	float getDefenseValue(Defense);

	void setDefenseValue(Defense, float defenseValue);

	virtual nlohmann::json toJson() const = 0;
	static std::shared_ptr<Character> fromJson(const nlohmann::json& j);

	int getId() const;

	//Virtual functions to be overridden by the human and creature classes
	virtual float getLuck() const { return 0.0f; } 
	virtual float getFaith() const { return 0.0f; } 
	virtual float getArcane() const { return 0.0f; } 
	virtual float getIntelligence() const { return 0.0f; } 
	virtual float getCharisma() const { return 0.0f; } 
	virtual float getAgility() const { return 0.0f; } 
	virtual float getStrength() const { return 0.0f; } 
	virtual float getFatigue() const { return 0.0f; } 
	virtual float getHealth() const { return 0.0f; } 
	virtual float getSpeed() const { return 0.0f; }
	virtual float getLevel() const { return 0.0f; }

	//Default Constructor
	Character() = default;

	//Main Constructor
	Character(bool isAlly, bool namedCharacter, bool isAlive, bool active, bool alert,
		std::string name, std::string description, float confidenceLevel,
		float healthPoints, float maxHealthPoints, float fatiguePoints,
		float maxFatiguePoints, float speed, float critChance, float dodgeChance,
		float blockChance, float bleedPoints, float maxBleedPoints,
		float burnPoints, float maxBurnPoints, float poisonPoints,
		float maxPoisonPoints, float frostPoints, float maxFrostPoints,
		float shockPoints, float maxShockPoints, float sleepPoints,
		float maxSleepPoints, const Inventory& inventory,
		float level, CombatFlags combatFlag);


	//Deconstructor
	virtual ~Character() = default;

	void addCombatFlag(Character::CombatFlags flag);

	void decayStatusEffects(std::shared_ptr<Character> target);

	//DESC: Chooses the ammunition to be used with a ranged weapon, sets it to ammo. Taraget is used to calculate damage
	//PRE: The character must have a ranged weapon equipped	
	//POST: The ammunition will be selected and used in the fireRangedWeapon function
	bool chooseAmmunition(std::shared_ptr<Weapon> weapon, std::shared_ptr<Character> target, std::shared_ptr<Ammunition> ammo);

	//DESC: Fires a ranged weapon at a provided target with the provided ammunition
	//PRE: chooseAmmunition shoud be properly called and used to select the ammunition to be used and call this function
	//POST: target will take damage, ammo choice will be passed to consume ammo method and decremeneted or removed
	void fireRangedWeapon(std::shared_ptr<Character> target, std::shared_ptr<Weapon> weapon, std::shared_ptr<Ammunition> ammo);

	//DESC: Fires a ranged weapon at a provided target, decrementing or removing ammunition as necessary
	//PRE: chooseAmmunition shoud be properly called and used to select the ammunition to be used and call this function
	//POST: Ammunition will be decremented or removed from the inventory, damage values will be sent to the takeDamage function to apply to target
	void consumeAmmo(std::shared_ptr<Ammunition> ammo);

	//DESC: throws a ranged consumable at a provided target, then passing the consumable to the consumeThrownConsumable function
	//PRE: chooseAmmunition shoud be properly called and used to select the ammunition to be used and call this function
	//POST: Target will take all damage and effects associated with the thrown weapon
	void throwThrownConsumable(std::shared_ptr<ThrownConsumable> consumable, std::shared_ptr<Character> target);

	//DESC: this function will decrement the consumable's quantity and remove if necessary
	//PRE: The consumable must have a quantity greater than 0
	//POST: The consumable's quantity will be decremented, or the consumable will be removed from the inventory if the quantity is 0
	void consumeThrownConsumable(std::shared_ptr<ThrownConsumable> consumable);

	//DESC: Kills the character, setting isAlive to false
	//PRE: The character must be alive
	//POST: The character will be dead
	void killCharacter();

	//DESC: Prints a menu allowing user to choose a spell from their attuned spells
	// If they dont have enough fatigue or choose to cancel it will return without casting
	// the spell
	//PRE: The character must have attuned spells, a valid catalyst,
	// and a valid target should be passed 
	//POST: TakeDamage will be called with all relevant parameters to cast a spell and
	// apply its effects
	bool chooseSpell(Weapon& weapon, std::vector<std::shared_ptr<Character>> enemyTargets, std::vector<std::shared_ptr<Character>> allyTargets, 
		std::shared_ptr<Spell>& spell, std::shared_ptr<Character>& target));

	void viewSpells();

	void viewSpellsBrief();

	//DESC: Removes a spell from the characters attuned spells/known spells
	//PRE: The spell must be valid and in the characters attuned spells/known spells
	//POST: The spell will be removed from the characters attuned spells/known spells
	void removeSpell(std::shared_ptr<Spell> spellToRemove);

	void castSpell(Spell& spell, std::shared_ptr<Weapon> weapon, std::shared_ptr<Character> target);

	void attackWithMelee(std::shared_ptr<Weapon> weapon, std::shared_ptr<Character> target);

	//DESC: A consumable is used on the character, applying its effects
	//PRE: The consumable must be valid and have effects
	//POST: The consumable's effects will be applied to the character, quantity will be decremented and item removed if necessary
	void useConsumable(std::shared_ptr<Consumable> consumable);

	//DESC: A weapon art is performed and all effects contained with it are applied to the target
	//PRE: A valid weapon and weapon art should be selected and used on the proper target. This function does not chose the target
	//POST: All effects contained within the weaopn art will be applied to their relevant targets
	void attackWithWeaponArt(std::shared_ptr<Weapon> weapon, std::shared_ptr<Character> target);

	//DESC: A consumable is used on the target, applying its effects
	//PRE: The consumable must be valid and have effects
	//POST: The consumable's effects will be applied to the target, quantity will be decremented and item removed if necessary
	void shareConsumable(std::shared_ptr<Consumable> consumable, std::shared_ptr<Character> target);
};
#endif // !Character_h


