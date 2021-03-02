#include "sveditor.cpp"
#include "tools.hpp"
#include "libs/crow_all.h"

string toJSON();

int main() {
    sveditor::getFile();
    crow::SimpleApp app;
    
    CROW_ROUTE(app, "/")([](){
        return "Hello " + sveditor::getName();
    });

    CROW_ROUTE(app, "/profile")([](){
        return toJSON();
    });

    app.port(18080).multithreaded().run();
}

string toJSON() {
    json::JSON obj;
    obj["name"] = sveditor::getName();
    obj["sex"] = sveditor::getSex();
    obj["date"] = sveditor::getDate();
    obj["playtime"] = sveditor::getPlaytime();
    obj["currentMoney"] = sveditor::getCurrentMoney();
    obj["moneyEarned"] = sveditor::getMoneyEarned();
    obj["skills"]["farmingLevel"] = sveditor::getFarmingLevel();
    obj["skills"]["combatLevel"] = sveditor::getCombatLevel();
    obj["skills"]["miningLevel"] = sveditor::getMiningLevel();
    obj["skills"]["foragingLevel"] = sveditor::getForagingLevel();
    obj["skills"]["fishingLevel"] = sveditor::getFishingLevel();

    return obj.dump();
}