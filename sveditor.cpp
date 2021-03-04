#include <iostream>
#include "libs/tinyxml2.cpp"
#include "libs/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

XMLDocument doc;
XMLElement* root;
XMLElement* player;

void setFile(string);
void setName(string);
void setCurrentMoney(string);

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
void setFile(string file) {
    doc.Parse(file.c_str());
    root = doc.FirstChildElement("SaveGame");
    player = root->FirstChildElement("player");
}

void setName(string name) {
    player->FirstChildElement("name")->SetText(name.c_str());
}

void setMoney(string money) {
    player->FirstChildElement("money")->SetText(money.c_str());
}

string getName() {
    return player->FirstChildElement("name")->GetText();
}

string getSex() {
    XMLElement* sex = player->FirstChildElement("isMale");
    if (strcmp(sex->GetText(),"true") == 0) {
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

string getCurrentMoney() {
    return player->FirstChildElement("money")->GetText();

}

string getMoneyEarned() {
    return player->FirstChildElement("totalMoneyEarned")->GetText();
}

string getFarmingLevel() {
    return player->FirstChildElement("farmingLevel")->GetText();
}

string getMiningLevel() {
    return player->FirstChildElement("miningLevel")->GetText();
}

string getCombatLevel() {
    return player->FirstChildElement("combatLevel")->GetText();
}

string getForagingLevel() {
    return player->FirstChildElement("foragingLevel")->GetText();
}

string getFishingLevel() {
    return player->FirstChildElement("fishingLevel")->GetText();
}
}
