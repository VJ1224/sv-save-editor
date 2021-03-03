#include "sveditor.cpp"
#include "tools.hpp"
#include "libs/crow_all.h"

crow::json::wvalue toJSON();

int main() {
    crow::SimpleApp app;
    crow::mustache::set_base(".");
    
    CROW_ROUTE(app, "/")([](){
        return crow::mustache::load("html/index.html").render();
    });

    CROW_ROUTE(app, "/profile")([](){
        return toJSON();
    });

    CROW_ROUTE(app, "/upload").methods("POST"_method)([](const crow::request& req){
        string content = req.body;
        content = content.substr(8);
        sveditor::setFile(content);
        return 1;
    });

    app.port(18080).multithreaded().run();

    // release: g++ main.cpp -lpthread -lboost_system -lz -o sveditor.out
    // debug: g++ main.cpp -ggdb -lpthread -lboost_system -lz -D CROW_ENABLE_DEBUG -o sveditor.out
}

crow::json::wvalue toJSON() {
    crow::json::wvalue obj;
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

    return obj;
}