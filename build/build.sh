#!/bin/bash

cd /usr/svsaveeditor/src
g++ main.cpp -lpthread -lboost_system -lz -o sveditor
./sveditor