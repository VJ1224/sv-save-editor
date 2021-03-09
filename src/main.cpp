#include "sveditor.cpp"
#include "tools.hpp"
#include "libs/crow_all.h"

crow::json::wvalue toJSON();

int main()
{
    crow::SimpleApp app;
    crow::mustache::set_base(".");

    CROW_ROUTE(app, "/")
    ([]() {
        return crow::mustache::load("pages/index.html").render();
    });

    CROW_ROUTE(app, "/profile")
    ([]() {
        if (sveditor::root == NULL)
            return crow::mustache::load("pages/index.html").render();

        crow::mustache::context ctx = toJSON();
        return crow::mustache::load("pages/profile.html").render(ctx);
    });

    CROW_ROUTE(app, "/download")
    ([]() {
        if (sveditor::root == NULL)
            return crow::mustache::load("pages/index.html").render();

        return sveditor::downloadFile();
    });

    CROW_ROUTE(app, "/upload").methods("POST"_method)
    ([](const crow::request &req) {
        sveditor::setFile(req.body);
        return 200;
    });

    CROW_ROUTE(app, "/filename").methods("POST"_method)
    ([](const crow::request &req) {
        sveditor::setFileName(req.body);
        return 200;
    });

    CROW_ROUTE(app, "/edit").methods("POST"_method)
    ([](const crow::request &req) {
        if (sveditor::root == NULL)
            return 400;

        crow::json::rvalue data = crow::json::load(req.body);
        if (!data)
            return 400;

        sveditor::setPlayerAttribute("name", data["name"].s());
        sveditor::setPlayerAttribute("farmName", data["farmName"].s());
        sveditor::setPlayerAttribute("favoriteThing", data["favoriteThing"].s());

        sveditor::setPlayerAttribute("money", data["money"].s());
        sveditor::setPlayerAttribute("maxHealth", data["health"].s());
        sveditor::setPlayerAttribute("maxStamina", data["stamina"].s());

        sveditor::setExperiencePoints("farming", stoi(data["farming"].s()));
        sveditor::setExperiencePoints("mining", stoi(data["mining"].s()));
        sveditor::setExperiencePoints("combat", stoi(data["combat"].s()));
        sveditor::setExperiencePoints("foraging", stoi(data["foraging"].s()));
        sveditor::setExperiencePoints("fishing", stoi(data["fishing"].s()));

        if(data.has("sex")) sveditor::setSex(data["sex"].s());
        if(data.has("animal")) sveditor::setAnimal(data["animal"].s());
        if(data.has("profession")) sveditor::addProfession(data["profession"].s());

        return 200;
    });

    app.loglevel(crow::LogLevel::WARNING);
    app.port(18080).multithreaded().run();

    // g++ main.cpp -lpthread -lboost_system -lz -o ../build/sveditor.out
}

crow::json::wvalue toJSON()
{
    crow::json::wvalue obj;
    obj["filename"] = sveditor::getFileName();

    obj["sex"] = sveditor::getSex();
    obj["animal"] = sveditor::getAnimal();
    obj["date"] = sveditor::getDate();
    obj["playtime"] = sveditor::getPlaytime();

    obj["name"] = sveditor::getPlayerAttribute("name");
    obj["farmName"] = sveditor::getPlayerAttribute("farmName");
    obj["favoriteThing"] = sveditor::getPlayerAttribute("favoriteThing");

    obj["currentMoney"] = sveditor::getPlayerAttribute("money");
    obj["moneyEarned"] = sveditor::getPlayerAttribute("totalMoneyEarned");

    obj["maxHealth"] = sveditor::getPlayerAttribute("maxHealth");
    obj["maxStamina"] = sveditor::getPlayerAttribute("maxStamina");

    obj["skills"]["farmingLevel"] = sveditor::getPlayerAttribute("farmingLevel");
    obj["skills"]["combatLevel"] = sveditor::getPlayerAttribute("combatLevel");
    obj["skills"]["miningLevel"] = sveditor::getPlayerAttribute("miningLevel");
    obj["skills"]["foragingLevel"] = sveditor::getPlayerAttribute("foragingLevel");
    obj["skills"]["fishingLevel"] = sveditor::getPlayerAttribute("fishingLevel");

    obj["skills"]["farmingExp"] = sveditor::getExperiencePoints("farming");
    obj["skills"]["combatExp"] = sveditor::getExperiencePoints("combat");
    obj["skills"]["miningExp"] = sveditor::getExperiencePoints("mining");
    obj["skills"]["foragingExp"] = sveditor::getExperiencePoints("foraging");
    obj["skills"]["fishingExp"] = sveditor::getExperiencePoints("fishing");

    obj["professions"] = sveditor::getProfession();

    return obj;
}