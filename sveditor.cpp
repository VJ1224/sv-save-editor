#include <iostream>
#include <fstream>
#include <vector>
#include "libs/tinyxml2.cpp"
#include "libs/tinyxml2.h"
#include "libs/json.hpp"

using namespace std;
using namespace tinyxml2;

XMLDocument doc;
XMLElement* root;
XMLElement* player;

void getFile();

string getName();
string getSex();

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
void getFile() {
    doc.LoadFile("data.xml");
    root = doc.FirstChildElement("SaveGame");
    player = root->FirstChildElement("player");
}

string getName() {
    XMLElement* name = player->FirstChildElement("name");
    return name->GetText();
}

string getSex() {
    XMLElement* sex = player->FirstChildElement("isMale");
    if (strcmp(sex->GetText(),"true")) {
        return "Male";
    } else {
        return "Female";
    }
}

string getDate() {
    XMLElement* day = player->FirstChildElement("dayOfMonthForSaveGame");
    XMLElement* season = player->FirstChildElement("seasonForSaveGame");
    XMLElement* year = player->FirstChildElement("yearForSaveGame");

    const char* seasonName;
    int seasonValue = atoi(season->GetText());
    switch(seasonValue) {
        case 1: seasonName = "Spring"; break;
        case 2: seasonName = "Summer"; break;
        case 3: seasonName = "Fall"; break;
        case 4: seasonName = "Winter"; break;
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

string getCurrentMoney() {
    XMLElement* money = player->FirstChildElement("money");
    return money->GetText();

}

string getMoneyEarned() {
    XMLElement* totalMoneyEarned = player->FirstChildElement("totalMoneyEarned");
    return totalMoneyEarned->GetText();
}

string getFarmingLevel() {
    XMLElement* farmingLevel = player->FirstChildElement("farmingLevel");
    return string(farmingLevel->GetText());
}

string getMiningLevel() {
    XMLElement* miningLevel = player->FirstChildElement("miningLevel");
    return string(miningLevel->GetText());
}

string getCombatLevel() {
    XMLElement* combatLevel = player->FirstChildElement("combatLevel");
    return string(combatLevel->GetText());
}

string getForagingLevel() {
    XMLElement* foragingLevel = player->FirstChildElement("foragingLevel");
    return string(foragingLevel->GetText());
}

string getFishingLevel() {
    XMLElement* fishingLevel = player->FirstChildElement("fishingLevel");
    return string(fishingLevel->GetText());
}
}
