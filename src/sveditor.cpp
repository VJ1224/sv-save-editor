#include <vector> 
#include <string> 
#include <algorithm> 
#include <sstream> 
#include <iterator> 
#include <iostream> 
#include "libs/tinyxml2.cpp"
#include "libs/tinyxml2.h"
#include "libs/crow_all.h"

using namespace std;
using namespace tinyxml2;

namespace sveditor2 {
bool validateFile(string file) {
    XMLDocument doc;
    doc.Parse(file.c_str());

    XMLElement* root = doc.FirstChildElement("SaveGame");
    if (root == NULL) {
        return false;
    }

    XMLElement* player = root->FirstChildElement("player");
    if (player == NULL) {
        return false;
    }

    return true;
}

string getPlayerSex(XMLElement* player) {
    XMLElement* sex = player->FirstChildElement("isMale");
    if (strcmp(sex->GetText(),"true") == 0) {
        return "Male";
    } else {
        return "Female";
    }
}

string getPlayerAnimal(XMLElement* player) {
    XMLElement* animal = player->FirstChildElement("catPerson");
    if (strcmp(animal->GetText(),"true") == 0) {
        return "Cat";
    } else {
        return "Dog";
    }
}

string getDate(XMLElement* player) {
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

string getPlaytime(XMLElement* player) {
    XMLElement* millisecondsPlayed = player->FirstChildElement("millisecondsPlayed");

    long milli = atol(millisecondsPlayed->GetText());

    int seconds = milli / 1000;

    int minutes = seconds / 60;
    seconds %= 60;

    int hours = minutes / 60;
    minutes %= 60;

    return to_string(hours) + "h " + to_string(minutes) + "m " + to_string(seconds) + "s";
}

string getPlayerAttribute(XMLElement* player, const char* attr) {
    return player->FirstChildElement(attr)->GetText();
}

string getExperiencePoints(XMLElement* player, const char* skill) {
    XMLElement *expPoints = player->FirstChildElement("experiencePoints");
    XMLElement* child = expPoints->FirstChildElement("int");

    for (int i = 0; i < 5; i++) {
        if (strcmp(skill, "farming") == 0 && i == 0) {
            return child->GetText();
        } else if (strcmp(skill, "fishing") == 0 && i == 1) {
            return child->GetText();
        } else if (strcmp(skill, "foraging") == 0 && i == 2) {
            return child->GetText();
        } else if (strcmp(skill, "mining") == 0 && i == 3) {
            return child->GetText();
        } else if (strcmp(skill, "combat") == 0 && i == 4) {
            return child->GetText();
        }

        child = child->NextSiblingElement("int");
    }

    return "0";
}

string getProfession(XMLElement* player) {
    vector<string> profs;
    XMLElement*  professions = player->FirstChildElement("professions");
    XMLElement* child = professions->FirstChildElement("int");
    
    while (child != NULL) {
        const char* val = child->GetText();
        switch(atoi(val)) {
            case 0: profs.push_back("Rancher"); break;
            case 1: profs.push_back("Tiller"); break;
            case 2: profs.push_back("Coopmaster"); break;
            case 3: profs.push_back("Shepherd"); break;
            case 4: profs.push_back("Artisan"); break;
            case 5: profs.push_back("Agriculturist"); break;
            case 6: profs.push_back("Fisher"); break;
            case 7: profs.push_back("Trapper"); break;
            case 8: profs.push_back("Angler"); break;
            case 9: profs.push_back("Pirate"); break;
            case 10: profs.push_back("Mariner"); break;
            case 11: profs.push_back("Luremaster"); break;
            case 12: profs.push_back("Forester"); break;
            case 13: profs.push_back("Gatherer"); break;
            case 14: profs.push_back("Lumberjack"); break;
            case 15: profs.push_back("Tapper"); break;
            case 16: profs.push_back("Botanist"); break;
            case 17: profs.push_back("Tracker"); break;
            case 18: profs.push_back("Miner"); break;
            case 19: profs.push_back("Geologist"); break;
            case 20: profs.push_back("Blacksmith"); break;
            case 21: profs.push_back("Prospector"); break;
            case 22: profs.push_back("Excavator"); break;
            case 23: profs.push_back("Gemologist"); break;
            case 24: profs.push_back("Fighter"); break;
            case 25: profs.push_back("Scout"); break;
            case 26: profs.push_back("Brute"); break;
            case 27: profs.push_back("Defender"); break;
            case 28: profs.push_back("Acrobat"); break;
            case 29: profs.push_back("Desperado"); break;
        }
        
        child = child->NextSiblingElement("int");
    }

    ostringstream vts; 
    if (!profs.empty()) { 
        copy(profs.begin(), profs.end()-1, ostream_iterator<string>(vts, ", ")); 
        vts << profs.back(); 
    } 

    return vts.str();
}

string getFile(string file) {
    XMLDocument doc;
    doc.Parse(file.c_str());

    XMLElement* root = doc.FirstChildElement("SaveGame");
    XMLElement* player = root->FirstChildElement("player");

    crow::json::wvalue obj;

    obj["name"] = getPlayerAttribute(player, "name");
    obj["farmName"] = getPlayerAttribute(player, "farmName");

    obj["favoriteThing"] = getPlayerAttribute(player, "favoriteThing");
    obj["currentMoney"] = getPlayerAttribute(player, "money");
    obj["moneyEarned"] = getPlayerAttribute(player, "totalMoneyEarned");
    obj["maxHealth"] = getPlayerAttribute(player, "maxHealth");
    obj["maxStamina"] = getPlayerAttribute(player, "maxStamina");

    obj["sex"] = getPlayerSex(player);
    obj["animal"] = getPlayerAnimal(player);
    obj["date"] = getDate(player);
    obj["playtime"] = getPlaytime(player);

    obj["skills"]["farmingLevel"] = getPlayerAttribute(player, "farmingLevel");
    obj["skills"]["combatLevel"] = getPlayerAttribute(player, "combatLevel");
    obj["skills"]["miningLevel"] = getPlayerAttribute(player, "miningLevel");
    obj["skills"]["foragingLevel"] = getPlayerAttribute(player, "foragingLevel");
    obj["skills"]["fishingLevel"] = getPlayerAttribute(player, "fishingLevel");

    obj["skills"]["farmingExp"] = getExperiencePoints(player, "farming");
    obj["skills"]["combatExp"] = getExperiencePoints(player, "combat");
    obj["skills"]["miningExp"] = getExperiencePoints(player, "mining");
    obj["skills"]["foragingExp"] = getExperiencePoints(player, "foraging");
    obj["skills"]["fishingExp"] = getExperiencePoints(player, "fishing");

    obj["professions"] = getProfession(player);

    return obj.dump();
}

void setPlayerAttribute(XMLElement* player, const char* attr, string value) {
    player->FirstChildElement(attr)->SetText(value.c_str());
}

void setExperiencePoints(XMLElement* player, const char* skill, string level) {
    XMLElement *expPoints = player->FirstChildElement("experiencePoints");
    XMLElement* child = expPoints->FirstChildElement("int");
    const char* exp;

    if (strcmp(level.c_str(), "1") == 0) exp = "100";
    if (strcmp(level.c_str(), "2") == 0) exp = "380";
    if (strcmp(level.c_str(), "3") == 0) exp = "770";
    if (strcmp(level.c_str(), "4") == 0) exp = "1300";
    if (strcmp(level.c_str(), "5") == 0) exp = "2150";
    if (strcmp(level.c_str(), "6") == 0) exp = "3300";
    if (strcmp(level.c_str(), "7") == 0) exp = "4800";
    if (strcmp(level.c_str(), "8") == 0) exp = "6900";
    if (strcmp(level.c_str(), "9") == 0) exp = "10000";
    if (strcmp(level.c_str(), "10") == 0) exp = "15000";

    for (int i = 0; i < 5; i++) {
        if (strcmp(skill, "farming") == 0 && i == 0) {
            setPlayerAttribute(player, "farmingLevel", level);
            child->SetText(exp);
            break;
        } else if (strcmp(skill, "fishing") == 0 && i == 1) {
            setPlayerAttribute(player, "fishingLevel", level);
            child->SetText(exp);
            break;
        } else if (strcmp(skill, "foraging") == 0 && i == 2) {
            setPlayerAttribute(player, "foragingLevel", level);
            child->SetText(exp);
            break;
        } else if (strcmp(skill, "mining") == 0 && i == 3) {
            setPlayerAttribute(player, "miningLevel", level);
            child->SetText(exp);
            break;
        } else if (strcmp(skill, "combat") == 0 && i == 4) {
            setPlayerAttribute(player, "combatLevel", level);
            child->SetText(exp);
            break;
        }
        
        child = child->NextSiblingElement("int");
    }
}

void addProfession(XMLElement* player, string prof) {
    XMLElement*  professions = player->FirstChildElement("professions");
    XMLElement* child = professions->InsertNewChildElement("int");
    child->SetText(prof.c_str());
}

string editFile(string file, crow::json::rvalue data) {
    XMLDocument doc;
    doc.Parse(file.c_str());

    XMLElement* root = doc.FirstChildElement("SaveGame");
    XMLElement* player = root->FirstChildElement("player");
    
    if(data.has("name")) setPlayerAttribute(player, "name", data["name"].s());
    if(data.has("farmName")) setPlayerAttribute(player, "farmName", data["farmName"].s());
    if(data.has("favoriteThing")) setPlayerAttribute(player, "favoriteThing", data["favoriteThing"].s());

    if(data.has("money")) setPlayerAttribute(player, "money", data["money"].s());
    if(data.has("health")) setPlayerAttribute(player, "maxHealth", data["health"].s());
    if(data.has("stamina")) setPlayerAttribute(player, "maxStamina", data["stamina"].s());

    if(data.has("farming")) setExperiencePoints(player, "farming", data["farming"].s());
    if(data.has("mining")) setExperiencePoints(player, "mining", data["mining"].s());
    if(data.has("combat")) setExperiencePoints(player, "combat", data["combat"].s());
    if(data.has("foraging")) setExperiencePoints(player, "foraging", data["foraging"].s());
    if(data.has("fishing")) setExperiencePoints(player, "fishing", data["fishing"].s());

    if (data.has("sex")) {
        string sex = data["sex"].s();
        if (strcmp(sex.c_str(), "male") == 0) {
            setPlayerAttribute(player, "isMale", "true");
        } else {
            setPlayerAttribute(player, "isMale", "false");
        }
    }

    if (data.has("animal")) {
        string animal = data["animal"].s();
        if (strcmp(animal.c_str(), "cat") == 0) {
            setPlayerAttribute(player, "catPerson", "true");
        } else {
            setPlayerAttribute(player, "catPerson", "false");
        }
    }

    if (data.has("profession")) {
        addProfession(player, data["profession"].s());
    }

    XMLPrinter printer;
    doc.Accept(&printer);
    return printer.CStr();
}
}