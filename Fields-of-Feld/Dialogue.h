#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <string>
#include <vector>
#include <optional>
#include <functional>
#include "color.hpp"
#include "Character.h"

class Dialogue
{
public:
	Dialogue();
	Dialogue(std::shared_ptr<Character> speaker, std::shared_ptr<Character> target, std::string text = "DEFAULT", std::string emotion = "DEFAULT", float gravity = 1.0f, int coolDown = 1.0f);
	~Dialogue();
	
	void playConversation();
	void playQuip();
	bool isAvailable() const;

	void addResponse(const Dialogue& response);
	void setCondition(std::function<bool()> condition);
	void setEffect(std::function<void()> effect);

private:
	std::shared_ptr<Character> speaker = nullptr;
	std::shared_ptr<Character> target = nullptr;
	std::string text = "DEFAULT TEXT PLS CHANGE";
	float gravity = 1.0f; //chance of dialogue playing over other options
	std::vector<Dialogue> responses; //responses to the dialogue
	std::function<bool()> condition; //condition for the dialogue to play
	std::vector<std::string> tags; //tags for organization
	std::string emotion = "NO EMOTION PLS CHANGE"; //emotion of the speaker
	std::function<void()> effect; //effect triggered when dialogue is played
	int coolDown = 0; //turns before the dialogue can be played again
};

#endif // !DIALOGUE_H