#include "sveditor.cpp"
#include "tools.hpp"
#include "libs/crow_all.h"

crow::json::wvalue toJSON();

int main() {
    crow::SimpleApp app;
    crow::mustache::set_base(".");
    
    CROW_ROUTE(app, "/")([](){
        return crow::mustache::load("pages/index.html").render();
    });

    CROW_ROUTE(app, "/profile")([](){
        if (sveditor::root == NULL) return crow::mustache::load("pages/index.html").render();

        crow::mustache::context ctx = toJSON();
        return crow::mustache::load("pages/profile.html").render(ctx);
    });

    CROW_ROUTE(app, "/upload").methods("POST"_method)([](const crow::request& req){
        sveditor::setFile(req.body);
        return 200;
    });

    CROW_ROUTE(app, "/edit").methods("POST"_method)([](const crow::request& req){
        if (sveditor::root == NULL) return 400;
        
        crow::json::rvalue data = crow::json::load(req.body);
        if(!data) return 400;

        if (data.has("name")) sveditor::setPlayerAttribute("name", data["name"].s());
        if (data.has("money")) sveditor::setPlayerAttribute("money", data["money"].s());
        if (data.has("sex")) sveditor::setPlayerAttribute("isMale", data["sex"].s());
        if (data.has("animal")) sveditor::setPlayerAttribute("catPerson", data["animal"].s());

        return 200;
    });

    app.port(18080).multithreaded().run();

    // release: g++ main.cpp -lpthread -lboost_system -lz -o sveditor.out
    // debug: g++ main.cpp -ggdb -lpthread -lboost_system -lz -D CROW_ENABLE_DEBUG -o sveditor.out
}

crow::json::wvalue toJSON() {
    crow::json::wvalue obj;
    obj["sex"] = sveditor::getSex();
    obj["animal"] = sveditor::getAnimal();
    obj["date"] = sveditor::getDate();
    obj["playtime"] = sveditor::getPlaytime();

    obj["name"] = sveditor::getPlayerAttribute("name");
    obj["currentMoney"] = sveditor::getPlayerAttribute("money");
    obj["moneyEarned"] = sveditor::getPlayerAttribute("totalMoneyEarned");
    obj["skills"]["farmingLevel"] = sveditor::getPlayerAttribute("farmingLevel");
    obj["skills"]["combatLevel"] = sveditor::getPlayerAttribute("combatLevel");
    obj["skills"]["miningLevel"] = sveditor::getPlayerAttribute("miningLevel");
    obj["skills"]["foragingLevel"] = sveditor::getPlayerAttribute("foragingLevel");
    obj["skills"]["fishingLevel"] = sveditor::getPlayerAttribute("fishingLevel");

    return obj;
}