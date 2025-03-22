#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include <algorithm>
#include "color.hpp"
#include "Item.h"
#include "Character.h"
#include "Creature.h"
#include "optional"
#include "Dialogue.h"
#include "Weapon.h"
#include "Armor.h"
#include "Trinket.h"
#include "Human.h"
#include "Consumable.h"
#include "ThrownConsumable.h"
#include "nlohmann/json.hpp"
#include "Enchantment.h"
#include "Effect.h"
#include "Spell.h"
#include "Potion.h"

using namespace std;
using json = nlohmann::json;

#pragma region Function Declarations
//DESC: Validates the user inputted a number within the specified range
//PRE: Min and max values must be passed in
//POST: Returns the validated input
int validateInput(int min, int max);
//DESC:
//PRE:
//POST:
void openCombat(std::shared_ptr<Human> player, shared_ptr<Character> enemy);
//DESC: Gets a random, context sensitive banter line from the sender to the reciever
//PRE: Sender and reciever must be initialized
//POST: Reciever will be insulted, results printed to console (enemy characters will have their confidence lowered)
//void getCombatBanter(Character sender, Character& reciever);
//DESC:
//PRE:
//POST:
//void getGenericCombatBanter(Character sender);
//DESC:
//PRE:
//POST:
void playerTurn(std::shared_ptr<Human> player, shared_ptr<Weapon> weaponChoice, std::shared_ptr<Ammunition> ammoChoice, shared_ptr<Spell> spellChoice, shared_ptr<Character> targetChoice, std::shared_ptr<ThrownConsumable> thrownConsumableChoice,
	std::shared_ptr<Consumable> consumableChoice, float playerMovement);
#pragma endregion Function Declarations
extern void setupDialogue(std::vector<Dialogue>& dialogues, shared_ptr<Character> player, shared_ptr<Character> npc);

int main()
{
	/*std::cout << std::fixed << std::setprecision(2) << std::endl;
	json example = { {"name", "BUNGUS"}, {"class", "WIZARD"} };
	cout << "Character: " << example.dump(4) << endl;*/
	/*vector<Dialogue> dialogues;
	std::shared_ptr<Human> player = new Human;
	player->setCharacterClass(Human::CharacterClass::WIZARD);
	std::shared_ptr<Human> npc = new Human;
	npc->setCharacterClass(Human::CharacterClass::KNIGHT);
	npc->name = "Knight";
	player->name = "BUNGUS";
	setupDialogue(dialogues, player, npc);

	dialogues[0].playConversation();

	delete player;
	delete npc;*/
	//std::shared_ptr<Human> npc = new Human();
	////npc->setCharacterClass(Human::CharacterClass::KNIGHT);
	//npc->name = "Knight";
	//npc->healthPoints = 500;
	//npc->maxHealthPoints = 500;
	//npc->distanceFromPlayer = 5;
	//std::shared_ptr<Human> npc2 = new Human();
	//npc->allies.push_back(npc2);
	//std::shared_ptr<Human> player = new Human();
	//player->name = "BUNGUS";


	//do {
	//	cout << "enemy health: " << npc->healthPoints << endl;
	//	cout << "enemy distance: " << npc->distanceFromPlayer << endl;
	//	player->chooseSpell(*staff, npc);
	//	cout << "enemy health: " << npc->healthPoints << endl;
	//	cout << "enemy distance: " << npc->distanceFromPlayer << endl;
	//	std::shared_ptr<Effect> effect = new Effect();
	//	effect->refreshEffects(npc);
	//} while (npc->healthPoints > 0);




	auto player = make_shared<Human>();
	auto ally1 = make_shared<Human>();
	auto bandit1 = make_shared<Human>();
	auto bandit2 = make_shared<Human>();
	player->allies.push_back(ally1);
	bandit1->allies.push_back(bandit2);
	bandit2->allies.push_back(bandit1);
	//shared_ptr<Item> staff = std::make_shared<Weapon>("Staff", "A simple wooden staff", 1, 200, 20, 1, 10, false, false, Weapon::WeaponType::STAFF, Item::EquipSlots::OFFHAND);
	shared_ptr<Spell> force;
	player->faith = 100;
	force = force->getForceBurstEffect(*player);
	player->attunedSpells.push_back(force);
	bandit1->position[player->getId()] = 10;
	bandit2->position[player->getId()] = 30;
	//shared_ptr<Weapon> sword = std::make_shared<Weapon>(false, "Sword", "A simple steel sword", 1, 10, 20, 1, 10, false, false, Weapon::WeaponType::STRAIGHTSWORD, Item::EquipSlots::MAINHAND);
	//sword->setPhysicalDamage(PhysicalDamageType::SLASH, 10);
	//sword->setWeaponRequirementValue(StatScaling::STRENGTH, 20);
	////cout << sword->getWeaponRequirementValue(StatScaling::STRENGTH) << endl;
	//player->inventory.equippedItems.push_back(sword);
	//player->inventory.equippedItems.push_back(staff);
	bandit1->name = "Bandit 1";
	bandit2->name = "Bandit 2";
	bandit1->speed = 250;
	bandit2->speed = 100;
	ally1->speed = 50;
	player->speed = 500;
	player->name = "BING BONG";
	ally1->name = "ALLY 1";
	//staff->hasBeenInitialized = true;
	player->isPlayer = true;
	ally1->isAlly = true;
	player->fatiguePoints = 500;
	player->maxFatiguePoints = 500;
	bandit1->healthPoints = 5000;
	bandit1->maxHealthPoints = 5000;
	bandit2->healthPoints = 5000;
	bandit2->maxHealthPoints = 5000;
	player->arcane = 20;
	player->intelligence = 100;
	shared_ptr<Enchantment> enchant;
	enchant = enchant->getMagicWeaponEffect(*player);
	//sword->enchantments.push_back(enchant);
	////std::shared_ptr<Armor> armor = std::make_shared<Armor>("Steel Chestplate", "TESTING", 40, 50, false, false, true, Armor::ArmorDescriptor::FULLPLATE);
	//armor->setPhysicalResistance(PhysicalDamageType::SLASH, 100);
	//armor->setPhysicalResistance(PhysicalDamageType::PIERCE, 100);
	//armor->setPhysicalResistance(PhysicalDamageType::BLUNT, 100);
	//armor->setPhysicalResistance(PhysicalDamageType::CHOP, 100);
	shared_ptr<Enchantment> enchant2;
	enchant2 = enchant2->getFrostArmorEffect(*player);
	//armor->enchantments.push_back(enchant2);
	//player->inventory.equippedItems.push_back(armor);
	//bandit1->inventory.equippedItems.push_back(armor);
	std::shared_ptr<Spell> fireball;
	fireball = fireball->getFireBallEffect(*player);

	std::shared_ptr<Spell> oak;
	oak = oak->getOakenArmorEffect(*player);

	std::shared_ptr<Spell> summon;
	summon = summon->getSummonAnimalAllyEffect(*player);

	std::shared_ptr<Spell> bonetrousle;
	bonetrousle = bonetrousle->getBonetrousleEffect(*player);

	std::shared_ptr<Spell> grasp;
	grasp = grasp->getEndothermicGraspEffect(*player);

	std::shared_ptr<Spell> fruit;
	fruit = fruit->getFruitOfTheEarthEffect(*player);
	player->attunedSpells.push_back(fruit);
	player->attunedSpells.push_back(grasp);
	player->attunedSpells.push_back(bonetrousle);
	player->attunedSpells.push_back(summon);
	player->attunedSpells.push_back(oak);
	player->attunedSpells.push_back(fireball);
	

	openCombat(player, bandit1);
	return 0;
}

int validateInput(int min, int max)
{
	int choice;
	do
	{
		cout << "\n=--->\n" << endl;
		cout << ">> ";
		cin >> choice;
		if (cin.fail() || choice > max || choice < min)
		{
			cout << "Enter a number from " << min << " - " << max << endl;
		}
		cin.clear();
		cin.ignore(10000, '\n');
	} while (cin.fail() || choice > max || choice < min);
	return choice;
}

//Grab dialogue files from DialogueLines.cpp

string getConfidenceDescription(std::shared_ptr<Human> character)
{
	if (character->confidenceLevel >= 100)
		return "They're jovial, as if you aren't a threat at all.";
	else if (character->confidenceLevel >= 80 && character->confidenceLevel < 100)
		return "They seem confident, but there's something there. Are they starting to get scared?";
	else if (character->confidenceLevel >= 60 && character->confidenceLevel < 80)
		return "If you weren't mistaken, you'd think they're scared of you.";

	else if (character->confidenceLevel >= 40 && character->confidenceLevel < 60)
		return "They're eyeing you like a coinpurse. Is it fear in their eyes?";

	else if (character->confidenceLevel >= 20 && character->confidenceLevel < 40)
		return "They're looking around as if for an exit.";

	else if (character->confidenceLevel >= 0 && character->confidenceLevel < 20)
		return "You can feel the terror in their veins from here.";
	else
		return "You're not quite sure how confident they are.";

}

void openCombat(shared_ptr<Human> player, shared_ptr<Character> enemy)
{
	//set this condition to true if the fight ends for any reason
	bool exitFight = false;
	do
	{

		//SETS ALL NECESSARY VARIABLES FOR THE COMBAT LOOP

		//Get player equipment 
		shared_ptr<Weapon> mainHand, reserve1, offHand, reserve2;

		shared_ptr<Armor> headArmor, chestArmor, armArmor, legArmor;
		shared_ptr<Trinket> amulet, ring1, ring2, misc;
		player->inventory.getEquippedItems(mainHand, offHand, reserve1, reserve2, headArmor, chestArmor, armArmor, legArmor, amulet, ring1, ring2, misc);

		//check if player has equipment to swap to (changes menu color to represent this)
		bool hasStowedWeapons = false;

		if ((reserve2->reach > 0) || (reserve1->reach > 0))
		{
			hasStowedWeapons = true;
		}

		//Used to track the player's consumables and grey out the consumable option if they have none
		/*vector<std::shared_ptr<Item>> consumables = player->inventory.consumables();
		vector<std::shared_ptr<Item>> throwingWeapons = player->inventory.getThrownWeapons();*/

		//tracks the spent ammunition and throwing weapons to be returned at the end of the turn (based on luck and proficiency with item skill)
		vector<Item> spentProjectiles;

		//tracks the living/dead allies and enemies
		vector<shared_ptr<Character>> deadAllies;
		vector<shared_ptr<Character>> deadEnemies;

		vector<shared_ptr<Character>> livingAlliesPointers;
		vector<shared_ptr<Character>> livingEnemiesPointers;
		
		//checks if the allies and enemies are alive and adds them to the living/dead vectors
		if (player->allies.size() > 0)
		{
			for (shared_ptr<Character> ally : player->allies)
			{
				if (ally->isAlive)
				{
					livingAlliesPointers.push_back(ally);
				}
				else
				{
					deadAllies.push_back(ally);
				}
			}
		}
		if (enemy->allies.size() > 0)
		{
			for (shared_ptr<Character> enemy : enemy->allies)
			{
				if (enemy->isAlive)
				{
					livingEnemiesPointers.push_back(enemy);
				}
				else
				{
					deadEnemies.push_back(enemy);
				}
			}
		}
		//Add the enemy to the list of living enemies
		if (enemy->isAlive)	livingEnemiesPointers.push_back(enemy);

		//general variables for the combat loop
		int playerOptionChoice = 0;

		//finds the minimum distance from the player to an enemy from the group
		float minDistanceFromPlayer = 1000;
		for (int i = 0; i < livingEnemiesPointers.size(); i++)
		{
			if (livingEnemiesPointers[i]->position[player->getId()] <= minDistanceFromPlayer)
			{
				minDistanceFromPlayer = livingEnemiesPointers[i]->position[player->getId()];
			}
		}
		//used to determine the color of menu text in the attack option (gold for in range, grey for out of range)
		// they will not be able to select out of range options and this will help them intuit why
		// set to 1000 initially as range will never be this high in practice 
		bool inRange = false;
		//check if any spells attuned are in range
		int spellsInRange = 0;
		for (int i = 0; i < player->attunedSpells.size(); i++)
		{
			if (player->attunedSpells[i]->range >= minDistanceFromPlayer)
			{
				spellsInRange++;
			}
		}
		//check if any spells, mainhand, or offhand weapons are in range
		if (minDistanceFromPlayer <= mainHand->reach || minDistanceFromPlayer <= offHand->reach || spellsInRange > 0)
		{
			inRange = true;
		}

		//INITIAL SANITY CHECKS


		//check if player is dead
		if (!player->isAlive)
		{
			cout << dye::light_red("You have fallen...") << endl;
			exitFight = true;
			break;
		}
		if (player->isAlive && livingEnemiesPointers.size() == 0)
		{
			std::cout << "\n=--->\n" << std::endl;
			cout << "The battlefield is quiet once again..." << endl;
		}
		//End of combat encounter rewards for player (repeated in case the loop terminates here)
		if (player->isAlive && livingEnemiesPointers.size() == 0)
		{
			for (int i = 0; i < deadEnemies.size(); i++)
			{
				int choiec;
				cin >> choiec;
				/*player->gainExperience(deadEnemies[i]);
				player->openLootInterface(deadEnemies[i]); ---------------------------------------------------------- < TODO */
			}
			exitFight = true;
		}

		//set to false initially, true once this has been played. Exists so this text only gets played once
		bool playedBefore = false;

		//INITIAL ENCOUNTER TEXT
		//Player is alive, at least one ally is alive, and at least one enemy is alive
		if (player->isAlive && livingEnemiesPointers.size() > 0 && livingAlliesPointers.size() > 0 && !playedBefore)
		{
			//Encounter text
			std::cout << "\n=--->\n" << std::endl;
			cout << "You encounter";
			for (int i = 0; i < livingEnemiesPointers.size(); i++)
			{
				if (livingEnemiesPointers.size() == 1 && !livingEnemiesPointers[i]->namedCharacter)
				{
					cout << " a " << dye::light_yellow(livingEnemiesPointers[i]->name) << "!" << endl;
				}
				else
				{
					if (i == livingEnemiesPointers.size() - 1)
					{
						cout << " and";
					}
					if (!livingEnemiesPointers[i]->namedCharacter)
					{
						cout << " a " << dye::light_yellow(livingEnemiesPointers[i]->name);
					}
					else
					{
						cout << " " << dye::light_yellow(livingEnemiesPointers[i]->name);
					}
					if (i < livingEnemiesPointers.size() - 1)
					{
						cout << ",";
					}
					if (i == livingEnemiesPointers.size() - 1)
					{
						cout << "!" << endl;
					}
				}
			}
			//Allies text
			std::cout << "\n=--->\n" << std::endl;
			if (player->allies.size() > 1) cout << "Your allies,";
			if (player->allies.size() == 1) cout << "Your ally,";
			for (int i = 0; i < livingAlliesPointers.size(); i++)
			{
				if (livingAlliesPointers.size() == 1)
				{
					cout << " a " << dye::light_yellow(livingAlliesPointers[i]->name) << " joins you!" << endl;
				}
				else
				{
					if (i == livingAlliesPointers.size() - 1)
					{
						cout << " and";
					}
					if (!livingAlliesPointers[i]->namedCharacter)
					{
						cout << " a " << dye::light_yellow(livingAlliesPointers[i]->name);
					}
					else
					{
						cout << " " << dye::light_yellow(livingAlliesPointers[i]->name);
					}
					if (i < livingAlliesPointers.size() - 1)
					{
						cout << ",";
					}
					if (i == livingAlliesPointers.size() - 1)
					{
						cout << " joins you!" << endl;
					}
				}
			}
			playedBefore = true;
		}
		//Player is alive, all allies dead or nonexistant, and at least one enemy is alive
		if (player->isAlive == true && livingEnemiesPointers.size() > 0 && livingAlliesPointers.size() == 0 && !playedBefore)
		{
			//Encounter text
			std::cout << "\n=--->\n" << std::endl;
			cout << "You encounter";
			for (int i = 0; i < livingEnemiesPointers.size(); i++)
			{
				if (livingEnemiesPointers.size() == 1 && !livingEnemiesPointers[i]->namedCharacter)
				{
					cout << " a " << dye::light_yellow(livingEnemiesPointers[i]->name) << "!" << endl;
				}
				else
				{
					if (i == livingEnemiesPointers.size() - 1)
					{
						cout << " and";
					}
					if (!livingEnemiesPointers[i]->namedCharacter)
					{
						cout << " a " << dye::light_yellow(livingEnemiesPointers[i]->name);
					}
					else
					{
						cout << " " << dye::light_yellow(livingEnemiesPointers[i]->name);
					}
					if (i < livingEnemiesPointers.size() - 1)
					{
						cout << ",";
					}
					if (i == livingEnemiesPointers.size() - 1)
					{
						cout << "!" << endl;
					}
				}
			}
			//Allies text
			std::cout << "\n=--->\n" << std::endl;
			cout << "You have no allies to assist you..." << endl;
			playedBefore = true;
		}

		//Intro Context Sensitive Text (repeated in check enemy option along with more details)
		/*for (int i = 0; i < livingEnemiesPointers.size(); i++) ----------------------------------------------------------< TODO
		{
			std::cout << "\n=--->\n" << std::endl;
			livingEnemiesPointers[i]->checkCharacterIntro(player);
		}*/

		//only play a round if exitFight = false (there are living enemies and the player is alive)
		if (exitFight == false)
		{
			
			//set this condition to true once the player has defeated all enemies or all allies have been defeated
			bool exitCombat = false;
			//COMBAT LOOP
			do
			{

				//set this condition to true once the player commits to an option all the way through their submenus
				bool inputChosen = false;

				//Option 1 variables
				float playerMovement = 0.0f;
				shared_ptr<Weapon> weaponChoice = nullptr;;
				std::shared_ptr<Ammunition> ammoChoice = nullptr; //this will be a pointer to the ammo choice so that the quantity can be updated
				shared_ptr<Spell> spellChoice = nullptr;;
				shared_ptr<Character> targetChoice = nullptr; //this is a pointer to the target choice so that the target's health can be updated

				//Option 2 variables
				//NONE

				//Option 3 variables
				//NONE

				//Option 4 variables
				std::shared_ptr<Potion> potionChoice = nullptr; //this is a pointer to the potion choice so that the quantity can be updated
				shared_ptr<Character> potionTarget = nullptr; //this is a pointer to the target choice so that the target's health can be updated

				//ADD MORE AS MORE POTION TYPES GET IMPLEMENTED
				//Used to track the player's potions and grey out the potion option if they have none
				vector<std::shared_ptr<Potion>> fatiguePotions;
				vector<std::shared_ptr<Potion>> healingPotions;
				vector<std::shared_ptr<Potion>> Potions;

				int numPotionCategories = 0;
				for (shared_ptr<Item> item : player->inventory.backpackItems)
				{
					//TODO ADD CONSUMABLE LOGIC
				}

				bool hasPotion = false;

				//EXPAND AS MORE POTIONS GET ADDED
				if (healingPotions.size() > 0 || fatiguePotions.size() > 0)
				{
					hasPotion = true;
				}

				//Option 5 variables
				shared_ptr<ThrownConsumable> thrownConsumableChoice;
				shared_ptr<Consumable> consumableChoice;
				shared_ptr<Character> consumableTarget;
				shared_ptr<Character> thrownConsumableTarget;
				vector<shared_ptr<Consumable>> consumables;
				vector<shared_ptr<ThrownConsumable>> throwingWeapons;

				for (shared_ptr<Item> item : player->inventory.backpackItems)
				{
					//gets throwing weapons and consumables
					if (shared_ptr<ThrownConsumable> consumable = std::dynamic_pointer_cast<ThrownConsumable>(item))
					{
						throwingWeapons.push_back(consumable);
					}
					if (shared_ptr<Consumable> consumable = std::dynamic_pointer_cast<Consumable>(item))
					{
						consumables.push_back(consumable);
					}
				}

				//Option 6 variables
				//NONE

				//Option 7 variables
				//NONE

				//Option 8 variables
				//NONE

				//Option 9 variables
				//NONE

				//Option 10 variables
				//NONE

				std::cout << "\n=--->\n" << std::endl;
				//print out the main combat menu

				//Option 1: Attack
				if (inRange)
				{
					cout << dye::light_yellow(" 1) Attack!") << endl;
				}
				else
				{
					cout << dye::grey(" 1) Attack") << endl;
				}

				//Option 2: Swap Weapons
				if (hasStowedWeapons)
				{
					cout << dye::light_yellow(" 2) Swap to Your Stored weapons") << endl;
				}
				else
				{
					cout << dye::grey(" 2) Swap to Your Stored weapons") << endl;
				}

				//Option 3: View Spells
				if (player->attunedSpells.size() > 0)
				{
					cout << dye::light_yellow(" 3) View Spells") << endl;
				}
				else
				{
					cout << dye::grey(" 3) View Spells") << endl;
				}

				//Option 4: Use Potion
				if (healingPotions.size() > 0 || fatiguePotions.size() > 0)
				{
					cout << dye::light_yellow(" 4) Use Potion") << endl;
				}
				else
				{
					cout << dye::grey(" 4) Use Potion") << endl;
				}

				//Option 5: Use Item
				if (consumables.size() > 0 || throwingWeapons.size() > 0)
				{
					cout << dye::light_yellow(" 5) Use Item") << endl;
				}
				else
				{
					cout << dye::grey(" 5) Use Item") << endl;
				}

				//Option 6: Taunt Enemy
				if (livingEnemiesPointers.size() == 0)
				{
					cout << dye::light_yellow(" 6) Taunt Your Enemy") << endl;
				}
				else
				{
					cout << dye::light_yellow(" 6) Taunt Your Enemies") << endl;
				}

				//Option 7: Check Enemy
				if (livingEnemiesPointers.size() == 0)
				{
					cout << dye::light_yellow(" 7) Check Your Enemy") << endl;
				}
				else
				{
					cout << dye::light_yellow(" 7) Check Your Enemies") << endl;
				}

				//Option 8: Check Ally/Self
				if (livingAlliesPointers.size() == 0)
				{
					cout << dye::light_yellow(" 8) Check Self") << endl;
				}
				else if (livingAlliesPointers.size() == 1)
				{
					cout << dye::light_yellow(" 8) Check Self or Ally") << endl;
				}
				else
				{
					cout << dye::light_yellow(" 8) Check Self or Allies") << endl;
				}

				//Option 9: Check Ally/Self Equipment
				if (livingAlliesPointers.size() == 0)
				{
					cout << dye::light_yellow(" 9) Check Equipment") << endl;
				}
				else if (livingAlliesPointers.size() == 1)
				{
					cout << dye::light_yellow(" 9) Check Equipment for Self or Ally") << endl;
				}
				else
				{
					cout << dye::light_yellow(" 9) Check Equipment for Self or Allies") << endl;
				}

				//Option 10: Flee
				cout << dye::light_yellow(" 10) Flee from Combat") << endl;

				//input validation
				int initialChoice = validateInput(1, 10);

				switch (initialChoice)
				{
				case 1: // ATTACK
				{

					if (!inRange)
					{
						cout << dye::white("\n You are out of range of any enemies!") << endl;
						break;
					}
					else
					{
						float distanceTraveled = player->speed / 15;
						int numEnemiesInRange = 0;
						int numEnemiesInRangeForward = 0;
						int numEnemiesInRangeBackward = 0;
						for (int i = 0; i < livingEnemiesPointers.size(); i++)
						{
							if (livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled <= mainHand->reach
								|| livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled <= offHand->reach)
							{
								numEnemiesInRangeForward++;
							}
							if (livingEnemiesPointers[i]->position[player->getId()] + distanceTraveled * 0.8 <= mainHand->reach
								|| livingEnemiesPointers[i]->position[player->getId()] + distanceTraveled * 0.8 <= offHand->reach)
							{
								numEnemiesInRangeBackward++;
							}
							if (livingEnemiesPointers[i]->position[player->getId()] <= mainHand->reach || livingEnemiesPointers[i]->position[player->getId()] <= offHand->reach)
							{
								numEnemiesInRange++;
							}
						}
						if (numEnemiesInRangeForward > 0 || spellsInRange > 0) cout << dye::light_yellow(" 1) Advance and Attack!") << endl;
						else cout << dye::grey(" 1) Advance and Attack!") << endl;
						if (numEnemiesInRange > 0 || spellsInRange > 0) cout << dye::light_yellow(" 2) Stand Your Ground and Attack!") << endl;
						else cout << dye::grey(" 2) Stand Your Ground and Attack!") << endl;
						if (numEnemiesInRangeBackward > 0 || spellsInRange > 0) cout << dye::light_yellow(" 3) Retreat and Attack!") << endl;
						else cout << dye::grey(" 3) Retreat and Attack!") << endl;
						cout << dye::light_yellow(" 4) Move Without Attacking!") << endl;
						cout << dye::light_yellow(" 5) Go back") << endl;

						//input validation
						int attackChoice = validateInput(1, 5);

						switch (attackChoice)
						{
						case 1: // ADVANCE AND ATTACK
						{
							float advanceMovement = 0 - player->speed / 20;

							if (numEnemiesInRangeBackward > 0)
							{
								//get enemies in range of a spell if they move forward and attack and check if player has fatiuge to cast spell
								spellsInRange = 0;
								for (shared_ptr<Spell> spells : player->attunedSpells)
								{
									if (spells->range >= minDistanceFromPlayer - distanceTraveled && spells->fatigueCost <= player->fatiguePoints)
									{
										spellsInRange++;
									}
								}
								for (int i = 0; i < livingEnemiesPointers.size(); i++)
								{
									//in range of both weapons and at least one spell
									if (livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled <= mainHand->reach &&
										livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled <= offHand->reach &&
										spellsInRange > 0)
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << mainHand->name
											<< ", and " << offHand->name << ", and attuned spell(s)" << endl;
									}
									//in range of both weapons and no spells
									else if (livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled <= mainHand->reach &&
										livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled <= offHand->reach &&
										spellsInRange == 0)
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << mainHand->name
											<< ", and " << offHand->name << endl;
									}
									//in range of mainhand and at least one spell
									else if (livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled <= mainHand->reach &&
										spellsInRange > 0 && livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled > offHand->reach)
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << mainHand->name
											<< ", and attuned spell(s)" << endl;
									}
									//in range of mainhand and no spells
									else if (livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled <= mainHand->reach &&
										spellsInRange == 0 && livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled > offHand->reach)
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << mainHand->name << endl;
									}
									//in range of offhand and at least one spell
									else if (livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled <= offHand->reach &&
										spellsInRange > 0 && livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled > mainHand->reach)
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << offHand->name
											<< ", and attuned spell(s)" << endl;
									}
									//in range of offhand and no spells
									else if (livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled <= offHand->reach &&
										spellsInRange == 0 && livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled > mainHand->reach)
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << offHand->name << endl;
									}
									//in range of at least one spell
									else if (spellsInRange > 0 && livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled > offHand->reach
										&& livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled > mainHand->reach)
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of attuned spell(s)" << endl;
									}
									else
									{
										cout << dye::grey(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << endl;
									}
								}
								int advanceChoice = 0;
								advanceChoice = validateInput(1, livingEnemiesPointers.size());

								//check if the player is in range of the enemy they selected
								if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] - distanceTraveled > mainHand->reach
									&& livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] - distanceTraveled > offHand->reach
									&& spellsInRange == 0)
								{
									//They're not in range of choice, go back
									cout << "You are not in range of that enemy!" << endl;
									break;
								}
								else // they're in range and chose a target, ask which weapon to hit them with
								{
									//if they have two weapons to attack with, ask which one they want to use
									if (mainHand->hasBeenInitialized && offHand->hasBeenInitialized)
									{
										cout << "Which weapon would you like to attack with?" << endl;
										cout << dye::light_yellow(" 1) " + mainHand->name) << endl;
										cout << dye::light_yellow(" 2) " + offHand->name) << endl;
										cout << dye::light_yellow(" 3) Go back") << endl;
										int mainOrOffChoice = validateInput(1, 3);
										switch (mainOrOffChoice)
										{
										case 1: // MAINHAND
										{
											//CAST SPELL
											std::cout << "\n=--->\n" << std::endl;
											if (mainHand->weaponType == Weapon::WeaponType::TALISMAN || mainHand->weaponType == Weapon::WeaponType::CHIME ||
												mainHand->weaponType == Weapon::WeaponType::TOME || mainHand->weaponType == Weapon::WeaponType::ORB ||
												mainHand->weaponType == Weapon::WeaponType::STAFF || mainHand->weaponType == Weapon::WeaponType::WAND)
											{
												//check if player has enough fatigue to cast any spells
												int spellsPlayerCanCast = 0;
												for (shared_ptr<Spell> spell : player->attunedSpells)
												{
													if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
												}

												if (spellsPlayerCanCast == 0)
												{
													cout << "You don't have enough fatigue to cast any spells!" << endl;
													break;
												}

												////print all enemies
												//cout << " Which target do you pick?" << endl;
												//for (int i = 0; i < livingEnemiesPointers.size(); i++)
												//{
												//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												//}
												////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
												//if (spellAttackChoice > livingEnemiesPointers.size()) break;

												//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
												// choose to cast a spell
												bool spellAttackCommitted = player->chooseSpell(*mainHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
												if (spellAttackCommitted)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];
													weaponChoice = mainHand;
													playerMovement = advanceMovement;
													inputChosen = true;
													break;
												}
												break;
											}
											//PROJECTILE WEAPON
											else if (mainHand->weaponType == Weapon::WeaponType::LONGBOW || mainHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
												mainHand->weaponType == Weapon::WeaponType::GREATBOW || mainHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
												mainHand->weaponType == Weapon::WeaponType::CROSSBOW || mainHand->weaponType == Weapon::WeaponType::BALLISTA)
											{
												//print all enemies
												/*cout << " Which target do you pick?" << endl;
												for (int i = 0; i < livingEnemiesPointers.size(); i++)
												{
													cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												}
												cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);*/

												bool projectileAttackCommitted = player->chooseAmmunition(mainHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
												if (projectileAttackCommitted)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1];
													weaponChoice = mainHand;
													playerMovement = advanceMovement;
													inputChosen = true;
													break;
												}
												else
												{
													break;
												}
											}
											else
											{
												if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] - distanceTraveled <= mainHand->reach)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1];
													weaponChoice = mainHand;
													playerMovement = advanceMovement;
													inputChosen = true;
													break;
												}
												else
												{
													cout << "You are not in range of that enemy!" << endl;
													break;
												}
											}

										}
										case 2: // OFFHAND
										{
											//CAST SPELL
											std::cout << "\n=--->\n" << std::endl;
											if (offHand->weaponType == Weapon::WeaponType::TALISMAN || offHand->weaponType == Weapon::WeaponType::CHIME ||
												offHand->weaponType == Weapon::WeaponType::TOME || offHand->weaponType == Weapon::WeaponType::ORB ||
												offHand->weaponType == Weapon::WeaponType::STAFF || offHand->weaponType == Weapon::WeaponType::WAND)
											{
												//check if player has enough fatigue to cast any spells
												int spellsPlayerCanCast = 0;
												for (shared_ptr<Spell> spell : player->attunedSpells)
												{
													if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
												}

												if (spellsPlayerCanCast == 0)
												{
													cout << "You don't have enough fatigue to cast any spells!" << endl;
													break;
												}

												////print all enemies
												//cout << " Which target do you pick?" << endl;
												//for (int i = 0; i < livingEnemiesPointers.size(); i++)
												//{
												//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												//}
												////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
												//if (spellAttackChoice > livingEnemiesPointers.size()) break;

												//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
												// choose to cast a spell
												bool spellAttackCommitted = player->chooseSpell(*offHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
												if (spellAttackCommitted)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

													weaponChoice = offHand;
													playerMovement = advanceMovement;
													inputChosen = true;
													break;
												}
											}
											//PROJECTILE WEAPON
											else if (offHand->weaponType == Weapon::WeaponType::LONGBOW || offHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
												offHand->weaponType == Weapon::WeaponType::GREATBOW || offHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
												offHand->weaponType == Weapon::WeaponType::CROSSBOW || offHand->weaponType == Weapon::WeaponType::BALLISTA)
											{
												//print all enemies
												/*cout << " Which target do you pick?" << endl;
												for (int i = 0; i < livingEnemiesPointers.size(); i++)
												{
													cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												}
												cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);*/

												bool projectileAttackCommitted = player->chooseAmmunition(offHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
												if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
												weaponChoice = offHand;
												playerMovement = advanceMovement;
												inputChosen = true;
												break;
											}
											else
											{
												if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] - distanceTraveled <= mainHand->reach)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1];
													weaponChoice = offHand;
													playerMovement = advanceMovement;
													inputChosen = true;
													break;
												}
												else
												{
													cout << "You are not in range of that enemy!" << endl;
													break;
												}
											}
										}
										case 3: // GO BACK
										{
											break;
										}
										default:
										{
											cout << dye::white("\n  Enter a number between 1 - 3") << endl;
											break;
										}
										}
									}
									//if only mainhand is available
									else if (mainHand->hasBeenInitialized && !offHand->hasBeenInitialized)
									{
										//CAST SPELL
										std::cout << "\n=--->\n" << std::endl;
										if (mainHand->weaponType == Weapon::WeaponType::TALISMAN || mainHand->weaponType == Weapon::WeaponType::CHIME ||
											mainHand->weaponType == Weapon::WeaponType::TOME || mainHand->weaponType == Weapon::WeaponType::ORB ||
											mainHand->weaponType == Weapon::WeaponType::STAFF || mainHand->weaponType == Weapon::WeaponType::WAND)
										{
											//check if player has enough fatigue to cast any spells
											int spellsPlayerCanCast = 0;
											for (shared_ptr<Spell> spell : player->attunedSpells)
											{
												if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
											}

											if (spellsPlayerCanCast == 0)
											{
												cout << "You don't have enough fatigue to cast any spells!" << endl;
												break;
											}

											////print all enemies
											//cout << " Which target do you pick?" << endl;
											//for (int i = 0; i < livingEnemiesPointers.size(); i++)
											//{
											//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											//}
											////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
											//if (spellAttackChoice > livingEnemiesPointers.size()) break;

											//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
											// choose to cast a spell
											bool spellAttackCommitted = player->chooseSpell(*mainHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
											if (spellAttackCommitted)
											{
												targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

												weaponChoice = mainHand;
												playerMovement = advanceMovement;
												inputChosen = true;
												break;
											}
										}
										//PROJECTILE WEAPON
										else if (mainHand->weaponType == Weapon::WeaponType::LONGBOW || mainHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
											mainHand->weaponType == Weapon::WeaponType::GREATBOW || mainHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
											mainHand->weaponType == Weapon::WeaponType::CROSSBOW || mainHand->weaponType == Weapon::WeaponType::BALLISTA)
										{
											//print all enemies
											/*cout << " Which target do you pick?" << endl;
											for (int i = 0; i < livingEnemiesPointers.size(); i++)
											{
												cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											}
											cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);*/

											bool projectileAttackCommitted = player->chooseAmmunition(mainHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
											if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
											weaponChoice = mainHand;
											playerMovement = advanceMovement;
											inputChosen = true;
											break;
										}
										else
										{
											if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] - distanceTraveled <= mainHand->reach)
											{
												targetChoice = livingEnemiesPointers[advanceChoice - 1];
												weaponChoice = mainHand;
												playerMovement = advanceMovement;
												inputChosen = true;
												break;
											}
											else
											{
												cout << "You are not in range of that enemy!" << endl;
												break;
											}
										}
									}
									//if only offhand is available
									else if (offHand->hasBeenInitialized && !mainHand->hasBeenInitialized)
									{
										//CAST SPELL
										std::cout << "\n=--->\n" << std::endl;
										if (offHand->weaponType == Weapon::WeaponType::TALISMAN || offHand->weaponType == Weapon::WeaponType::CHIME ||
											offHand->weaponType == Weapon::WeaponType::TOME || offHand->weaponType == Weapon::WeaponType::ORB ||
											offHand->weaponType == Weapon::WeaponType::STAFF || offHand->weaponType == Weapon::WeaponType::WAND)
										{
											//check if player has enough fatigue to cast any spells
											int spellsPlayerCanCast = 0;
											for (shared_ptr<Spell> spell : player->attunedSpells)
											{
												if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
											}

											if (spellsPlayerCanCast == 0)
											{
												cout << "You don't have enough fatigue to cast any spells!" << endl;
												break;
											}

											////print all enemies
											//cout << " Which target do you pick?" << endl;
											//for (int i = 0; i < livingEnemiesPointers.size(); i++)
											//{
											//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											//}
											////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
											//if (spellAttackChoice > livingEnemiesPointers.size()) break;

											//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
											// choose to cast a spell
											bool spellAttackCommitted = player->chooseSpell(*offHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
											if (spellAttackCommitted)
											{
												targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

												weaponChoice = offHand;
												playerMovement = advanceMovement;
												inputChosen = true;
												break;
											}
										}
										//PROJECTILE WEAPON
										else if (offHand->weaponType == Weapon::WeaponType::LONGBOW || offHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
											offHand->weaponType == Weapon::WeaponType::GREATBOW || offHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
											offHand->weaponType == Weapon::WeaponType::CROSSBOW || offHand->weaponType == Weapon::WeaponType::BALLISTA)
										{
											////print all enemies
											//cout << " Which target do you pick?" << endl;
											//for (int i = 0; i < livingEnemiesPointers.size(); i++)
											//{
											//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											//}
											//cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											//int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);

											bool projectileAttackCommitted = player->chooseAmmunition(offHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
											if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
											weaponChoice = offHand;
											playerMovement = advanceMovement;
											inputChosen = true;
											break;
										}
										else
										{
											//print all enemies
											cout << " Which target do you pick?" << endl;
											for (int i = 0; i < livingEnemiesPointers.size(); i++)
											{
												cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											}
											int meleeAttackChoice = validateInput(1, livingEnemiesPointers.size());
											if (livingEnemiesPointers[meleeAttackChoice - 1]->position[player->getId()] - distanceTraveled <= offHand->reach)
											{
												targetChoice = livingEnemiesPointers[meleeAttackChoice - 1];
												inputChosen = true;
												playerMovement = advanceMovement;
												weaponChoice = offHand;
												break;
											}
											else
											{
												cout << "You are not in range of that enemy!" << endl;
												break;
											}
											break;
										}
									}
									else
									{
										cout << "ERROR: No weapons initialized!" << endl;
										break;
									}
									break;
								}
							}
							else
							{
								cout << "No enemies are in range of your retreating attack..." << endl;
								break;
							}
						}
						case 2: // STAND YOUR GROUND AND ATTACK
						{
							float standMovement = 0;
							if (numEnemiesInRangeBackward > 0)
							{
								for (int i = 0; i < livingEnemiesPointers.size(); i++)
								{
									if (livingEnemiesPointers[i]->position[player->getId()] <= mainHand->reach &&
										livingEnemiesPointers[i]->position[player->getId()] <= offHand->reach)
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << mainHand->name
											<< " and " << offHand->name << endl;
									}
									else if (livingEnemiesPointers[i]->position[player->getId()] <= offHand->reach)
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << offHand->name << endl;
									}
									else if (livingEnemiesPointers[i]->position[player->getId()] <= mainHand->reach)
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << mainHand->name << endl;
									}
									else
									{
										cout << dye::grey(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << endl;
									}
								}
								int advanceChoice = 0;
								advanceChoice = validateInput(1, livingEnemiesPointers.size());

								//check if the player is in range of the enemy they selected
								if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] > mainHand->reach
									&& livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] > offHand->reach)
								{
									//They're not in range of choice, go back
									cout << "You are not in range of that enemy!" << endl;
									break;
								}
								else // they're in range and chose a target, ask which weapon to hit them with
								{
									//if they have two weapons to attack with, ask which one they want to use
									if (mainHand->hasBeenInitialized && offHand->hasBeenInitialized)
									{
										cout << "Which weapon would you like to attack with?" << endl;
										cout << dye::light_yellow(" 1) " + mainHand->name) << endl;
										cout << dye::light_yellow(" 2) " + offHand->name) << endl;
										cout << dye::light_yellow(" 3) Go back") << endl;
										int mainOrOffChoice = validateInput(1, 3);
										switch (mainOrOffChoice)
										{
										case 1: // MAINHAND
										{
											//CAST SPELL
											std::cout << "\n=--->\n" << std::endl;
											if (mainHand->weaponType == Weapon::WeaponType::TALISMAN || mainHand->weaponType == Weapon::WeaponType::CHIME ||
												mainHand->weaponType == Weapon::WeaponType::TOME || mainHand->weaponType == Weapon::WeaponType::ORB ||
												mainHand->weaponType == Weapon::WeaponType::STAFF || mainHand->weaponType == Weapon::WeaponType::WAND)
											{
												//check if player has enough fatigue to cast any spells
												int spellsPlayerCanCast = 0;
												for (shared_ptr<Spell> spell : player->attunedSpells)
												{
													if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
												}

												if (spellsPlayerCanCast == 0)
												{
													cout << "You don't have enough fatigue to cast any spells!" << endl;
													break;
												}

												////print all enemies
												//cout << " Which target do you pick?" << endl;
												//for (int i = 0; i < livingEnemiesPointers.size(); i++)
												//{
												//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												//}
												////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
												//if (spellAttackChoice > livingEnemiesPointers.size()) break;

												//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
												// choose to cast a spell
												bool spellAttackCommitted = player->chooseSpell(*mainHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
												if (spellAttackCommitted)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

													weaponChoice = mainHand;
													playerMovement = standMovement;
													inputChosen = true;
													break;
												}
											}
											//PROJECTILE WEAPON
											else if (mainHand->weaponType == Weapon::WeaponType::LONGBOW || mainHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
												mainHand->weaponType == Weapon::WeaponType::GREATBOW || mainHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
												mainHand->weaponType == Weapon::WeaponType::CROSSBOW || mainHand->weaponType == Weapon::WeaponType::BALLISTA)
											{
												////print all enemies
												//cout << " Which target do you pick?" << endl;
												//for (int i = 0; i < livingEnemiesPointers.size(); i++)
												//{
												//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												//}
												//cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												//int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);

												bool projectileAttackCommitted = player->chooseAmmunition(mainHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
												if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
												playerMovement = standMovement;
												weaponChoice = mainHand;
												inputChosen = true;
												break;
											}
											else
											{
												if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] <= mainHand->reach)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1];
													weaponChoice = mainHand;
													playerMovement = standMovement;
													inputChosen = true;
													break;
												}
												else
												{
													cout << "HERE" << endl;
													cout << "You are not in range of that enemy!" << endl;
													break;
												}
											}

										}
										case 2: // OFFHAND
										{
											//CAST SPELL
											std::cout << "\n=--->\n" << std::endl;
											if (offHand->weaponType == Weapon::WeaponType::TALISMAN || offHand->weaponType == Weapon::WeaponType::CHIME ||
												offHand->weaponType == Weapon::WeaponType::TOME || offHand->weaponType == Weapon::WeaponType::ORB ||
												offHand->weaponType == Weapon::WeaponType::STAFF || offHand->weaponType == Weapon::WeaponType::WAND)
											{
												//check if player has enough fatigue to cast any spells
												int spellsPlayerCanCast = 0;
												for (shared_ptr<Spell> spell : player->attunedSpells)
												{
													if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
												}

												if (spellsPlayerCanCast == 0)
												{
													cout << "You don't have enough fatigue to cast any spells!" << endl;
													break;
												}

												////print all enemies
												//cout << " Which target do you pick?" << endl;
												//for (int i = 0; i < livingEnemiesPointers.size(); i++)
												//{
												//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												//}
												////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
												//if (spellAttackChoice > livingEnemiesPointers.size()) break;

												//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
												// choose to cast a spell
												bool spellAttackCommitted = player->chooseSpell(*offHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
												if (spellAttackCommitted)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

													weaponChoice = offHand;
													playerMovement = standMovement;
													inputChosen = true;
													break;
												}
											}
											//PROJECTILE WEAPON
											else if (offHand->weaponType == Weapon::WeaponType::LONGBOW || offHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
												offHand->weaponType == Weapon::WeaponType::GREATBOW || offHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
												offHand->weaponType == Weapon::WeaponType::CROSSBOW || offHand->weaponType == Weapon::WeaponType::BALLISTA)
											{
												//print all enemies
												/*cout << " Which target do you pick?" << endl;
												for (int i = 0; i < livingEnemiesPointers.size(); i++)
												{
													cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												}
												cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);*/

												bool projectileAttackCommitted = player->chooseAmmunition(offHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
												if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
												weaponChoice = offHand;
												playerMovement = standMovement;
												inputChosen = true;
												break;
											}
											else
											{
												if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] <= offHand->reach)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1];
													weaponChoice = offHand;
													playerMovement = standMovement;
													inputChosen = true;
													break;
												}
												else
												{
													cout << "You are not in range of that enemy!" << endl;
													break;
												}
											}
										}
										case 3: // GO BACK
										{
											break;
										}
										default:
										{
											cout << dye::white("\n  Enter a number between 1 - 3") << endl;
											break;
										}
										}
									}
									//if only mainhand is available
									else if (mainHand->hasBeenInitialized && !offHand->hasBeenInitialized)
									{
										//CAST SPELL
										std::cout << "\n=--->\n" << std::endl;
										if (mainHand->weaponType == Weapon::WeaponType::TALISMAN || mainHand->weaponType == Weapon::WeaponType::CHIME ||
											mainHand->weaponType == Weapon::WeaponType::TOME || mainHand->weaponType == Weapon::WeaponType::ORB ||
											mainHand->weaponType == Weapon::WeaponType::STAFF || mainHand->weaponType == Weapon::WeaponType::WAND)
										{
											//check if player has enough fatigue to cast any spells
											int spellsPlayerCanCast = 0;
											for (shared_ptr<Spell> spell : player->attunedSpells)
											{
												if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
											}

											if (spellsPlayerCanCast == 0)
											{
												cout << "You don't have enough fatigue to cast any spells!" << endl;
												break;
											}

											////print all enemies
											//cout << " Which target do you pick?" << endl;
											//for (int i = 0; i < livingEnemiesPointers.size(); i++)
											//{
											//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											//}
											////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
											//if (spellAttackChoice > livingEnemiesPointers.size()) break;

											//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
											// choose to cast a spell
											bool spellAttackCommitted = player->chooseSpell(*mainHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
											if (spellAttackCommitted)
											{
												targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

												weaponChoice = mainHand;
												playerMovement = standMovement;
												inputChosen = true;
												break;
											}
										}
										//PROJECTILE WEAPON
										else if (mainHand->weaponType == Weapon::WeaponType::LONGBOW || mainHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
											mainHand->weaponType == Weapon::WeaponType::GREATBOW || mainHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
											mainHand->weaponType == Weapon::WeaponType::CROSSBOW || mainHand->weaponType == Weapon::WeaponType::BALLISTA)
										{
											//print all enemies
											/*cout << " Which target do you pick?" << endl;
											for (int i = 0; i < livingEnemiesPointers.size(); i++)
											{
												cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											}
											cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);*/

											bool projectileAttackCommitted = player->chooseAmmunition(mainHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
											if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
											weaponChoice = mainHand;
											playerMovement = standMovement;
											inputChosen = true;
											break;
										}
										else
										{
											if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] <= mainHand->reach)
											{
												targetChoice = livingEnemiesPointers[advanceChoice - 1];
												weaponChoice = mainHand;
												playerMovement = standMovement;
												inputChosen = true;
												break;
											}
											else
											{
												cout << "You are not in range of that enemy!" << endl;
												break;
											}
										}
									}
									//if only offhand is available
									else if (offHand->hasBeenInitialized && !mainHand->hasBeenInitialized)
									{
										//CAST SPELL
										std::cout << "\n=--->\n" << std::endl;
										if (offHand->weaponType == Weapon::WeaponType::TALISMAN || offHand->weaponType == Weapon::WeaponType::CHIME ||
											offHand->weaponType == Weapon::WeaponType::TOME || offHand->weaponType == Weapon::WeaponType::ORB ||
											offHand->weaponType == Weapon::WeaponType::STAFF || offHand->weaponType == Weapon::WeaponType::WAND)
										{
											//check if player has enough fatigue to cast any spells
											int spellsPlayerCanCast = 0;
											for (shared_ptr<Spell> spell : player->attunedSpells)
											{
												if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
											}

											if (spellsPlayerCanCast == 0)
											{
												cout << "You don't have enough fatigue to cast any spells!" << endl;
												break;
											}

											////print all enemies
											//cout << " Which target do you pick?" << endl;
											//for (int i = 0; i < livingEnemiesPointers.size(); i++)
											//{
											//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											//}
											////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
											//if (spellAttackChoice > livingEnemiesPointers.size()) break;

											//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
											// choose to cast a spell
											bool spellAttackCommitted = player->chooseSpell(*offHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
											if (spellAttackCommitted)
											{
												targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

												weaponChoice = offHand;
												playerMovement = standMovement;
												inputChosen = true;
												break;
											}
										}
										//PROJECTILE WEAPON
										else if (offHand->weaponType == Weapon::WeaponType::LONGBOW || offHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
											offHand->weaponType == Weapon::WeaponType::GREATBOW || offHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
											offHand->weaponType == Weapon::WeaponType::CROSSBOW || offHand->weaponType == Weapon::WeaponType::BALLISTA)
										{
											//print all enemies
											/*cout << " Which target do you pick?" << endl;
											for (int i = 0; i < livingEnemiesPointers.size(); i++)
											{
												cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											}
											cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);*/

											bool projectileAttackCommitted = player->chooseAmmunition(offHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
											if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
											weaponChoice = offHand;
											playerMovement = standMovement;
											inputChosen = true;
											break;
										}
										else
										{
											//print all enemies
											cout << " Which target do you pick?" << endl;
											for (int i = 0; i < livingEnemiesPointers.size(); i++)
											{
												cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											}
											int meleeAttackChoice = validateInput(1, livingEnemiesPointers.size());
											if (livingEnemiesPointers[meleeAttackChoice - 1]->position[player->getId()] <= offHand->reach)
											{
												targetChoice = livingEnemiesPointers[meleeAttackChoice - 1];
												weaponChoice = mainHand;
												playerMovement = standMovement;
												inputChosen = true;
												break;
											}
											else
											{
												cout << "You are not in range of that enemy!" << endl;
												break;
											}
											break;
										}
									}
									else
									{
										cout << "ERROR: No weapons initialized!" << endl;
										break;
									}
									break;
								}
							}
							else
							{
								cout << "No enemies are in range of your retreating attack..." << endl;
								break;
							}
						}
						case 3: // RETREAT AND ATTACK
						{
							float retreatMovement = player->speed / 20;
							if (numEnemiesInRangeBackward > 0)
							{
								for (int i = 0; i < livingEnemiesPointers.size(); i++)
								{
									if (livingEnemiesPointers[i]->position[player->getId()] + distanceTraveled <= mainHand->reach &&
										livingEnemiesPointers[i]->position[player->getId()] + distanceTraveled <= offHand->reach)
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << mainHand->name
											<< " and " << offHand->name << endl;
									}
									else if (livingEnemiesPointers[i]->position[player->getId()] + distanceTraveled <= offHand->reach)
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << offHand->name << endl;
									}
									else if (livingEnemiesPointers[i]->position[player->getId()] + distanceTraveled <= mainHand->reach)
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << mainHand->name << endl;
									}
									else
									{
										cout << dye::grey(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << endl;
									}
								}
								int advanceChoice = 0;
								advanceChoice = validateInput(1, livingEnemiesPointers.size());

								//check if the player is in range of the enemy they selected
								if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] + distanceTraveled > mainHand->reach
									&& livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] + distanceTraveled > offHand->reach)
								{
									//They're not in range of choice, go back
									cout << "You are not in range of that enemy!" << endl;
									break;
								}
								else // they're in range and chose a target, ask which weapon to hit them with
								{
									//if they have two weapons to attack with, ask which one they want to use
									if (mainHand->hasBeenInitialized && offHand->hasBeenInitialized)
									{
										cout << "Which weapon would you like to attack with?" << endl;
										cout << dye::light_yellow(" 1) " + mainHand->name) << endl;
										cout << dye::light_yellow(" 2) " + offHand->name) << endl;
										cout << dye::light_yellow(" 3) Go back") << endl;
										int mainOrOffChoice = validateInput(1, 3);
										switch (mainOrOffChoice)
										{
										case 1: // MAINHAND
										{
											//CAST SPELL
											std::cout << "\n=--->\n" << std::endl;
											if (mainHand->weaponType == Weapon::WeaponType::TALISMAN || mainHand->weaponType == Weapon::WeaponType::CHIME ||
												mainHand->weaponType == Weapon::WeaponType::TOME || mainHand->weaponType == Weapon::WeaponType::ORB ||
												mainHand->weaponType == Weapon::WeaponType::STAFF || mainHand->weaponType == Weapon::WeaponType::WAND)
											{
												//check if player has enough fatigue to cast any spells
												int spellsPlayerCanCast = 0;
												for (shared_ptr<Spell> spell : player->attunedSpells)
												{
													if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
												}

												if (spellsPlayerCanCast == 0)
												{
													cout << "You don't have enough fatigue to cast any spells!" << endl;
													break;
												}

												////print all enemies
												//cout << " Which target do you pick?" << endl;
												//for (int i = 0; i < livingEnemiesPointers.size(); i++)
												//{
												//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												//}
												////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
												//if (spellAttackChoice > livingEnemiesPointers.size()) break;

												//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
												// choose to cast a spell
												bool spellAttackCommitted = player->chooseSpell(*mainHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
												if (spellAttackCommitted)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

													weaponChoice = mainHand;
													playerMovement = retreatMovement;
													inputChosen = true;
													break;
												}
											}
											//PROJECTILE WEAPON
											else if (mainHand->weaponType == Weapon::WeaponType::LONGBOW || mainHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
												mainHand->weaponType == Weapon::WeaponType::GREATBOW || mainHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
												mainHand->weaponType == Weapon::WeaponType::CROSSBOW || mainHand->weaponType == Weapon::WeaponType::BALLISTA)
											{
												////print all enemies
												//cout << " Which target do you pick?" << endl;
												//for (int i = 0; i < livingEnemiesPointers.size(); i++)
												//{
												//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												//}
												//cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												//int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);

												bool projectileAttackCommitted = player->chooseAmmunition(mainHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
												if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
												weaponChoice = mainHand;
												playerMovement = retreatMovement;
												inputChosen = true;
												break;
											}
											else
											{
												if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] + distanceTraveled <= mainHand->reach)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1];
													inputChosen = true;
													playerMovement = retreatMovement;
													break;
												}
												else
												{
													cout << "You are not in range of that enemy!" << endl;
													break;
												}
											}

										}
										case 2: // OFFHAND
										{
											//CAST SPELL
											std::cout << "\n=--->\n" << std::endl;
											if (offHand->weaponType == Weapon::WeaponType::TALISMAN || offHand->weaponType == Weapon::WeaponType::CHIME ||
												offHand->weaponType == Weapon::WeaponType::TOME || offHand->weaponType == Weapon::WeaponType::ORB ||
												offHand->weaponType == Weapon::WeaponType::STAFF || offHand->weaponType == Weapon::WeaponType::WAND)
											{
												//check if player has enough fatigue to cast any spells
												int spellsPlayerCanCast = 0;
												for (shared_ptr<Spell> spell : player->attunedSpells)
												{
													if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
												}

												if (spellsPlayerCanCast == 0)
												{
													cout << "You don't have enough fatigue to cast any spells!" << endl;
													break;
												}

												////print all enemies
												//cout << " Which target do you pick?" << endl;
												//for (int i = 0; i < livingEnemiesPointers.size(); i++)
												//{
												//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												//}
												////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
												//if (spellAttackChoice > livingEnemiesPointers.size()) break;

												//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
												// choose to cast a spell
												bool spellAttackCommitted = player->chooseSpell(*offHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
												if (spellAttackCommitted)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

													weaponChoice = offHand;
													playerMovement = retreatMovement;
													inputChosen = true;
													break;
												}
											}
											//PROJECTILE WEAPON
											else if (offHand->weaponType == Weapon::WeaponType::LONGBOW || offHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
												offHand->weaponType == Weapon::WeaponType::GREATBOW || offHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
												offHand->weaponType == Weapon::WeaponType::CROSSBOW || offHand->weaponType == Weapon::WeaponType::BALLISTA)
											{
												////print all enemies
												//cout << " Which target do you pick?" << endl;
												//for (int i = 0; i < livingEnemiesPointers.size(); i++)
												//{
												//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												//}
												//cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												//int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);

												bool projectileAttackCommitted = player->chooseAmmunition(offHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
												if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
												weaponChoice = offHand;
												playerMovement = retreatMovement;
												inputChosen = true;
												break;
											}
											else
											{
												if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] + distanceTraveled <= offHand->reach)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1];
													weaponChoice = offHand;
													playerMovement = retreatMovement;
													inputChosen = true;
													break;
												}
												else
												{
													cout << "You are not in range of that enemy!" << endl;
													break;
												}
											}
										}
										case 3: // GO BACK
										{
											break;
										}
										default:
										{
											cout << dye::white("\n  Enter a number between 1 - 3") << endl;
											break;
										}
										}
									}
									//if only mainhand is available
									else if (mainHand->hasBeenInitialized && !offHand->hasBeenInitialized)
									{
										//CAST SPELL
										std::cout << "\n=--->\n" << std::endl;
										if (mainHand->weaponType == Weapon::WeaponType::TALISMAN || mainHand->weaponType == Weapon::WeaponType::CHIME ||
											mainHand->weaponType == Weapon::WeaponType::TOME || mainHand->weaponType == Weapon::WeaponType::ORB ||
											mainHand->weaponType == Weapon::WeaponType::STAFF || mainHand->weaponType == Weapon::WeaponType::WAND)
										{
											//check if player has enough fatigue to cast any spells
											int spellsPlayerCanCast = 0;
											for (shared_ptr<Spell> spell : player->attunedSpells)
											{
												if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
											}

											if (spellsPlayerCanCast == 0)
											{
												cout << "You don't have enough fatigue to cast any spells!" << endl;
												break;
											}

											////print all enemies
											//cout << " Which target do you pick?" << endl;
											//for (int i = 0; i < livingEnemiesPointers.size(); i++)
											//{
											//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											//}
											////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
											//if (spellAttackChoice > livingEnemiesPointers.size()) break;

											//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
											// choose to cast a spell
											bool spellAttackCommitted = player->chooseSpell(*mainHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
											if (spellAttackCommitted)
											{
												targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

												weaponChoice = mainHand;
												playerMovement = retreatMovement;
												inputChosen = true;
											}
										}
										//PROJECTILE WEAPON
										else if (mainHand->weaponType == Weapon::WeaponType::LONGBOW || mainHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
											mainHand->weaponType == Weapon::WeaponType::GREATBOW || mainHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
											mainHand->weaponType == Weapon::WeaponType::CROSSBOW || mainHand->weaponType == Weapon::WeaponType::BALLISTA)
										{
											//print all enemies
											/*cout << " Which target do you pick?" << endl;
											for (int i = 0; i < livingEnemiesPointers.size(); i++)
											{
												cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											}
											cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);*/

											bool projectileAttackCommitted = player->chooseAmmunition(mainHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
											if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
											weaponChoice = mainHand;
											playerMovement = retreatMovement;
											inputChosen = true;
											break;
										}
										else
										{
											if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] + distanceTraveled <= mainHand->reach)
											{
												targetChoice = livingEnemiesPointers[advanceChoice - 1];
												weaponChoice = mainHand;
												playerMovement = retreatMovement;
												inputChosen = true;
												break;
											}
											else
											{
												cout << "You are not in range of that enemy!" << endl;
												break;
											}
										}
									}
									//if only offhand is available
									else if (offHand->hasBeenInitialized && !mainHand->hasBeenInitialized)
									{
										//CAST SPELL
										std::cout << "\n=--->\n" << std::endl;
										if (offHand->weaponType == Weapon::WeaponType::TALISMAN || offHand->weaponType == Weapon::WeaponType::CHIME ||
											offHand->weaponType == Weapon::WeaponType::TOME || offHand->weaponType == Weapon::WeaponType::ORB ||
											offHand->weaponType == Weapon::WeaponType::STAFF || offHand->weaponType == Weapon::WeaponType::WAND)
										{
											//check if player has enough fatigue to cast any spells
											int spellsPlayerCanCast = 0;
											for (shared_ptr<Spell> spell : player->attunedSpells)
											{
												if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
											}

											if (spellsPlayerCanCast == 0)
											{
												cout << "You don't have enough fatigue to cast any spells!" << endl;
												break;
											}

											////print all enemies
											//cout << " Which target do you pick?" << endl;
											//for (int i = 0; i < livingEnemiesPointers.size(); i++)
											//{
											//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											//}
											////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
											//if (spellAttackChoice > livingEnemiesPointers.size()) break;

											//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
											// choose to cast a spell
											bool spellAttackCommitted = player->chooseSpell(*offHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
											if (spellAttackCommitted)
											{
												targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

												weaponChoice = offHand;
												playerMovement = retreatMovement;
												inputChosen = true;
											}
										}
										//PROJECTILE WEAPON
										else if (offHand->weaponType == Weapon::WeaponType::LONGBOW || offHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
											offHand->weaponType == Weapon::WeaponType::GREATBOW || offHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
											offHand->weaponType == Weapon::WeaponType::CROSSBOW || offHand->weaponType == Weapon::WeaponType::BALLISTA)
										{
											////print all enemies
											//cout << " Which target do you pick?" << endl;
											//for (int i = 0; i < livingEnemiesPointers.size(); i++)
											//{
											//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											//}
											////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											//int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);

											bool projectileAttackCommitted = player->chooseAmmunition(offHand, livingEnemiesPointers[advanceChoice], ammoChoice);
											if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
											weaponChoice = offHand;
											playerMovement = retreatMovement;
											inputChosen = true;
											break;
										}
										else
										{
											//print all enemies
											cout << " Which target do you pick?" << endl;
											for (int i = 0; i < livingEnemiesPointers.size(); i++)
											{
												cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											}
											int meleeAttackChoice = validateInput(1, livingEnemiesPointers.size());
											if (livingEnemiesPointers[meleeAttackChoice - 1]->position[player->getId()] + distanceTraveled <= offHand->reach)
											{
												targetChoice = livingEnemiesPointers[meleeAttackChoice - 1];
												weaponChoice = mainHand;
												playerMovement = retreatMovement;
												inputChosen = true;
												break;
											}
											else
											{
												cout << "You are not in range of that enemy!" << endl;
												break;
											}
											break;
										}
									}
									else
									{
										cout << "ERROR: No weapons initialized!" << endl;
										break;
									}
									break;
								}
							}
							else
							{
								cout << "No enemies are in range of your retreating attack..." << endl;
								break;
							}
						}
						case 4://MOVE WITHOUT ATTACKING
						{
							std::cout << "\n=--->\n" << std::endl;
							cout << dye::light_yellow(" 1) Move Forward") << endl;
							cout << dye::light_yellow(" 2) Move Backward") << endl;
							cout << dye::light_yellow(" 3) Go back") << endl;

							int moveChoice = validateInput(1, 3);
							switch (moveChoice)
							{
							case 1: //ADVANCE
							{
								float advanceMovement = 0 - player->speed / 20;
								for (int i = 0; i < livingEnemiesPointers.size(); i++)
								{
									cout << dye::light_yellow(" " + to_string(i + 1) + ") Advance on: " + livingEnemiesPointers[i]->name) << endl;
								}
								cout << dye::light_yellow(" " + to_string(livingEnemiesPointers.size() + 1) + ") ") << dye::light_yellow("Go back...") << endl;
								int advanceNoAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);
								if (advanceNoAttackChoice == livingEnemiesPointers.size() + 1) break;
								else
								{
									targetChoice = livingEnemiesPointers[advanceNoAttackChoice - 1];
									playerMovement = advanceMovement;
									inputChosen = true;
									break;
								}
								
								break;
							}
							case 2: //RETREAT
							{
								float retreatMovement = player->speed / 20;
								for (int i = 0; i < livingEnemiesPointers.size(); i++)
								{
									cout << dye::light_yellow(" " + to_string(i + 1) + ") Retreat from: " + livingEnemiesPointers[i]->name) << endl;
								}
								cout << dye::light_yellow(" " + to_string(livingEnemiesPointers.size() + 1) + ") ") << dye::light_yellow("Go back...") << endl;
								int advanceNoAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);
								if (advanceNoAttackChoice == livingEnemiesPointers.size() + 1) break;
								else
								{
									targetChoice = livingEnemiesPointers[advanceNoAttackChoice - 1];
									playerMovement = retreatMovement;
									inputChosen = true;
									break;
								}
								break;
							}
							case 3: //GO BACK
							{
								break;
							}
							default:
							{
								cout << dye::white("\n  Enter a number between 1 - 3") << endl;
								break;
							}
							}
							break;
						}
						case 5:// GO BACK
						{
							break;
						}
						default:
						{
							cout << dye::white("\n  Enter a number between 1 - 4") << endl;
							break;
						}
						}
						break;
					}
				}
				case 2: // SWAP WEAPONS
				{
					if (hasStowedWeapons)
					{
						//TODO
						std::cout << "\n=--->\n" << std::endl;
						cout << dye::light_yellow(" 1) Swap to Your Stowed Weapons") << endl;
						cout << dye::light_yellow(" 2) Go back") << endl;

						//input validation
						int swapWeaponChoice = validateInput(1, 2);

						if (swapWeaponChoice == 1)
						{
							std::cout << "\n";
							std::cout << "=--->" << std::endl;
							std::cout << "\n";
							cout << "PLACEHOLDER SWAP WEAPON  TEXT" << endl;
							break;
						}
						else
						{
							break;
						}

					}
					else //NO STOWED WEAPONS, GO BACK
					{
						std::cout << "\n=--->\n" << std::endl;
						cout << dye::white("\n You have no stowed weapons to swap to!") << endl;
						break;
					}
				}
				case 3: // VIEW SPELLS
				{
					if (player->attunedSpells.size() > 0)
					{
						std::cout << "\n=--->\n" << std::endl;
						player->viewSpells();
						break;
					}
					else //NO SPELLS, GO BACK
					{
						std::cout << "\n=--->\n" << std::endl;
						cout << dye::white("\n You have no spells to view!") << endl;
						break;
					}
				}
				case 4: // USE POTION
				{
					if (hasPotion)
					{
						std::cout << "\n=--->\n" << std::endl;
						cout << dye::light_yellow(" 1) Drink Potion") << endl;
						if (livingAlliesPointers.size() > 0)
						{
							cout << dye::light_yellow(" 2) Share with a Friend") << endl;
							cout << dye::light_yellow(" 3) Go back") << endl;
						}
						else
						{
							cout << dye::grey(" 2) Share with a Friend") << endl;
							cout << dye::light_yellow(" 3) Go back") << endl;
						}

						//input validation
						int potionChoice = validateInput(1, 3);

						switch (potionChoice)
						{
						case 1: // DRINK POTION
						{
							//TODO
							std::cout << "\n=--->\n" << std::endl;
							cout << dye::light_yellow(" DRINK POTION PLACEHOLDER TEXT") << endl;

							int potionSubChoice = validateInput(1, numPotionCategories);
							break;
						}
						case 2: // SHARE POTION
						{
							if (livingAlliesPointers.size() > 0)
							{
								//TODO
								std::cout << "\n=--->\n" << std::endl;
								cout << dye::light_yellow(" SHARE POTION PLACEHOLDER TEXT") << endl;
								int potionSubChoice = validateInput(1, numPotionCategories);
								break;
							}
							else //NO ALLIES, GO BACK
							{
								std::cout << "\n=--->\n" << std::endl;
								cout << dye::white("\n You have no allies to share a potion with!") << endl;
								break;
							}
						}
						case 3: // GO BACK
						{
							break;
						}
						}
					}
					else //NO POTIONS, GO BACK
					{
						std::cout << "\n=--->\n" << std::endl;
						cout << dye::white("\n You have no potions to use!") << endl;
						break;
					}
					break;
				case 5: // USE ITEM
				{
					if (consumables.size() > 0 || throwingWeapons.size() > 0)
					{
						std::cout << "\n=--->\n" << std::endl;
						if (consumables.size() > 0)
						{
							cout << dye::light_yellow(" 1) Use Consumable") << endl;
						}
						else
						{
							cout << dye::grey(" 1) Use Consumable") << endl;
						}
						if (throwingWeapons.size() > 0)
						{
							cout << dye::light_yellow(" 2) Use Throwing Weapon") << endl;
						}
						else
						{
							cout << dye::grey(" 2) Use Throwing Weapon") << endl;
						}
						cout << dye::light_yellow(" 3) Go back") << endl;

						//input validation
						int consumableChoice = validateInput(1, 3);

						switch (consumableChoice)
						{
						case 1: // THROWING WEAPON
						{
							if (!throwingWeapons.empty())
							{
								cout << "THROWING WEAPON GO" << endl;
								break;
							}
							else //NO THROWING WEAPONS, GO BACK
							{
								std::cout << "\n=--->\n" << std::endl;
								cout << "\n You have no throwing weapons to use!" << endl;
								break;
							}
							break;
						}
						case 2: // CONSUMABLE
						{
							if (!consumables.empty())
							{
								// TODO
								cout << "CONSUMABLE GO" << endl;
								break;
							}
							else //NO CONSUMAMBLES, GO BACK
							{
								std::cout << "\n=--->\n" << std::endl;
								cout << "\n You have no consumables to use!" << endl;
								break;
							}
							break;
						}
						case 3: // GO BACK
						{
							break;
						}
						}
					}
					else
					{
						std::cout << "\n=--->\n" << std::endl;
						cout << "\n You have no items to use!" << endl;
					}
					break;
				}
				case 6: // TAUNT ENEMY
				{
					std::cout << "\n=--->\n" << std::endl;
					cout << dye::light_yellow("1) By the Book") << endl;
					cout << dye::light_yellow("2) Make Something Up") << endl;
					cout << dye::light_yellow("3) Go back") << endl;

					//input validation
					int tauntChoice = validateInput(1, 3);
					switch (tauntChoice)
					{
					case 1: // PRESELECTED TAUNT
					{
						//TODO TAUNT FUNCTION
						cout << dye::light_yellow("PLACEHOLDER TAUNT") << endl;
						break;
					}
					case 2: // USER INPUT TAUNT
					{
						string taunt;
						std::cout << "\n=--->\n" << std::endl;
						cout << dye::light_yellow(" Give them your best shot: ");
						cin.ignore(10000, '\n');
						getline(cin, taunt);

						//TODO TAUNT FUNCTION
						break;
					}
					case 3: // GO BACK
					{
						break;
					}
					}
					break;
				}
				case 7: // CHECK ENEMY
				{
					std::cout << "\n=--->\n" << std::endl;
					for (int i = 0; i < livingEnemiesPointers.size(); i++)
					{
						string confidenceDescription = getConfidenceDescription(std::dynamic_pointer_cast<Human>(livingEnemiesPointers[i]));
						cout << dye::light_yellow(i + 1) << ") " << dye::light_yellow(livingEnemiesPointers[i]->name) << dye::light_yellow("; ") << dye::white(confidenceDescription) << endl;
					}
					cout << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") Go back") << endl;

					//input validation
					int checkEnemyChoice = validateInput(1, livingEnemiesPointers.size() + 1);

					if (checkEnemyChoice == livingEnemiesPointers.size() + 1) // GO BACK
					{
						break;
					}
					else // CHECK ENEMY
					{
						//TODO
						cout << dye::light_yellow("PLACEHOLDER CHECK ENEMY") << endl;
						break;
					}
					break;
				}
				case 8: // CHECK ALLY/SELF
				{
					std::cout << "\n=--->\n" << std::endl;
					if (!livingAlliesPointers.empty())
					{
						cout << dye::light_yellow("1") << ") " << dye::light_yellow(player->name) << " " << dye::white(player->healthPoints) << "/" << dye::white(player->maxHealthPoints) << dye::light_yellow(" HP")
							<< " " << dye::white(player->fatiguePoints) << "/" << dye::white(player->maxFatiguePoints) << dye::light_yellow(" MP") << endl;
						for (int i = 0; i < livingAlliesPointers.size(); i++)
						{
							cout << dye::light_yellow(i + 2) << ") " << dye::white(livingAlliesPointers[i]->name) << " " << dye::white(livingAlliesPointers[i]->healthPoints) << "/" << dye::light_yellow(livingAlliesPointers[i]->maxHealthPoints) << " HP"
								<< " " << dye::white(livingAlliesPointers[i]->fatiguePoints) << "/" << dye::white(livingAlliesPointers[i]->maxFatiguePoints) << dye::light_yellow(" MP") << endl;
						}
						cout << dye::light_yellow(livingAlliesPointers.size() + 1) << dye::light_yellow(") Go back") << endl;

						//input validation
						int checkAllyChoice = validateInput(1, livingAlliesPointers.size() + 1);
						if (checkAllyChoice == livingAlliesPointers.size() + 1) // GO BACK
						{
							break;
						}
						else // CHECK ALLY
						{
							//TODO
							cout << dye::light_yellow("PLACEHOLDER CHECK ALLY") << endl;
							break;
						}
					}
					else if (livingAlliesPointers.empty())
					{
						cout << dye::light_yellow("1") << ") " << dye::light_yellow(player->name) << " " << dye::white(player->healthPoints) << "/" << dye::white(player->maxHealthPoints) << dye::light_yellow(" HP")
							<< " " << dye::white(player->fatiguePoints) << "/" << dye::white(player->maxFatiguePoints) << dye::light_yellow(" MP") << endl;
						cout << dye::light_yellow("2") << dye::light_yellow(") Go back") << endl;
						//input validation
						int checkAllyChoice = validateInput(1, 2);
						if (checkAllyChoice == 2) // GO BACK
						{
							break;
						}
						else // CHECK SELF
						{
							//TODO
							cout << dye::light_yellow("PLACEHOLDER CHECK SELF") << endl;
							break;
						}
					}
					break;
				}
				case 9: // CHECK ALLY/SELF EQUIPMENT
				{
					//To be assigned to each character's equipment
					shared_ptr<Weapon> mainhand = nullptr;
					shared_ptr<Weapon> offhand = nullptr;
					shared_ptr<Weapon> mainhand2 = nullptr;
					shared_ptr<Weapon> offhand2 = nullptr;
					std::cout << "\n=--->\n" << std::endl;
					if (!livingAlliesPointers.empty())
					{
						player->inventory.getEquippedWeapons(mainhand, offhand, mainhand2, offhand2);
						cout << dye::light_yellow("1") << ") " << dye::light_yellow(player->name) << " "
							<< dye::white(mainhand->name) << dye::light_yellow("; ") << dye::white(offhand->name) << endl;
						for (int i = 0; i < livingAlliesPointers.size(); i++)
						{
							livingAlliesPointers[i]->inventory.getEquippedWeapons(mainhand, offhand, mainhand2, offhand2);
							cout << dye::light_yellow(i + 2) << ") " << dye::light_yellow(livingAlliesPointers[i]->name) << " "
								<< dye::white(mainhand->name) << dye::light_yellow("; ") << dye::white(offhand->name) << endl;
						}
						cout << dye::light_yellow(livingAlliesPointers.size() + 1) << dye::light_yellow(") Go back") << endl;

						//input validation
						int checkAllyChoice = validateInput(1, livingAlliesPointers.size() + 1);
						if (checkAllyChoice == livingAlliesPointers.size() + 1) // GO BACK
						{
							break;
						}
						else // CHECK ALLY EQUIPMENT DETAILS
						{
							//TODO
							cout << dye::light_yellow("PLACEHOLDER CHECK ALLY EQUIPMENT") << endl;
							break;
						}
					}
					else if (livingAlliesPointers.empty())
					{
						player->inventory.getEquippedWeapons(mainhand, offhand, mainhand2, offhand2);
						cout << dye::light_yellow("1") << ") " << dye::light_yellow(player->name) << " "
							<< dye::white(mainhand->name) << dye::light_yellow("; ") << dye::white(offhand->name) << endl;
						cout << dye::light_yellow("2") << dye::light_yellow(") Go back") << endl;

						//input validation
						int checkAllyChoice = validateInput(1, 2);
						if (checkAllyChoice == 2) // GO BACK
						{
							break;
						}
						else // CHECK SELF EQUIPMENT DETAILS
						{
							//TODO
							cout << dye::light_yellow("PLACEHOLDER CHECK SELF EQUIPMENT") << endl;
							break;
						}
					}
					break;
				}
				case 10: // FLEE
				{
					//TODO
					break;
				}
				}
				}
				//Only progress to taking turns once the player locks in a choice, denoted by the boolean inputChosen
				if (inputChosen)
				{
					/*static_assert(std::is_base_of<Character, Creature>::value, "Creature should inherit from Character!");
					static_assert(std::is_base_of<Character, Human>::value, "Human should inherit from Character!");
					std::cout << "Type of summoned creature: " << typeid(*player->allies.back()).name() << std::endl;*/
					vector<shared_ptr<Character>> combatants;
					combatants.push_back(player);
					combatants.insert(combatants.end(), livingAlliesPointers.begin(), livingAlliesPointers.end());
					combatants.insert(combatants.end(), livingEnemiesPointers.begin(), livingEnemiesPointers.end());

					//sorts combatants by speed
					sort(combatants.begin(), combatants.end(), [](shared_ptr<Character> a, shared_ptr<Character> b) {return a->speed > b->speed; });

					//dummy effect to call refresh effects
					std::shared_ptr<Effect> effect = nullptr;

					// Process turns
					for (int i = 0; i < combatants.size(); i++)
					{
						if (combatants[i]->isAlive)
						{
							if (shared_ptr<Creature> creature = std::dynamic_pointer_cast<Creature>(combatants[i]))
							{
									if (creature->isAlly)
									{
										cout << "CREATURE ALLY TURN" << endl;
									}
									else
									{
										// Enemy Turn
										cout << "CREATURE ENEMY TURN" << endl;
									}
							}

							else if (shared_ptr<Human> human = dynamic_pointer_cast<Human>(combatants[i]); human && human->isPlayer)
							{
								// Player Turn
								playerTurn(human, weaponChoice, ammoChoice, spellChoice, targetChoice, thrownConsumableChoice, consumableChoice, playerMovement);
								
								//If player summoned an ally, add it to the living allies vector
								if (spellChoice)
								{
									if (spellChoice->summon)
									{
										shared_ptr<Character> summonedCreature = player->allies.back();
										livingAlliesPointers.push_back(summonedCreature);
									}
								}
							}

							else if (auto human = dynamic_pointer_cast<Human>(combatants[i]); human && human->isAlly)
							{
								// Ally Turn
								cout << "HUMAN ALLY TURN" << endl;
							}
							else
							{
								
								
								// Enemy Turn
								cout << "ENEMY TURN" << endl;
								cout << combatants[i]->name << " DISTANCE: " << combatants[i]->position[player->getId()] << endl;
							}
						}
					}

					//refresh effects at the end of each round (Pokemon rules baby)
					for (shared_ptr<Character> combatant : combatants)
					{
						effect->refreshEffects(combatant);
						if (combatant->healthPoints <= 0)
						{
							combatant->killCharacter();
							break;
						}
					}
					// Remove dead combatants 
					auto removeDead = [](vector<shared_ptr<Character>>& vec) {
						vec.erase(remove_if(vec.begin(), vec.end(), [](shared_ptr<Character> c) { return !c->isAlive; }), vec.end());
						};

					removeDead(livingEnemiesPointers);
					removeDead(livingAlliesPointers);
				}
				if (livingEnemiesPointers.size() == 0)
				{
					exitCombat = true;
				}

			} while (exitCombat == false);
		}


		//input 1: attack target
		// -> present option to attack forward, attack in place, attack in retreat, or go back
		// -> 1) Advance and Attack!
		// -> 2) Stand your ground and Attack!
		// -> -> (sub menu) 1) normal attack
		// -> -> (sub menu) 2) grapple enemy (strength check; if success, enemy is grappled and loses their turn + damage; if fail, player wastes turn & chance to take damage)
		// -> 3) Retreat and Attack!
		// -> 4) Go back
		// -> -> display all targets, greying out targets not in range of selected attack option with longest weapon or go back
		// -> -> 1) _____; ten stage health descriptor: _____; ten stage fatigue descriptor: _____; ten stage confidence descriptor: _____; (always highest level enemy)
		// -> -> 2) _____; ten stage health descriptor: _____; ten stage fatigue descriptor: _____; ten stage confidence descriptor: _____; (lowest level enemy)
		// -> -> 3) Go back
		// -> -> -> display all attack options (mainhand, offhand, spells if either main or offhands are casting tools) 
		// -> -> -> -> 1) Mainhand: _____; Damage: _____; Reach: _____; Speed: _____; Damgage Type: _____; Magic Damage Type: _____ (only if applicable)
		// -> -> -> -> 2) Offhand: _____; Damage: _____; Reach: _____; Speed: _____; Damgage Type: _____; Magic Damage Type: _____ (only if applicable)
		// -> -> -> -> (sub menu) 1) Spell: _____; Damage: _____; Reach: _____; Speed: _____; Damgage Type: _____; (only if applicable) Magic Damage Type: _____ 
		// -> -> -> -> (sub menu) 2) Bash them with your catalyst (always second to last option)
		// -> -> -> -> (sub menu) 3) Go back
		// -> -> -> -> 3) Go back
		// -> -> -> -> -------------------------
		// -> -> -> -> (sub menu) 1) Arrow: _____; Damage: _____; Reach: _____; Damgage Type: _____; Magic Damage Type: _____ (only if applicable)
		// -> -> -> -> (sub menu) 2) Bolt: _____; Damage: _____; Reach: _____; Damgage Type: _____; Magic Damage Type: _____ (only if applicable)
		// -> -> -> -> (sub menu) 3) Go back
		// -> -> -> -> grey out attack options not in range of specified target (ex: mainhand is spear offhand is dagger, offhand out of range but mainhand in range) or go back
		// -> -> -> -> -> 1) _____; 10 stage level descriptor; 10 stage health descriptor; 10 stage fatigue descriptor; 10 stage confidence descriptor
		// -> -> -> -> -> 2) _____; 10 stage level descriptor; 10 stage health descriptor; 10 stage fatigue descriptor; 10 stage confidence descriptor
		// -> -> -> -> -> 3) Go back
		// -> -> -> -> set values for player option choice, weapon choice, spell choice, and target choice

		//input 2: swap from mainhand and offhand to back items and vice versa
		// -> present option to swap mainhand and offhand with back items or go back
		// -> 1) Swap to your stowed weapons
		// -> -> - MAINHAND1 -> MAINHAND2
		// -> -> - OFFHAND1 -> OFFHAND2
		// -> 2) Go back
		// -> -> set values for player option choice (function will handle getting the quipped items and transferring them between slots)

		//input 3: view spells
		// -> present short list of all attuned spells (max of 10)
		// -> =---> Name: _____; Damage: _____; fatigue Cost: _____; Reach: _____; Speed: _____; Damage Type: _____; (if applicable) Magic Damage Type: _____
		// -> =---> Name: _____; Damage: _____; fatigue Cost: _____; Reach: _____; Speed: _____; Damage Type: _____; (if applicable) Magic Damage Type: _____

		//input 4: use potion
		// -> present short list of all potions
		// -> 1) _____ Potion; Magnitude: __; Quantity: __
		// -> 2) _____ Potion; Magnitude: __; Quantity: __
		// -> 3) Go back
		// -> -> present option to use on self, ally, or go back
		// -> -> -> self: set values for player option choice, potion choice, and target choice
		// -> -> -> ally: display all allies, greying out allies at full health
		// -> -> -> -> set values for player option choice, potion choice, and target choice

		//input 5: use item
		// -> present short list of all usable items in backpack (food, tools, etc)
		// -> 1) _____; Damage/Healing/Effect: __; Quantity: __
		// -> 2) _____; Damage/Healing/Effect: __; Quantity: __
		// -> 3) Go back
		// -> -> present option to use on self, ally, enemy, or go back
		// -> -> -> self: set values for player option choice, item choice, and target choice
		// -> -> -> ally: display all allies, greying out allies at full health
		// -> -> -> -> set values for player option choice, item choice, and target choice

		//input 6: check allies or self
		// -> display all allies and self
		// -> 1) _____; Health: __; fatigue: __; Confidence: __ (always player)
		// -> 2) _____; Health: __; fatigue: __; Confidence: __
		// -> 3) Go back
		// -> -> (self) display flavor text about your condition and equipped items
		// -> -> (ally) display flavor text about ally condition and equipped items

		//input 7: check enemies
		// -> display all enemies (sort by level)
		// -> 1) _____; 10 stage level descriptor; 10 stage health descriptor; 10 stage fatigue descriptor; 10 stage confidence descriptor
		// -> 2) _____; 10 stage level descriptor; 10 stage health descriptor; 10 stage fatigue descriptor; 10 stage confidence descriptor
		// -> 3) Go back

		//input 8: taunt enemies (confidence boost allies, makes enemy focus on you)
		// -> present all enemies
		// -> 1) _____; 10 stage level descriptor; 10 stage health descriptor; 10 stage fatigue descriptor; 10 stage confidence descriptor
		// -> 2) _____; 10 stage level descriptor; 10 stage health descriptor; 10 stage fatigue descriptor; 10 stage confidence descriptor
		// -> 3) Go back
		// -> -> 1) Taunt _____;
		// -> -> 2) Make something up

		//input 9: check allies or self equipment
		// -> Display all allies or self brief equipment overview
		// -> 1) _____; HP: _____; Mainhand: __; Offhand: __; Backslot1: __; Backslot2: __;
		// -> 2) _____; HP: _____; Mainhand: __; Offhand: __; Backslot1: __; Backslot2: __;
		// -> 3) Go back
		// -> -> (self) display all equipped items and their stats
		// -> -> (ally) display all equipped items and their stats

		//input 10: attempt to flee
		// -> Display 10 stage descriptor at odds of getting away
		// -> 1) Attempt to flee
		// -> 2) Go back


	} while (exitFight == false);
}
void playerTurn(std::shared_ptr<Human> player, shared_ptr<Weapon> weaponChoice, std::shared_ptr<Ammunition> ammoChoice, shared_ptr<Spell> spellChoice, shared_ptr<Character> targetChoice, std::shared_ptr<ThrownConsumable> thrownConsumableChoice,
	std::shared_ptr<Consumable> consumableChoice, float playerMovement)
{
	//Check if player object is null
	if (!player)
	{
		cout << "ERROR: player is null!" << endl;
		return;
	}
	//Target is a human
	if (dynamic_pointer_cast<std::shared_ptr<Human>>(targetChoice))
	{
		std::shared_ptr<Human> humanTarget = dynamic_pointer_cast<Human>(targetChoice);

		//move player
		
		if (playerMovement < 0) cout << "You advance by " << abs(playerMovement) << " units!" << endl;
		else if (playerMovement > 0) cout << "You retreat by " << abs(playerMovement) << " units!" << endl;
		else cout << "You stand your ground!" << endl;

		targetChoice->position[player->getId()] += playerMovement;

		//Printing if the player cannot move towards the enemy any closer
		if (targetChoice->position[player->getId()] <= 0)
		{
			targetChoice->position[player->getId()] = 0;
			cout << "You stand close enough to touch " << targetChoice->name << "!" << endl;
		}

		//Stop the turn if the player only chose to move
		if (playerMovement && !weaponChoice && !spellChoice && !thrownConsumableChoice && !consumableChoice)
		{
			return;
		}

		//Applying Passive Armor Enchantments
		for (std::shared_ptr<Item> item : player->inventory.equippedItems)
		{
			if (dynamic_pointer_cast<std::shared_ptr<Armor>>(item))
			{
				std::shared_ptr<Armor> armor = dynamic_pointer_cast<Armor>(item);
				for (std::shared_ptr<Enchantment> enchant : armor->enchantments)
				{
					if (!enchant->doesDamage)
					{
						//enchant->applyPassiveEffect(enchant, player);
					}
				}
			}
		}
		//Player chose to cast a spell
		if (spellChoice)
		{
			if (weaponChoice->weaponType != Weapon::WeaponType::TALISMAN && weaponChoice->weaponType != Weapon::WeaponType::CHIME &&
				weaponChoice->weaponType != Weapon::WeaponType::TOME && weaponChoice->weaponType != Weapon::WeaponType::ORB &&
				weaponChoice->weaponType != Weapon::WeaponType::STAFF && weaponChoice->weaponType != Weapon::WeaponType::WAND)
			{
				cout << "ERROR: weapon is not a casting tool!" << endl;
				return;
			}
			else
			{
				if (weaponChoice)
				{
					player->castSpell(*spellChoice, humanTarget, playerMovement);
				}
				else
				{
					cout << "ERROR: no weapon initialized!" << endl;
					return;
				}
			}
		}
		//Player chose to cast a spell on an ally
		if (spellChoice && humanTarget->isAlly)
		{
			if (weaponChoice->weaponType != Weapon::WeaponType::TALISMAN && weaponChoice->weaponType != Weapon::WeaponType::CHIME &&
				weaponChoice->weaponType != Weapon::WeaponType::TOME && weaponChoice->weaponType != Weapon::WeaponType::ORB &&
				weaponChoice->weaponType != Weapon::WeaponType::STAFF && weaponChoice->weaponType != Weapon::WeaponType::WAND)
			{
				cout << "ERROR: weapon is not a casting tool!" << endl;
				return;
			}
			else
			{
				if (weaponChoice)
				{
					player->castSpell(*spellChoice, humanTarget, playerMovement);
				}
				else
				{
					cout << "ERROR: no weapon initialized!" << endl;
					return;
				}
			}
		}
		//Player chose to attack an enemy with a melee weapon
		if (weaponChoice && !spellChoice)
		{
			player->attackWithMelee(weaponChoice, humanTarget);
		}
		//Player chose to attack an enemy with a ranged weapon
		if (weaponChoice && ammoChoice)
		{
			player->fireRangedWeapon(humanTarget, weaponChoice, ammoChoice);
		}
		//Player chose to attack an enemy with a thrown weapon
		if (thrownConsumableChoice)
		{
			player->throwThrownConsumable(thrownConsumableChoice, humanTarget);
		}
		//Player chose to share a consumable with an ally
		if (consumableChoice && humanTarget->isAlly)
		{

		}
		//Player chose to consume a consumable
		if (consumableChoice)
		{

		}
	}
	//Target is a creature
	else
	{
		cout << "ATTACKING CREATURES UNDER CONSTRUCTION!" << endl;
	}

}
//void attackEnemy(int& attackChoice, int weaponChoice, bool& progressRound, int inRange, Character& player, vector<Character>& enemies, vector<Character>& deadEnemies, Item mainhand1, Item mainhand2,
//	Item offhand1, Item offhand2, Item headArmor, Item chestArmor, Item armArmor, Item legArmor, Item amulet,
//	Item ring1, Item ring2, Item misc)
//{
//	//more functionality can be added later as more features get implemented
//	//such as:
//	//  -enchantments from equipped items influencing damage
//	//  -status effects
//	//  -etc.
//
//	if (weaponChoice == 1)
//	{
//		//mainhand
//		//weapon speed caps at 100. 
//		// Luck has a small impact on attack speed, making the "threshold" before they're done attacking
//		// for a turn longer.
//		float attackSpeedValue = abs(mainhand1.attackSpeed - 101);
//		for (int i = 0; i < 101 + player->luck;)
//		{
//
//			enemies[attackChoice - 1].takeDamage(mainhand1, player);
//			if (enemies[attackChoice - 1].isAlive == false)
//			{
//				deadEnemies.push_back(enemies[attackChoice - 1]);
//				enemies.erase(enemies.begin() + attackChoice - 1);
//				break;
//			}
//			//this is necessary, otherwise the loop will just keep attacking every enemy no matter 
//			//  what the user selects
//			i += attackSpeedValue;
//		}
//		attackChoice = 0;
//
//	}
//	else if (weaponChoice == 2)
//	{
//		//offhand
//		float attackSpeedValue = abs(offhand1.attackSpeed - 101);
//		for (int i = 0; i < 101;)
//		{
//
//			enemies[attackChoice - 1].takeDamage(offhand1, player);
//			if (enemies[attackChoice - 1].isAlive == false)
//			{
//				deadEnemies.push_back(enemies[attackChoice - 1]);
//				enemies.erase(enemies.begin() + attackChoice - 1);
//				break;
//			}
//			//this is necessary, otherwise the loop will just keep attacking every enemy no matter 
//			//  what the user selects
//			i += attackSpeedValue;
//		}
//		attackChoice = 0;
//	}
//}

//void enemyTurn(Character& player, shared_ptr<Character> enemy, vector<Character>& deadAllies, vector<Character>& livingAllies)
//{
//	//get enemy items
//	//should really make this kind of thing a function...
//	Item enemyMainhand;
//	Item enemyOffhand;
//	Item enemyHeadArmor;
//	Item enemyChestArmor;
//	Item enemyArmArmor;
//	Item enemyLegArmor;
//	Item enemyAmulet;
//	Item enemyRing1;
//	Item enemyRing2;
//	Item enemyMisc;
//
//	vector<Item> enemyItems = enemy->inventory.getEquippedItems();
//
//	for (int i = 0; i < enemyItems.size(); i++)
//	{
//		if (enemyItems[i].slot == Item::MAINHAND1)
//		{
//			enemyMainhand = enemyItems[i];
//		}
//		if (enemyItems[i].slot == Item::OFFHAND1)
//		{
//			enemyOffhand = enemyItems[i];
//		}
//		if (enemyItems[i].slot == Item::HEAD)
//		{
//			enemyHeadArmor = enemyItems[i];
//		}
//		if (enemyItems[i].slot == Item::CHEST)
//		{
//			enemyChestArmor = enemyItems[i];
//		}
//		if (enemyItems[i].slot == Item::ARMS)
//		{
//			enemyArmArmor = enemyItems[i];
//		}
//		if (enemyItems[i].slot == Item::LEGS)
//		{
//			enemyLegArmor = enemyItems[i];
//		}
//		if (enemyItems[i].slot == Item::AMULET)
//		{
//			enemyAmulet = enemyItems[i];
//		}
//		if (enemyItems[i].slot == Item::RING1)
//		{
//			enemyRing1 = enemyItems[i];
//		}
//		if (enemyItems[i].slot == Item::RING2)
//		{
//			enemyRing2 = enemyItems[i];
//		}
//		if (enemyItems[i].slot == Item::MISC)
//		{
//			enemyMisc = enemyItems[i];
//		}
//	}
//	//sets confidence level, max of 100, starts at 100 for humans by default as a baseline
//	// more flighty creatures will have lower confidence levels and vice versa
//	// the larger the difference between the player's level and the enemy's level, the lower the confidence level
//	// higher confidence levels give the chance for the enemy to use their turn insulting the player 
//	// or moving back and forth for no reason because they're confident they can win and to give the player more breathing
//	// room in larger fights
//
//	//DETAILS:
//
//	//confidence level is lowered by 5 for every level the player is above the enemy
//	//confidence level is increased by 5 for every level the player is below the enemy (up to 100)
//	//confidence level is lowered by 5 for every 10% of health the enemy loses
//	//confidence level is raised by 5 for every 10% of health the enemy regains
//
//	//confidence level is lowered by 1 for every 10% hp that an ally loses
//	//confidence level is increased by 1 for every 10%hp that an ally heals
//	//confidence level is raised by 10 for every 10% of health the player loses
//	//confidence level is lowered by 10 for every 10% of health the player regains
//
//	//confidence level is lowered by 50 for every ally that dies
//
//	////removes the enemy in question from the pool of allies
//	//for (int i = 0; i < livingAllies.size(); i++)
//	//{
//
//	//	if (livingAllies[i].name == enemy->name)
//	//	{
//	//		livingAllies.erase(livingAllies.begin() + i);
//	//		break; // Exit the loop after erasing the element
//	//	}
//
//	//}
//
//	// check dead allies
//	int deadAlliesNum = 0;
//	if (!deadAllies.empty())
//	{
//		for (int i = 0; i < deadAllies.size(); i++)
//		{
//			deadAlliesNum += 50;
//		}
//	}
//	enemy->confidenceLevel -= deadAlliesNum;
//
//	// check living allies
//	float healthLost = 0;
//	if (!livingAllies.empty())
//	{
//		for (int i = 0; i < livingAllies.size(); i++)
//		{
//			healthLost += (livingAllies[i].maxHealthPoints - livingAllies[i].healthPoints) / 10.0f;
//		}
//	}
//	enemy->confidenceLevel -= healthLost;
//
//	//check player health
//	float playerHealthLost = (player->maxHealthPoints - player->healthPoints) / 10.0f;
//	enemy->confidenceLevel += playerHealthLost;
//
//	//check player level
//	float levelDifference = player->level - enemy->level;
//	enemy->confidenceLevel -= levelDifference * 5;
//
//	//last minute sanity checks
//	if (enemy->confidenceLevel > 100)
//	{
//		enemy->confidenceLevel = 100;
//	}
//	if (enemy->confidenceLevel < 0)
//	{
//		enemy->confidenceLevel = 0;
//	}
//
//	//random number generator for decision making
//	int randomNum = (rand() % 101) + 1;
//
//
//	//decision tree
//
//	//enemy is confident, high chance to insult the player or meander about
//	if (enemy->confidenceLevel >= 90)
//	{
//		//insult the player
//		if (randomNum >= 60 - player->luck)
//		{
//			std::cout << "=--->" << std::endl;
//			getCombatBanter(*enemy, player);
//		}
//		//meander about
//		else if (randomNum >= 60 - player->luck)
//		{
//			std::cout << "=--->" << std::endl;
//			cout << "The " << enemy->name << " meanders about. Are they looking for an opening, or just taunting you?" << endl;
//		}
//		//attack the player
//		else
//		{
//			int distanceTraveled = enemy->speed / 10;
//			std::cout << "=--->" << std::endl;
//			if (enemy->distanceFromPlayer >= enemyMainhand.reach)
//			{
//				if (distanceTraveled > enemy->distanceFromPlayer || enemy->distanceFromPlayer < 0)
//				{
//					distanceTraveled = 0;
//					enemy->distanceFromPlayer = 0;
//					cout << "The " << enemy->name << " is right on top of you!" << endl;
//				}
//				else
//				{
//					cout << "The " << enemy->name << " advances by " << distanceTraveled << " units!" << endl;
//					enemy->distanceFromPlayer -= distanceTraveled;
//				}
//			}
//			else
//			{
//				for (int i = 0; i < 101;)
//				{
//					player->takeDamage(enemyMainhand, *enemy);
//					if (player->isAlive == false)
//					{
//						cout << "The " << enemy->name << " strikes you down!" << endl;
//						break;
//					}
//					i += enemyMainhand.attackSpeed;
//				}
//			}
//		}
//	}
//	//enemy is confident, medium chance to insult the player or meander about
//	else if (enemy->confidenceLevel < 90 && enemy->confidenceLevel >= 80)
//	{
//		//insult the player
//		if (randomNum >= 80 - player->luck)
//		{
//			std::cout << "=--->" << std::endl;
//			getCombatBanter(*enemy, player);
//		}
//		//meander about
//		else if (randomNum >= 80 - player->luck)
//		{
//			std::cout << "=--->" << std::endl;
//			cout << "The " << enemy->name << " meanders about. Are they looking for an opening, or just taunting you?" << endl;
//		}
//		//attack the player
//		else
//		{
//			int distanceTraveled = enemy->speed / 10;
//			std::cout << "=--->" << std::endl;
//			if (enemy->distanceFromPlayer >= enemyMainhand.reach)
//			{
//				if (distanceTraveled > enemy->distanceFromPlayer || enemy->distanceFromPlayer < 0)
//				{
//					distanceTraveled = 0;
//					enemy->distanceFromPlayer = 0;
//					cout << "The " << enemy->name << " is right on top of you!" << endl;
//				}
//				else
//				{
//					cout << "The " << enemy->name << " advances by " << distanceTraveled << " units!" << endl;
//					enemy->distanceFromPlayer -= distanceTraveled;
//				}
//			}
//			else
//			{
//				for (int i = 0; i < 101;)
//				{
//					player->takeDamage(enemyMainhand, *enemy);
//					if (player->isAlive == false)
//					{
//						cout << "The " << enemy->name << " strikes you down!" << endl;
//						break;
//					}
//					i += enemyMainhand.attackSpeed;
//				}
//			}
//		}
//	}
//	//enemy is confident, low chance to meander about or insult the player
//	else if (enemy->confidenceLevel < 80 && enemy->confidenceLevel >= 70)
//	{
//		//insult the player
//		if (randomNum >= 90 - player->luck)
//		{
//			std::cout << "=--->" << std::endl;
//			getCombatBanter(*enemy, player);
//		}
//		//meander about
//		else if (randomNum >= 90 - player->luck)
//		{
//			std::cout << "=--->" << std::endl;
//			cout << "The " << enemy->name << " meanders about. Are they looking for an opening, or just taunting you?" << endl;
//		}
//		//attack the player
//		else
//		{
//			int distanceTraveled = enemy->speed / 10;
//			std::cout << "=--->" << std::endl;
//			if (enemy->distanceFromPlayer >= enemyMainhand.reach)
//			{
//				if (distanceTraveled > enemy->distanceFromPlayer || enemy->distanceFromPlayer < 0)
//				{
//					distanceTraveled = 0;
//					enemy->distanceFromPlayer = 02;
//					cout << "The " << enemy->name << " is right on top of you!" << endl;
//				}
//				else
//				{
//					cout << "The " << enemy->name << " advances by " << distanceTraveled << " units!" << endl;
//					enemy->distanceFromPlayer -= distanceTraveled;
//				}
//			}
//			else
//			{
//				for (int i = 0; i < 101;)
//				{
//					player->takeDamage(enemyMainhand, *enemy);
//					if (player->isAlive == false)
//					{
//						cout << "The " << enemy->name << " strikes you down!" << endl;
//						break;
//					}
//					i += enemyMainhand.attackSpeed;
//				}
//			}
//		}
//	}
//	//enemy is not confident, check ally health and heal if necessary
//	//future implementation: allow them to use miracles to heal their allies
//	else if (enemy->confidenceLevel < 70 && enemy->confidenceLevel >= 60)
//	{
//		bool allyNeedsHealing = false;
//		for (int i = 0; i < livingAllies.size(); i++)
//		{
//			if (livingAllies[i].healthPoints <= livingAllies[i].maxHealthPoints * .5)
//			{
//				allyNeedsHealing = true;
//				break;
//			}
//		}
//		//heal allies if possible
//		if (allyNeedsHealing == true)
//		{
//			enemySharePotion(*enemy, livingAllies);
//		}
//		//heal themselves if not possible
//		else if (enemy->healthPoints <= enemy->maxHealthPoints * .5)
//		{
//			//find the first healing potion they have access to
//			for (int i = 0; i < enemy->inventory.potions.size(); i++)
//			{
//				if (enemy->inventory.potions[i].effects == Potion::HEALING)
//				{
//					enemy->drinkPotion(enemy->inventory.potions[i]);
//					break;
//				}
//			}
//		}
//		//attack the player
//		else
//		{
//			std::cout << "=--->" << std::endl;
//			for (int i = 0; i < 101;)
//			{
//				player->takeDamage(enemyMainhand, *enemy);
//				if (player->isAlive == false)
//				{
//					cout << "The " << enemy->name << " strikes you down!" << endl;
//					break;
//				}
//				i += enemyMainhand.attackSpeed;
//			}
//		}
//	}
//	//enemy is not confident, attack player, check ally health and heal if necessary
//	//future implementation: give them a very small chance for spells to fail
//
//	//enemy is not confident, attack player, check ally health and heal if necessary
//	//future implementation: give them a small chance for spells to fail
//
//	//enemy is terrified, attack player (swing speed increased, chance to miss increased), heals self
//	//future implementation: give them a small-medium chance for spells to fail
//
//	//enemy is terrified, attack player (swing speed increased, chance to miss greatly increased), heals self
//	//future implementation: give them a medium chance for spells to fail
//
//	//enemy is terrified, retreat (not flee, it would be annoying to the player), heals self
//}

//void printPotions(bool& progressRound, Character& character) {
//	std::cout << "You have the following potions:" << std::endl;
//	//add more here as more types get implemented
//
//	int healingTally = 0;
//	int fatigueTally = 0;
//	int cureDiseaseTally = 0;
//
//	std::string types[] = { "Restores Health", "Restores fatigue", "Cures Diseases" };
//
//	for (int i = 0; i < character.inventory.potions.size(); i++)
//	{
//		if (character.inventory.potions[i].effects == Potion::HEALING)
//		{
//			healingTally += character.inventory.potions[i].quantity;
//		}
//		else if (character.inventory.potions[i].effects == Potion::fatigue)
//		{
//			fatigueTally += character.inventory.potions[i].quantity;
//		}
//		else if (character.inventory.potions[i].effects == Potion::CUREDISEASE)
//		{
//			cureDiseaseTally += character.inventory.potions[i].quantity;
//		}
//	}
//
//	int categoryTally = 0;
//
//	categoryTally += 1;
//	std::cout << dye::light_yellow(categoryTally) << dye::light_yellow(") Healing Potions: x") << dye::light_yellow(healingTally) << std::endl;
//
//	categoryTally += 1;
//	std::cout << dye::light_yellow(categoryTally) << dye::light_yellow(") fatigue Potions: x") << dye::light_yellow(fatigueTally) << std::endl;
//
//	categoryTally += 1;
//	std::cout << dye::light_yellow(categoryTally) << dye::light_yellow(") Cure Disease Potions: x") << dye::light_yellow(cureDiseaseTally) << std::endl;
//
//	std::cout << "Would you like to drink a potion? Enter its number or press " << categoryTally + 1
//		<< " to go back" << std::endl;
//	int potionChoice = 0;
//	//input validation
//	do
//	{
//		std::cout << "\n>> ";
//		std::cin >> potionChoice;
//		if (std::cin.fail() || potionChoice > categoryTally + 1 || potionChoice == 0)
//		{
//			std::cout << "Enter a number from 1 - " << categoryTally + 1 << std::endl;
//		}
//		std::cin.clear();
//		std::cin.ignore(10000, '\n');
//	} while (std::cin.fail() || potionChoice > categoryTally + 1 || potionChoice == 0);
//
//	if (potionChoice == categoryTally + 1)
//	{
//		//we don't want it to consume a round if they decide not to drink a potion
//		progressRound = false;
//		return;
//	}
//	else
//	{
//		//healing potions
//		if (potionChoice == 1 && healingTally > 0)
//		{
//			std::vector<Potion> healingPotions;
//			std::cout << "Select which healing potion you would like to drink.." << std::endl;
//			for (int i = 1; i < character.inventory.potions.size() + 1; i++)
//			{
//				if (character.inventory.potions[i - 1].effects == Potion::HEALING)
//				{
//					std::cout << i << ") " << character.inventory.potions[i - 1].name << ", magnitude of "
//						<< character.inventory.potions[i - 1].magnitude << ", quantity of " << character.inventory.potions[i - 1].quantity << std::endl;
//					healingPotions.push_back(character.inventory.potions[i - 1]);
//				}
//			}
//			std::cout << healingPotions.size() + 1 << ") Go back" << std::endl;
//
//			do
//			{
//				std::cout << ">> ";
//				std::cin >> potionChoice;
//				if (std::cin.fail() || potionChoice > healingPotions.size() + 1 || potionChoice == 0)
//				{
//					std::cout << "Enter a number from 1 - " << healingPotions.size() + 1 << std::endl;
//				}
//				std::cin.clear();
//				std::cin.ignore(10000, '\n');
//			} while (std::cin.fail() || potionChoice > healingPotions.size() + 1 || potionChoice == 0);
//
//			if (potionChoice == healingPotions.size() + 1)
//			{
//				progressRound = false;
//			}
//			else
//			{
//				character.drinkPotion(healingPotions[potionChoice - 1]);
//				progressRound = true;
//			}
//		}
//		else if (potionChoice == 1 && healingTally <= 0)
//		{
//			std::cout << "You don't have any healing potions!" << std::endl;
//			progressRound = false;
//		}
//		//fatigue potions
//		else if (potionChoice == 2 && fatigueTally > 0)
//		{
//			std::vector<Potion> fatiguePotions;
//			std::cout << "Select which fatigue potion you would like to drink.." << std::endl;
//			for (int i = 1; i < character.inventory.potions.size() + 1; i++)
//			{
//				if (character.inventory.potions[i - 1].effects == Potion::fatigue)
//				{
//					std::cout << i << ") " << character.inventory.potions[i - 1].name << ", magnitude of "
//						<< character.inventory.potions[i - 1].magnitude << ", quantity of " << character.inventory.potions[i - 1].quantity << std::endl;
//					fatiguePotions.push_back(character.inventory.potions[i - 1]);
//				}
//			}
//			std::cout << fatiguePotions.size() + 1 << ") Go back" << std::endl;
//			do
//			{
//				std::cout << ">> ";
//				std::cin >> potionChoice;
//				if (std::cin.fail() || potionChoice > fatiguePotions.size() + 1 || potionChoice == 0)
//				{
//					std::cout << "Enter a number from 1 - " << fatiguePotions.size() + 1 << std::endl;
//				}
//				std::cin.clear();
//				std::cin.ignore(10000, '\n');
//			} while (std::cin.fail() || potionChoice > fatiguePotions.size() + 1 || potionChoice == 0);
//			if (potionChoice == fatiguePotions.size() + 1)
//			{
//				progressRound = false;
//			}
//			else
//			{
//				character.drinkPotion(fatiguePotions[potionChoice - 1]);
//				progressRound = true;
//			}
//		}
//		else if (potionChoice == 2 && fatigueTally <= 0)
//		{
//			std::cout << "You don't have any fatigue potions!" << std::endl;
//			progressRound = false;
//		}
//		//cure disease potions
//		else if (potionChoice == 3 && cureDiseaseTally > 0)
//		{
//			std::vector<Potion> cureDiseasePotions;
//			std::cout << "Select which cure disease potion you would like to drink.." << std::endl;
//			for (int i = 1; i < character.inventory.potions.size() + 1; i++)
//			{
//				if (character.inventory.potions[i - 1].effects == Potion::CUREDISEASE)
//				{
//					std::cout << i << ") " << character.inventory.potions[i - 1].name << ", magnitude of "
//						<< character.inventory.potions[i - 1].magnitude << ", quantity of " << character.inventory.potions[i - 1].quantity << std::endl;
//					cureDiseasePotions.push_back(character.inventory.potions[i - 1]);
//				}
//			}
//			std::cout << cureDiseasePotions.size() + 1 << ") Go back" << std::endl;
//			do
//			{
//				std::cout << ">> ";
//				std::cin >> potionChoice;
//				if (std::cin.fail() || potionChoice > cureDiseasePotions.size() + 1 || potionChoice == 0)
//				{
//					std::cout << "Enter a number from 1 - " << cureDiseasePotions.size() + 1 << std::endl;
//				}
//				std::cin.clear();
//				std::cin.ignore(10000, '\n');
//			} while (std::cin.fail() || potionChoice > cureDiseasePotions.size() + 1 || potionChoice == 0);
//			if (potionChoice == cureDiseasePotions.size() + 1)
//			{
//				progressRound = false;
//			}
//			else
//			{
//				character.drinkPotion(cureDiseasePotions[potionChoice - 1]);
//				progressRound = true;
//			}
//		}
//		else if (potionChoice == 3 && cureDiseaseTally <= 0)
//		{
//			std::cout << "You don't have any cure disease potions!" << std::endl;
//			progressRound = false;
//		}
//	}
//}
//
//void getCombatBanter(Character sender, Character& reciever)
//{
//	//random number generator for decision making
//	int randomNum = (rand() % 5) + 1;
//	//getting the sender's equipment
//	std::vector<Item> senderPotions = sender.inventory.potions();
//	std::vector<Item> senderItems = sender.inventory.getEquippedItems();
//	Item senderMainHand1;
//	Item senderMainHand2;
//	Item senderOffHand1;
//	Item senderOffHand2;
//	Item senderAmulet;
//	Item senderRing1;
//	Item senderRing2;
//	Item sendermisc;
//	Item senderHelmet;
//	Item senderChest;
//	Item senderArms;
//	Item senderLegs;
//
//	//until I figure out how to ensure this is set to false by default, we need this because its true 
//	//  by default 
//	senderMainHand1.hasBeenInitialized = false;
//	senderMainHand2.hasBeenInitialized = false;
//	senderOffHand1.hasBeenInitialized = false;
//	senderOffHand2.hasBeenInitialized = false;
//	senderAmulet.hasBeenInitialized = false;
//	senderRing1.hasBeenInitialized = false;
//	senderRing2.hasBeenInitialized = false;
//	sendermisc.hasBeenInitialized = false;
//	senderHelmet.hasBeenInitialized = false;
//	senderChest.hasBeenInitialized = false;
//	senderArms.hasBeenInitialized = false;
//	senderLegs.hasBeenInitialized = false;
//
//	for (int i = 0; i < senderItems.size(); i++)
//	{
//		if (senderItems[i].slot == Item::EquipSlots::MAINHAND)
//		{
//			senderMainHand1 = senderItems[i];
//		}
//		else if (senderItems[i].slot == Item::MAINHAND2)
//		{
//			senderMainHand2 = senderItems[i];
//		}
//		else if (senderItems[i].slot == Item::OFFHAND1)
//		{
//			senderOffHand1 = senderItems[i];
//		}
//		else if (senderItems[i].slot == Item::OFFHAND2)
//		{
//			senderOffHand2 = senderItems[i];
//		}
//		else if (senderItems[i].slot == Item::AMULET)
//		{
//			senderAmulet = senderItems[i];
//		}
//		else if (senderItems[i].slot == Item::RING1)
//		{
//			senderRing1 = senderItems[i];
//		}
//		else if (senderItems[i].slot == Item::RING2)
//		{
//			senderRing2 = senderItems[i];
//		}
//		else if (senderItems[i].slot == Item::MISC)
//		{
//			sendermisc = senderItems[i];
//		}
//		else if (senderItems[i].slot == Item::HEAD)
//		{
//			senderHelmet = senderItems[i];
//		}
//		else if (senderItems[i].slot == Item::CHEST)
//		{
//			senderChest = senderItems[i];
//		}
//		else if (senderItems[i].slot == Item::ARMS)
//		{
//			senderArms = senderItems[i];
//		}
//		else if (senderItems[i].slot == Item::LEGS)
//		{
//			senderLegs = senderItems[i];
//		}
//	}
//
//	//getting the reciever's equipment
//	std::vector<Potion> recieverPotions = reciever.inventory.potions;
//	std::vector<Item> recieverItems = reciever.inventory.getEquippedItems();
//	Item recieverMainHand1;
//	Item recieverMainHand2;
//	Item recieverOffHand1;
//	Item recieverOffHand2;
//	Item recieverAmulet;
//	Item recieverRing1;
//	Item recieverRing2;
//	Item recievermisc;
//	Item recieverHelmet;
//	Item recieverChest;
//	Item recieverArms;
//	Item recieverLegs;
//
//	//until I figure out how to ensure this is set to false by default, we need this because its true 
//	//  by default 
//	recieverMainHand1.hasBeenInitialized = false;
//	recieverMainHand2.hasBeenInitialized = false;
//	recieverOffHand1.hasBeenInitialized = false;
//	recieverOffHand2.hasBeenInitialized = false;
//	recieverAmulet.hasBeenInitialized = false;
//	recieverRing1.hasBeenInitialized = false;
//	recieverRing2.hasBeenInitialized = false;
//	recievermisc.hasBeenInitialized = false;
//	recieverHelmet.hasBeenInitialized = false;
//	recieverChest.hasBeenInitialized = false;
//	recieverArms.hasBeenInitialized = false;
//	recieverLegs.hasBeenInitialized = false;
//
//	for (int i = 0; i < recieverItems.size(); i++)
//	{
//		if (recieverItems[i].slot == Item::MAINHAND1)
//		{
//			recieverMainHand1 = recieverItems[i];
//		}
//		else if (recieverItems[i].slot == Item::MAINHAND2)
//		{
//			recieverMainHand2 = recieverItems[i];
//		}
//		else if (recieverItems[i].slot == Item::OFFHAND1)
//		{
//			recieverOffHand1 = recieverItems[i];
//		}
//		else if (recieverItems[i].slot == Item::OFFHAND2)
//		{
//			recieverOffHand2 = recieverItems[i];
//		}
//		else if (recieverItems[i].slot == Item::AMULET)
//		{
//			recieverAmulet = recieverItems[i];
//		}
//		else if (recieverItems[i].slot == Item::RING1)
//		{
//			recieverRing1 = recieverItems[i];
//		}
//		else if (recieverItems[i].slot == Item::RING2)
//		{
//			recieverRing2 = recieverItems[i];
//		}
//		else if (recieverItems[i].slot == Item::MISC)
//		{
//			recievermisc = recieverItems[i];
//		}
//		else if (recieverItems[i].slot == Item::HEAD)
//		{
//			recieverHelmet = recieverItems[i];
//		}
//		else if (recieverItems[i].slot == Item::CHEST)
//		{
//			recieverChest = recieverItems[i];
//		}
//		else if (recieverItems[i].slot == Item::ARMS)
//		{
//			recieverArms = recieverItems[i];
//		}
//		else if (recieverItems[i].slot == Item::LEGS)
//		{
//			recieverLegs = recieverItems[i];
//		}
//	}
//
//	if (randomNum == 1)
//	{
//		//WEAPONS
//		//if the player has nothing equipped
//		if (!recieverMainHand1.hasBeenInitialized && !recieverMainHand2.hasBeenInitialized && !recieverOffHand1.hasBeenInitialized && !recieverOffHand2.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("What are you gonna do, tickle me to death?") << endl;
//		}
//		//if the player is using a talisman
//		else if (recieverMainHand1.weaponType == Item::TALISMAN && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::TALISMAN && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("What, are you going to pray me to death?") << endl;
//		}
//		//if the player is using a chime
//		else if (recieverMainHand1.weaponType == Item::CHIME && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::CHIME && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("A chime? Good lord I'm annoyed already.") << endl;
//		}
//		//if the player is using a tome
//		else if (recieverMainHand1.weaponType == Item::TOME && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::TOME && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("Are you going to read me a bed time story from tome?") << endl;
//		}
//		//if the player is using a wand
//		else if (recieverMainHand1.weaponType == Item::WAND && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::WAND && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("Great. Another bloody wizard.") << endl;
//		}
//		//if the player is using a staff
//		else if (recieverMainHand1.weaponType == Item::STAFF && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::STAFF && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("A staff? You're gonna need it to walk when I'm done with you.") << endl;
//		}
//		//if the player is using a orb
//		else if (recieverMainHand1.weaponType == Item::ORB && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::ORB && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("An orb? I'll give you something to ponder!") << endl;
//		}
//		//if the player is using a dagger
//		else if (recieverMainHand1.weaponType == Item::DAGGER && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::DAGGER && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("Oh, a dagger! Are you going to carve me a little statue?") << endl;
//		}
//		//if the player is using a straight sword 
//		else if (recieverMainHand1.weaponType == Item::STRAIGHTSWORD && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::STRAIGHTSWORD && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("A straight sword? Fancy yourself a knight?") << endl;
//		}
//		//if the player is using a greatsword
//		else if (recieverMainHand1.weaponType == Item::GREATSWORD && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::GREATSWORD && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("A greatsword? You're compensating for something, aren't you?") << endl;
//		}
//		//if the player is using a fist weapon
//		else if (recieverMainHand1.weaponType == Item::FIST && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::FIST && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("Fist weapons? You're going to punch me to death? Really?") << endl;
//		}
//		//if the player is using a mace
//		else if (recieverMainHand1.weaponType == Item::MACE && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::MACE && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("A mace? The only skull you're cracking with that is your own when you trip over yourself.") << endl;
//		}
//		//if the player is using a great mace
//		else if (recieverMainHand1.weaponType == Item::GREATMACE && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::GREATMACE && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("A great mace? I'll just wait the three business days it will take for you to swing that thing.") << endl;
//		}
//		//if the player is using a hatchet
//		else if (recieverMainHand1.weaponType == Item::HATCHET && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::HATCHET && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("A hatchet? Did your Pa lend you that for tinder?") << endl;
//		}
//		//if the player is using a axe
//		else if (recieverMainHand1.weaponType == Item::AXE && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::AXE && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("An axe? There are plenty of trees around. Oh wait, you're using it as a weapon.") << endl;
//		}
//		//if the player is using a great axe
//		else if (recieverMainHand1.weaponType == Item::GREATAXE && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::GREATAXE && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("A great axe? The trees you fell with that must rival the girth of your mother!") << endl;
//		}
//		//if the player is using a thrusting sword
//		else if (recieverMainHand1.weaponType == Item::THRUSTINGSWORD && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::THRUSTINGSWORD && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("A thrusting sword? Fancy yourself some kind of noble?") << endl;
//		}
//		//if the player is using a spear
//		else if (recieverMainHand1.weaponType == Item::SPEAR && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::SPEAR && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("A spear? Coward, fight me from a reasonable range!") << endl;
//		}
//		//if the player is using a great spear
//		else if (recieverMainHand1.weaponType == Item::GREATSPEAR && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::GREATSPEAR && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("A great spear? You're compensating for something, aren't you?") << endl;
//		}
//		//if the player is using a halberd
//		else if (recieverMainHand1.weaponType == Item::HALBERD && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::HALBERD && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("A halberd? You're going to trip over yourself with that thing!") << endl;
//		}
//		//if the player is using a polehammer
//		else if (recieverMainHand1.weaponType == Item::POLEHAMMER && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::POLEHAMMER && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("A polehammer? What, not brave enough to use a weapon with an entire zip code's reach?") << endl;
//		}
//		//if the player is using a parrying shield
//		else if (recieverMainHand1.weaponType == Item::PARRYSHIELD && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::PARRYSHIELD && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("A parrying shield? Hold on, I'll swing nice and slow for you!") << endl;
//		}
//		//if the player is using a medium shield
//		else if (recieverMainHand1.weaponType == Item::MEDIUMSHIELD && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::MEDIUMSHIELD && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("A medium shield? Fancy yourself a knight, do you?") << endl;
//		}
//		//if the player is using a great shield
//		else if (recieverMainHand1.weaponType == Item::GREATSHIELD && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::GREATSHIELD && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("You know, they say the size of the shield is directly proportional to the size of the coward!") << endl;
//		}
//		//if the player is using a longbow
//		else if (recieverMainHand1.weaponType == Item::LONGBOW && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::LONGBOW && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("Great, an archer. Your cowardice is matched only by the annoyance you cause me.") << endl;
//		}
//		//if the player is using a compound bow
//		else if (recieverMainHand1.weaponType == Item::COMPOUNDBOW && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::COMPOUNDBOW && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("Of course, and now you're just gonna keep running and shooting and running and shooting. It's so boring!") << endl;
//		}
//		//if the player is using a great bow
//		else if (recieverMainHand1.weaponType == Item::GREATBOW && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::GREATBOW && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("What are you hunting with that bloody thing, boulders?") << endl;
//		}
//		//if the player is using a mini crossbow
//		else if (recieverMainHand1.weaponType == Item::MINICROSSBOW && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::MINICROSSBOW && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("A miniature crossbow? What are you hunting, mice?") << endl;
//		}
//		//if the player is using a crossbow
//		else if (recieverMainHand1.weaponType == Item::CROSSBOW && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::CROSSBOW && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("A crossbow? Sure, I'll wait the three business days it will take for you to reload it.") << endl;
//		}
//		//if the player is using a hand ballista
//		else if (recieverMainHand1.weaponType == Item::BALLISTA && recieverMainHand1.hasBeenInitialized ||
//			recieverOffHand1.weaponType == Item::BALLISTA && recieverOffHand1.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("Good lord, are you firing entire logs from that thing?") << endl;
//		}
//		else
//		{
//			getGenericCombatBanter(sender);
//		}
//	}
//	else if (randomNum == 2)
//	{
//		//ARMOR
//		int lightArmorCount = 0;
//		for (int i = 0; i < recieverItems.size(); i++)
//		{
//			if (recieverItems[i].armorType == Item::LEATHER || recieverItems[i].armorType == Item::PADDED || recieverItems[i].armorType == Item::STUDDEDLEATHER)
//			{
//				lightArmorCount++;
//			}
//		}
//		int mediumArmorCount = 0;
//		for (int i = 0; i < recieverItems.size(); i++)
//		{
//			if (recieverItems[i].armorType == Item::CHAIN || recieverItems[i].armorType == Item::LAMELLAR || recieverItems[i].armorType == Item::SCALE)
//			{
//				mediumArmorCount++;
//			}
//		}
//		int heavyArmorCount = 0;
//		for (int i = 0; i < recieverItems.size(); i++)
//		{
//			if (recieverItems[i].armorType == Item::CHAINPLATE || recieverItems[i].armorType == Item::BEASTSCALE || recieverItems[i].armorType == Item::FULLPLATE)
//			{
//				heavyArmorCount++;
//			}
//		}
//		//if the player is wearing no armor
//		if (!recieverHelmet.hasBeenInitialized && !recieverChest.hasBeenInitialized && !recieverArms.hasBeenInitialized && !recieverLegs.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("The madman is wearing nothing! I don't know if you're more brave or stupid.") << endl;
//		}
//		//if the player is wearing light armor
//		else if (lightArmorCount > mediumArmorCount && lightArmorCount > heavyArmorCount)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("Light armor? Couldn't fatiguege even a hint of weight on your body, could you?") << endl;
//		}
//		//if the player is wearing medium armor
//		else if (mediumArmorCount > lightArmorCount && mediumArmorCount > heavyArmorCount)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("So you couldn't decide if you wanted to be fast or durable, so you went with a worse version of both. Good job.") << endl;
//		}
//		//if the player is wearing heavy armor
//		else if (heavyArmorCount > lightArmorCount && heavyArmorCount > mediumArmorCount)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("Heavy armor? You know, they say the thickness of the steel is directly proportional to the thickness of the skull!") << endl;
//		}
//		//if they're wearing a mixture of armor types
//		else if (lightArmorCount > 0 && mediumArmorCount > 0 && heavyArmorCount > 0)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("Did your mother dress you?") << endl;
//		}
//		else
//		{
//			getGenericCombatBanter(sender);
//		}
//	}
//	else if (randomNum == 3)
//	{
//		//POTIONS
//		int healingTally = 0;
//		int fatigueTally = 0;
//		int cureDiseaseTally = 0;
//		for (int i = 0; i < recieverPotions.size(); i++)
//		{
//			if (recieverPotions[i].effects == Potion::HEALING)
//			{
//				healingTally += recieverPotions[i].quantity;
//			}
//			else if (recieverPotions[i].effects == Potion::fatigue)
//			{
//				fatigueTally += recieverPotions[i].quantity;
//			}
//			else if (recieverPotions[i].effects == Potion::CUREDISEASE)
//			{
//				cureDiseaseTally += recieverPotions[i].quantity;
//			}
//		}
//		//if the player has no potions
//		if (healingTally == 0 && fatigueTally == 0 && cureDiseaseTally == 0)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("No potions? Shame, I was running low.") << endl;
//		}
//		//if the player has mainly healing potions
//		else if (healingTally > fatigueTally && healingTally > cureDiseaseTally)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("You're gonna need all those healing potions you're hoarding!") << endl;
//		}
//		//if the player has mainly fatigue potions
//		else if (fatigueTally > healingTally && fatigueTally > cureDiseaseTally)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("fatigue potions? Another bloody wizard. Fantastic!") << endl;
//		}
//		//if the player has mainly cure disease potions
//		else if (cureDiseaseTally > healingTally && cureDiseaseTally > fatigueTally)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("Cure disease potions? Make a habit of covorting with wild animals or something?") << endl;
//		}
//		//if the player has a mix of potions
//		else if (healingTally > 0 && fatigueTally > 0 && cureDiseaseTally > 0)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("What are you, a walking apothecary?") << endl;
//		}
//		else
//		{
//			getGenericCombatBanter(sender);
//		}
//
//	}
//	else if (randomNum == 4)
//	{
//		//TRINKETS
//
//		//if the player has no trinkets
//		if (!recieverAmulet.hasBeenInitialized && !recieverRing1.hasBeenInitialized && !recieverRing2.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("No trinkets? No jewelry? What a let-down!") << endl;
//		}
//		//if the player has an amulet
//		else if (recieverAmulet.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("I'm gonna rip that amulet from your neck!") << endl;
//		}
//		//if the player has a ring
//		else if (recieverRing1.hasBeenInitialized || recieverRing2.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("I sure hope that isn't a wedding ring, I might feel bad about this.") << endl;
//		}
//		//if the player has two rings
//		else if (recieverRing1.hasBeenInitialized && recieverRing2.hasBeenInitialized)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("Two rings? Two times the profit for me.") << endl;
//		}
//		else
//		{
//			getGenericCombatBanter(sender);
//		}
//	}
//	else if (randomNum == 5)
//	{
//		//GOLD
//
//		//if the player has no gold
//		if (reciever.gold == 0)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("Do you not have a single gold piece on you? What a loser!") << endl;
//		}
//		//if the player has a <=200 gold
//		else if (reciever.gold <= 200 && reciever.gold > 0)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("I can hear all that gold in your pockets!") << endl;
//		}
//		//if the player has a <=500 gold
//		else if (reciever.gold <= 500 && reciever.gold > 200)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("You're carrying around a lot of gold, you know. Have you ever heard of a bank?") << endl;
//		}
//		//if the player has a <=1000 gold
//		else if (reciever.gold <= 1000 && reciever.gold > 500)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("How are you even carrying all that gold?") << endl;
//		}
//		//if the player has a >1000 gold
//		else if (reciever.gold > 1000)
//		{
//			cout << dye::light_yellow(sender.name) << ": " << dye::white("I'm gonna retire with all that gold you're carrying!") << endl;
//		}
//		else
//		{
//			getGenericCombatBanter(sender);
//		}
//	}
//}

//void getGenericCombatBanter(Character sender)
//{
//	//fallback generic lines (for debug)
//	int randomNum = (rand() % 9) + 1;
//	switch (randomNum) {
//	case 1:
//	{
//		cout << dye::light_yellow(sender.name) << ": " << dye::white("Well men, we've trained hard, but looking upon the face of our enemy, I fear we needn't... have trained quite so hard.") << endl;
//		break;
//	}
//	case 2:
//	{
//		cout << dye::light_yellow(sender.name) << ": " << dye::white("Look men, look how terrible they are!") << endl;
//		break;
//	}
//	case 3:
//	{
//		cout << dye::light_yellow(sender.name) << ": " << dye::white("Maybe, you should take up FARMING!") << endl;
//		break;
//	}
//	case 4:
//	{
//		cout << dye::light_yellow(sender.name) << ": " << dye::white("You move with the grace of a drunken peasant!") << endl;
//		break;
//	}
//	case 5:
//	{
//		cout << dye::light_yellow(sender.name) << ": " << dye::white("Ahoy, uh, the 'dung covered peasant convention,' is THAT way!") << endl;
//		break;
//	}
//	case 6:
//	{
//		cout << dye::light_yellow(sender.name) << ": " << dye::white("My Nan can fight better than that!") << endl;
//		break;
//	}
//	case 7:
//	{
//		cout << dye::light_yellow(sender.name) << ": " << dye::white("Your mother was a hamster!") << endl;
//		break;
//	}
//	case 8:
//	{
//		cout << dye::light_yellow(sender.name) << ": " << dye::white("Your father smelt of elderberries!") << endl;
//		break;
//	}
//	case 9:
//	{
//		cout << dye::light_yellow(sender.name) << ": " << dye::white("I fart in your general direction!") << endl;
//		break;
//	}
//	}
//}
//
//void enemySharePotion(Character& character, vector<Character>& allies)
//{
//	std::vector<Potion> healingPotions;
//	for (int i = 0; i < character.inventory.potions.size(); i++)
//	{
//		if (character.inventory.potions[i].effects == Potion::HEALING)
//		{
//			healingPotions.push_back(character.inventory.potions[i]);
//		}
//	}
//	std::vector<Potion> fatiguePotions;
//	for (int i = 0; i < character.inventory.potions.size(); i++)
//	{
//		if (character.inventory.potions[i].effects == Potion::fatigue)
//		{
//			fatiguePotions.push_back(character.inventory.potions[i]);
//		}
//	}
//	std::vector<Potion> cureDiseasePotions;
//	for (int i = 0; i < character.inventory.potions.size(); i++)
//	{
//		if (character.inventory.potions[i].effects == Potion::CUREDISEASE)
//		{
//			cureDiseasePotions.push_back(character.inventory.potions[i]);
//		}
//	}
//
//	//check ally health
//	if (!allies.empty() && !healingPotions.empty())
//	{
//		for (int i = 0; i < allies.size(); i++)
//		{
//			if (allies[i].healthPoints <= allies[i].maxHealthPoints * .5)
//			{
//				cout << "=--->" << endl;
//				cout << dye::light_yellow(character.name) << " tosses a healing potion to " << dye::light_yellow(allies[i].name) << endl;
//				allies[i].inventory.addPotion(healingPotions[0]);
//				for (int i = 0; i < character.inventory.potions.size(); i++)
//				{
//					if (character.inventory.potions[i].effects == Potion::HEALING)
//					{
//						character.inventory.potions.erase(character.inventory.potions.begin() + i);
//					}
//				}
//			}
//		}
//	}
//	//check ally fatigue
//	else if (!allies.empty() && !fatiguePotions.empty())
//	{
//		for (int i = 0; i < allies.size(); i++)
//		{
//			if (allies[i].fatiguePoints <= allies[i].maxfatiguePoints * .5)
//			{
//				cout << "=--->" << endl;
//				cout << dye::light_yellow(character.name) << " tosses a fatigue potion to " << dye::light_yellow(allies[i].name) << endl;
//				allies[i].inventory.addPotion(fatiguePotions[0]);
//				character.inventory.potions.erase(character.inventory.potions.begin() + 0);
//				for (int i = 0; i < character.inventory.potions.size(); i++)
//				{
//					if (character.inventory.potions[i].effects == Potion::fatigue)
//					{
//						character.inventory.potions.erase(character.inventory.potions.begin() + i);
//					}
//				}
//			}
//		}
//	}
//	//check ally disease
//}