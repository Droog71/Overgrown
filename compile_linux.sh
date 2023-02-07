#! /bin/bash
g++ main.cpp $PWD/src/*.cpp -Iinclude -o Overgrown -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lstdc++fs -ggdb -v
