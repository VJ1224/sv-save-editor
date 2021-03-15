# Stardew Valley Save Editor

A save editor for Stardew Valley on PC.

## Usage

Upload the XML save file (not SaveGameInfo, the full file) and edit the attributes that you would like to change.

## Requirements

* Docker

## Files

* main.cpp: web service, uses crowcpp

* sveditor.cpp: read/write the XML file, uses tinyxml2

* pages: HTML pages

* static: static files such as CSS and images.

## Run

* docker build --tag sveditor:latest .
* docker run -td -p 18080:18080 sveditor
* Navigate to port 18080 on localhost

[Live](http://142.93.214.88:18080/)

## Credits:

* C++ microframework for running web services 

    [CrowCPP](https://github.com/CrowCpp/crow)

* XML parser

    [TinyXML2](https://github.com/leethomason/tinyxml2)