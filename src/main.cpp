#include "sveditor.cpp"
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
        return crow::mustache::load("pages/profile.html").render();
    });

    CROW_ROUTE(app, "/validate").methods("POST"_method)
    ([](const crow::request &req) {
        if (sveditor2::validateFile(req.body)) return 200;
        else return 403;
    });

    CROW_ROUTE(app, "/parse").methods("POST"_method)
    ([](const crow::request &req) {
        return crow::response(sveditor2::getFile(req.body));
    });

    CROW_ROUTE(app, "/edit").methods("POST"_method)
    ([](const crow::request &req) {
        crow::json::rvalue data = crow::json::load(req.body);
        return crow::response(sveditor2::editFile(data["file"].s(), data["data"]));
    });

    app.loglevel(crow::LogLevel::WARNING);
    app.port(18080).multithreaded().run();

    // g++ main.cpp -lpthread -lboost_system -lz -o ../build/sveditor.out
}