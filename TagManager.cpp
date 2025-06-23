#include "TagManager.h"

//constructs list from names vector
TagManager::TagManager(vector<string> names){
	if (names.size() == 0) {
		throw "No names in the list!";
	}
	//construct first node outside of the loop to initialize a next ptr so list state can be changed/traversed
	ringFront = new TagNode(names[0], nullptr);

	//attach new nodes of the remaining names to the next ptr of the current node
	TagNode* curr = ringFront;
	for (int i = 1; i < names.size(); i++) {
		curr->next = new TagNode(names[i], nullptr);
		curr = curr->next;
	}
}

//traverses list using curr ptr as to maintain list state, accesses necessary data fields/nodes
void TagManager::printTagRing(){
	TagNode* curr = ringFront;
	while (curr != nullptr) {
		cout << curr->name << " is trying to tag ";
		if (curr->next != nullptr) {
			cout << curr->next->name << endl;
		}
		else {
			cout << ringFront->name << endl;
		}
		curr = curr->next;
	}
}
//same as priting the tag ring, does not access next node, only name & tagger fields of current node
void TagManager::printOutList(){
	TagNode* curr = outFront;
	while (curr != nullptr) {
		cout << curr->name << " was tagged by " << curr->tagger << endl;
		curr = curr->next;
	}
	
}

//helper 1/2, cleans the name typed by the user to match the format of the names in names.txt
//note that this will not work if names are not in First or First Last format, could be modified 
//to make the typed name and the name of the current node being checked all lower, seemed unnecessary 
//since we are only given names.txt
string TagManager::nameCleaner(string name) {
	string result = "";
	for (int i = 0; i < name.length(); i++) {
		if (i == 0 || name[i - 1] == ' ') {
			result += toupper(name[i]);
		}
		else {
			result += tolower(name[i]);
		}
	}
	return result;
}

//implements the shared logic for both tagRingContains and outListContains, accepts additional TagNode*
//parameter to allow both functions to use the same logic without redundant implementation
bool TagManager::contains(TagNode* listFront, string name) {
	string cleanedName = nameCleaner(name);
	TagNode* curr = listFront;
	while (curr != nullptr) {
		if (curr->name == cleanedName) {
			return true;
		}
		curr = curr->next;
	}
	return false;
}

bool TagManager::tagRingContains(string name){
	return contains(ringFront, name);
}

bool TagManager::outListContains(string name){
	return contains(outFront, name);
}

//checks for list size of 1 without storing additional data in member variable
bool TagManager::isGameOver(){
	return ringFront->next == nullptr;
}

//calls isGameOver as check for boolean value of game over
string TagManager::winner(){
	if (isGameOver()) {
		return ringFront->name;
	}
	return "";
}

//main tag cycle logic
void TagManager::tag(string name){
	//checks if the game is over, throws string if true, checks if name is in the ring, throws string is false, game ove takes precedence
	if (isGameOver()) {
		throw "Game Over!";
	}
	else if (!tagRingContains(name)) {
		throw " Not in ring.";
	}
	//cleans the name once at the start of the logic to avoid calling the method, which might have 
	//increased runtime complexity beyond O(N)
	string cleanedName = nameCleaner(name);

	//checks if the first node is the target since this requires slightly different logic
	//if true, stores first node in temp variable, assigns the front to the next node, then traverses to the final node
	//once at the final node, target nodes tagger field is set to the name of the final node, target node is added to the front of the out list
	if (ringFront->name == cleanedName) {
		TagNode* out = ringFront;
		ringFront = ringFront->next;
		TagNode* curr = ringFront;
		while (curr->next != nullptr) {
			curr = curr->next;
		}
		out->tagger = curr->name;
		out->next = outFront;
		outFront = out;
	}
	//similar logic, traverses first to the node right before the target, again stores target node in temp
	//sets target nodes tagger field to be the current nodes name field, adds target node to the front of the out list
	else {
		TagNode* curr = ringFront;
		while (curr->next->name != cleanedName) {
			curr = curr->next;
		}
		TagNode* out = curr->next;
		curr->next = curr->next->next;
		out->tagger = curr->name;
		out->next = outFront;
		outFront = out;
	}
}