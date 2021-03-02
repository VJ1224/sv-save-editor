#include "sveditor.cpp"
#include "tools.hpp"
#include "json.hpp"

int main() {
    sveditor::getFile();
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

    std::cout << obj << std::endl;
}