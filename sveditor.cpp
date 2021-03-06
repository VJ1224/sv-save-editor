#include <iostream>
#include "libs/tinyxml2.cpp"
#include "libs/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

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

    int minutes = seconds / 60;
    seconds %= 60;

    int hours = minutes / 60;
    minutes %= 60;

    return to_string(hours) + "h " + to_string(minutes) + "m " + to_string(seconds) + "s";
}

string getPlayerAttribute(const char* attr) {
    return player->FirstChildElement(attr)->GetText();
}

string getExperiencePoints(const char* skill) {
    XMLElement *expPoints = player->FirstChildElement("experiencePoints");
    XMLElement* child = expPoints->FirstChildElement("int");
    string exp[5] = {""};
    
    for (int i = 0; i < 5; i++) {
        exp[i] = child->GetText();
        child = child->NextSiblingElement("int");
    }

    if (strcmp(skill, "farming") == 0) {
        return exp[0];
    } else if (strcmp(skill, "fishing") == 0) {
        return exp[1];
    } else if (strcmp(skill, "foraging") == 0) {
        return exp[2];
    } else if (strcmp(skill, "mining") == 0) {
        return exp[3];
    } else if (strcmp(skill, "combat") == 0) {
        return exp[4];
    }

    return "0";
}
}
