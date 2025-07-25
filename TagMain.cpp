// CS 133, Project 3: Tag
// Instructor-provided testing program.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <ctime>
#include <algorithm>
#include <cstdlib>

#include "TagManager.h"

using namespace std;
/**
 * TagMain is the main client program for tag game management.
 * It reads names from a file names.txt, shuffles them, and uses them to
 * start the game.  The user is asked for the name of the next person tagged
 * until the game is over.
 */

/** input file name from which to read data */
const string INPUT_FILENAME = "names.txt";

/** true for different results every run; false for predictable results */
const bool RANDOM = true;
    
/**
 * If not random, use this value to guide the sequence of numbers
 * that will be generated by random.
 */
const int SEED = 42;



// takes a reference to a string and removes all whitespace before the first
// non-whitespace character and removes all whitespace after the last 
// non-whitespace character. If the string only contains whitespace it will be 
// empty after it is passed to this function.
// Assumes that the passed in string is not null.
void trim(string& word) {
    // count how many whitespace characters are at the beginning
    int count = 0;
    while(isspace(word[count])) {
        count++;
    }
    // remove that many characters
    word.erase(0, count);

    // count how many whitespace characters are at the end
    count = word.length() - 1;
    while(isspace(word[count])) {
        count--;
    }
    count++;
    // remove the ending whitespace characters
    word.erase(count, word.length() - count);
}


/**
 * Handles the details of recording one tagging.  Shows the current tag
 * ring and out list to the user, prompts for a name and records the
 * tag if the name is legal.
 */
void oneTag(TagManager& manager) {
    // print both linked lists
    cout << "Current tag ring:" << endl;
    manager.printTagRing();
    cout << endl << "Current out list:" << endl;
    manager.printOutList();
    
    // prompt for next person to tag
    cout << endl;
    cout << "next person tagged? ";
    string name;
    getline(cin, name);
    trim(name);
    cout << endl;

    // tag the person, if possible
    if (manager.outListContains(name)) {
        cout << name << " is already out." << endl;
    } else if (!manager.tagRingContains(name)) {
        cout << "Unknown person." << endl;
    } else {
        manager.tag(name);
    }
    cout << endl;
}


int main() {
    // open input and make sure it exists
    ifstream input(INPUT_FILENAME);
    if (!input.good()) {
        cout << "Required input file not found; exiting." << endl << INPUT_FILENAME << endl;
        return 1;
    }
    
    // read names into a set to eliminate duplicates
    set<string> names;
    string name;
    while (getline(input, name)) {
        trim(name);
        if (name.length() > 0) {
            names.insert(name);
        }
    }

    // transfer to a vector, shuffle and build a TagManager
    vector<string> nameList (names.begin(), names.end());
    // seed random depending on the RANDOM variable
    (RANDOM) ? srand(time(0)) : srand(SEED);
    random_shuffle (nameList.begin(), nameList.end());
    TagManager manager (nameList);

    // prompt the user for tagged players until the game is over
    while (!manager.isGameOver()) {
        oneTag(manager);
    }

    // report who won
    cout << "Game was won by " << manager.winner() << endl;
    cout << "Final graveyard is as follows:" << endl;
    manager.printOutList();
    return 0;
}

