#include <iostream>
#include <fstream>
#include <vector>
#include "tinyxml2.cpp"
#include "tinyxml2.h"
#include "tools.hpp"

using namespace std;
using namespace tinyxml2;
using namespace tools;


XMLDocument doc;
XMLElement* root;
XMLElement* player;

void printFarmer();
void printDate();
void printMoney();
void printPlaytime();
void printSkills();

int main(void)
{
    cout << endl << "Stardew Valley" << endl;
   
    doc.LoadFile("data.xml");
    root = doc.FirstChildElement("SaveGame");
    player = root->FirstChildElement("player");
    
    printFarmer();
    printPlaytime();
    printDate();
    printMoney();
    printSkills();
        
    return 0;
}

void printFarmer() {
    XMLElement* name = player->FirstChildElement("name");
    cout << "Name: " << name->GetText() << endl;

    XMLElement* sex = player->FirstChildElement("isMale");
    if (sex->GetText() == "true") {
        cout << "Sex: Male" << endl << endl;
    } else {
        cout << "Sex: Female" << endl << endl;
    }
}


void printDate() {
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

    cout << "Date: " << "Day " << day->GetText() << " of " << seasonName << ", Year " << year->GetText() << endl << endl;
}

void printPlaytime() {
    XMLElement* millisecondsPlayed = player->FirstChildElement("millisecondsPlayed");
    
    long milli = atol(millisecondsPlayed->GetText());

    int seconds = milli / 1000;
    milli %= 1000;

    int minutes = seconds / 60;
    seconds %= 60;

    int hours = minutes / 60;
    minutes %= 60;

    cout << "Playtime: " << hours << "h " << minutes << "m " << seconds << "s" << endl << endl;
}

void printMoney() {
    XMLElement* money = player->FirstChildElement("money");
    cout << "Current Money: " << formatNumber(money->GetText()) << "g" << endl;

    XMLElement* totalMoneyEarned = player->FirstChildElement("totalMoneyEarned");
    cout << "Total Money Earned: " << formatNumber(totalMoneyEarned->GetText()) << "g\n" << endl;
}



void printSkills() {
    XMLElement* farmingLevel = player->FirstChildElement("farmingLevel");
    XMLElement* miningLevel = player->FirstChildElement("miningLevel");
    XMLElement* combatLevel = player->FirstChildElement("combatLevel");
    XMLElement* foragingLevel = player->FirstChildElement("foragingLevel");
    XMLElement* fishingLevel = player->FirstChildElement("fishingLevel");

    cout << "Skills:" << endl;
    cout << "Farming: Lvl " << farmingLevel->GetText() << endl; 
    cout << "Mining: Lvl " << miningLevel->GetText() << endl; 
    cout << "Combat: Lvl " << combatLevel->GetText() << endl; 
    cout << "Foraging: Lvl " << foragingLevel->GetText() << endl; 
    cout << "Fishing: Lvl " << fishingLevel->GetText() << endl; 
}