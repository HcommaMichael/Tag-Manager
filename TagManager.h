#ifndef TAG_MANAGER_H
#define TAG_MANAGER_H

#include "TagNode.h"
#include <vector>
#include <iostream>

//TagManager class, contains all specified memeber methods + 2 helper methods for handling case insensitivity
//and eliminating redundancy from contains methods.
class TagManager {
public:
	TagManager(vector<string> names);
	void printTagRing();
	void printOutList();
	bool tagRingContains(string name);
	bool outListContains(string name);
	bool isGameOver();
	string winner();
	void tag(string name);
	string nameCleaner(string name);
	bool contains(TagNode* listFront, string name);

//only member variables are the two lists themselves
private:
	TagNode* ringFront = nullptr;
	TagNode* outFront = nullptr;

};

#endif