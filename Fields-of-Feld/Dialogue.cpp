#include "Dialogue.h"

Dialogue::Dialogue()
{

}

Dialogue::Dialogue(Character* speaker, Character* target, std::string text, std::string emotion, float gravity, int coolDown) 
	: speaker(speaker), target(target), text(text), emotion(emotion), gravity(gravity), coolDown(coolDown), effect(nullptr), condition(nullptr)
{

}

Dialogue::~Dialogue()
{

}

void Dialogue::playConversation() {
	if (!isAvailable()) {
		return;
	}

	//Print the dialogue
	std::cout << "=--->" << std::endl;
	std::cout << dye::light_yellow(" ") << dye::light_yellow(speaker->name) << ": " << text << std::endl;

	//Triggers the effect, if available
	if (effect) {
		effect();
	}

	//Trigger the responses, if available
	if (!responses.empty()) {
		for (int i = 0; i < responses.size(); i++) {
			std::cout << "=--->" << std::endl;
			std::cout << dye::light_yellow(" ") << dye::light_yellow(i + 1) << dye::light_yellow(") ") << responses[i].text << std::endl;
		}

		//Input validation
		int choice;
		do
		{
			std::cout << "=--->" << std::endl;
			std::cout << dye::light_yellow(" Respond:");
			std::cin >> choice;
			if (std::cin.fail() || choice < 1 || choice > responses.size())
			{
				std::cout << "=--->" << std::endl;
				std::cout << dye::white(" Invalid choice. Please try again.") << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
		} while (choice < 1 || choice > responses.size());

		responses[choice - 1].playConversation();
	}
	else
	{
		std::cout << "=--->" << std::endl;
		std::cout << dye::light_yellow(" ") << dye::light_yellow(target->name) << ": " << "There's nothing left to say." << std::endl;
	}
	
}

void Dialogue::playQuip() {
	if (!isAvailable()) {
		return;
	}
	//Print the dialogue
	std::cout << "=--->" << std::endl;
	std::cout << dye::light_yellow(" ") << dye::light_yellow(speaker->name) << ": " << text << std::endl;
	//Triggers the effect, if available
	if (effect) {
		effect();
	}
}
//Check if dialogue is available
bool Dialogue::isAvailable() const {
	return condition ? condition() : true;
}

//Add a response to the dialogue to allow for branching dialogue
void Dialogue::addResponse(const Dialogue& response) {
	responses.push_back(response);
}

//Set a condition for the dialogue to play
void Dialogue::setCondition(std::function<bool()> condition){
	this->condition = condition;
}

//Set an effect to trigger when the dialogue is played
void Dialogue::setEffect(std::function<void()> effect) {
	this->effect = effect;
}