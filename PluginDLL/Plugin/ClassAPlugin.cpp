#include "ClassAPlugin.h"

#include <fstream>
#include <iostream>
void ClassA::Init() {
    std::ifstream rfile;
    rfile.open("config.txt", std::ios::in);
    if (rfile.is_open()) {
        std::string str;
        rfile >> str;
        std::cout << str << std::endl;
        rfile.close();
    } else {
        std::cout << "A Init" << std::endl;
    }
    std::cout << "A Init" << std::endl;
}

void ClassA::Register() {
    std::cout << "A Register" << std::endl;
}

void ClassA::Run() {
    std::cout << "A Run" << std::endl;
}

void ClassA::Reset() {
    std::cout << "A Reset" << std::endl;
}
