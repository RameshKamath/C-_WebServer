#include <iostream>

#include "crow_all.h"
using namespace std;
using namespace crow;

void sendFile(crow::response & res, string filename, string contentType){
    std::ifstream in("../public/" + filename, ifstream::in);
    if (in)
    {
        ostringstream contents;
        contents << in.rdbuf();
        in.close();
        res.code = 200;
        res.set_header("Content-Type", contentType);
        res.write(contents.str());
    }
    else
    {
        res.code = 404;
        res.write("<h1> 404 File not Found</h1>");
    }
    res.end();
}

void sendHtml(crow::response & res, string filename){
    sendFile(res, filename + ".html", "text/html");
}

void sendStyles(crow::response & res, string filename)
{
    sendFile(res, "styles/" + filename, "text/css");
}

void sendImages(crow::response & res, string filename)
{
    sendFile(res, "images/" +filename, "image/jpeg");
}

void sendScripts(crow::response & res, string filename)
{
    sendFile(res, "scripts/" + filename, "text/javascript");
}

int main(int argc, char** argv){
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([](const crow::request &req, crow::response & res) {
        sendHtml(res, "index");
    });
    CROW_ROUTE(app, "/about")
    ([](const crow::request &req, crow::response & res) {
        sendHtml(res, "about");
    });

    CROW_ROUTE(app, "/images/<string>")
    ([](const crow::request &req, crow::response & res, string filename) {
        sendImages(res, filename);
    });

    CROW_ROUTE(app, "/styles/<string>")
    ([](const crow::request &req, crow::response & res,string filename) {
        sendStyles(res, filename);
    });

    CROW_ROUTE(app, "/scripts/<string>")
    ([](const crow::request &req, crow::response & res,string filename) {
        sendScripts(res, filename);
    });

    char * port = getenv("PORT");

    uint16_t iPort = static_cast<uint16_t>(port!=NULL? stoi(port): 8080);

    std::cout <<"PORT = " << iPort << std::endl;

    app.port(iPort).multithreaded().run();
}