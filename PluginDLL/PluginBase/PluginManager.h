#pragma once
#include <dlfcn.h>

#include <fstream>
#include <iostream>
#include <string>

#include "PluginBase.h"

class PluginManager {
public:
    static PluginManager* GetInstance() {
        static PluginManager pm;
        return &pm;
    }

    void Init();

    void Register();

    void Run();

    void Reset();

private:
    void ReadConfig();

private:
    PluginBase* _impl;
    std::string _dllpath;
};