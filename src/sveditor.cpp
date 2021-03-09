#include <vector> 
#include <string> 
#include <algorithm> 
#include <sstream> 
#include <iterator> 
#include <iostream> 
#include "libs/tinyxml2.cpp"
#include "libs/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

namespace sveditor {

XMLDocument doc;
XMLElement* root = NULL;
XMLElement* player = NULL;
string filename;

void clearFile() {
    doc.Clear();
    root = NULL;
    player = NULL;
}

void setFile(string file) {
    doc.Parse(file.c_str());

    if (doc.Error()) {
        clearFile();
        return;
    }

    root = doc.FirstChildElement("SaveGame");
    if (root == NULL) {
        clearFile();
        return;
    }

    player = root->FirstChildElement("player");
    if (player == NULL) {
        clearFile();   
    }
}

void setFileName(string name) {
    filename = name;
}

string getFileName() {
    return filename;
}

string downloadFile() {
    XMLPrinter printer;
    doc.Accept(&printer);
    return printer.CStr();
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

string getProfession() {
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

void setPlayerAttribute(const char* attr, string value) {
    player->FirstChildElement(attr)->SetText(value.c_str());
}

void setSex(string sex) {
    if (strcmp(sex.c_str(), "male") == 0) {
        setPlayerAttribute("isMale", "true");
    } else {
        setPlayerAttribute("isMale", "false");
    }
}

void setAnimal(string animal) {
    if (strcmp(animal.c_str(), "cat") == 0) {
        setPlayerAttribute("catPerson", "true");
    } else {
        setPlayerAttribute("catPerson", "false");
    }
}

void setExperiencePoints(const char* skill, int level) {
    XMLElement *expPoints = player->FirstChildElement("experiencePoints");
    XMLElement* child = expPoints->FirstChildElement("int");
    const char* exp;

    switch(level) {
        case 1: exp = "100"; break;
        case 2: exp = "380"; break;
        case 3: exp = "770"; break;
        case 4: exp = "1300"; break;
        case 5: exp = "2150"; break;
        case 6: exp = "3300"; break;
        case 7: exp = "4800"; break;
        case 8: exp = "6900"; break;
        case 9: exp = "10000"; break;
        case 10: exp = "15000"; break;
    }
    
    for (int i = 0; i < 5; i++) {
        if (strcmp(skill, "farming") == 0 && i == 0) {
            setPlayerAttribute("farmingLevel", to_string(level));
            child->SetText(exp);
            break;
        } else if (strcmp(skill, "fishing") == 0 && i == 1) {
            setPlayerAttribute("fishingLevel", to_string(level));
            child->SetText(exp);
            break;
        } else if (strcmp(skill, "foraging") == 0 && i == 2) {
            setPlayerAttribute("foragingLevel", to_string(level));
            child->SetText(exp);
            break;
        } else if (strcmp(skill, "mining") == 0 && i == 3) {
            setPlayerAttribute("miningLevel", to_string(level));
            child->SetText(exp);
            break;
        } else if (strcmp(skill, "combat") == 0 && i == 4) {
            setPlayerAttribute("combatLevel", to_string(level));
            child->SetText(exp);
            break;
        }
        
        child = child->NextSiblingElement("int");
    }
}

void addProfession(string prof) {
    XMLElement*  professions = player->FirstChildElement("professions");
    XMLElement* child = professions->InsertNewChildElement("int");
    child->SetText(prof.c_str());
}
}
