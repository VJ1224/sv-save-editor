#include <iostream>
#include "libs/tinyxml2.cpp"
#include "libs/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

void setFile(string);
void setPlayerAttribute(string, string);

bool fileLoaded();
string getName();
string getSex();
string getAnimal();

string getCurrentMoney();
string getMoneyEarned();

string getPlaytime();
string getDate();

string getFarmingLevel();
string getMiningLevel();
string getCombatLevel();
string getFishingLevel();
string getForagingLevel();

namespace sveditor {

XMLDocument doc;
XMLElement* root = NULL;
XMLElement* player = NULL;

void setFile(string file) {
    doc.Parse(file.c_str());
    root = doc.FirstChildElement("SaveGame");
    player = root->FirstChildElement("player");
}

void setPlayerAttribute(const char* attr, string value) {
    player->FirstChildElement(attr)->SetText(value.c_str());
}

string getSex() {
    XMLElement* sex = player->FirstChildElement("isMale");
    if (strcmp(sex->GetText(),"true") == 0) {
        return "Male";
    } else {
        return "Female";
    }
}

string getAnimal() {
    XMLElement* animal = player->FirstChildElement("catPerson");
    if (strcmp(animal->GetText(),"true") == 0) {
        return "Cat";
    } else {
        return "Dog";
    }
}

string getDate() {
    XMLElement* day = player->FirstChildElement("dayOfMonthForSaveGame");
    XMLElement* season = player->FirstChildElement("seasonForSaveGame");
    XMLElement* year = player->FirstChildElement("yearForSaveGame");

    const char* seasonName;
    int seasonValue = atoi(season->GetText());
    switch(seasonValue) {
        case 0: seasonName = "Spring"; break;
        case 1: seasonName = "Summer"; break;
        case 2: seasonName = "Fall"; break;
        case 3: seasonName = "Winter"; break;
    }

    return "Day " + string(day->GetText()) + " of " + seasonName + ", Year " + year->GetText();
}

string getPlaytime() {
    XMLElement* millisecondsPlayed = player->FirstChildElement("millisecondsPlayed");

    long milli = atol(millisecondsPlayed->GetText());

    int seconds = milli / 1000;
    milli %= 1000;

    int minutes = seconds / 60;
    seconds %= 60;

    int hours = minutes / 60;
    minutes %= 60;

    return to_string(hours) + "h " + to_string(minutes) + "m " + to_string(seconds) + "s";
}

string getPlayerAttribute(const char* attr) {
    return player->FirstChildElement(attr)->GetText();
}
}
