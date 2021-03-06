# Stardew Valley Save Editor

A save editor for Stardew Valley on PC.

## Usage

Upload the XML save file (not SaveGameInfo, the full file) and edit the attributes that you would like to change.

## Requirements

* C++ compiler

## Files

* main.cpp: web backend, uses crowcpp

* sveditor.cpp: interact with the XML file, uses tinyxml2

* tools.hpp: helper methods

* pages: HTML pages

* static: static files such as CSS and images.

## Run

* Release: g++ main.cpp -lpthread -lboost_system -lz -o sveditor.out
* Debug: g++ main.cpp -ggdb -lpthread -lboost_system -lz -D CROW_ENABLE_DEBUG -o sveditor.out


## Credits:

* C++ microframework for running web services 

    [CrowCPP](https://github.com/CrowCpp/crow)

* XML parser

    [TinyXML2](https://github.com/leethomason/tinyxml2)