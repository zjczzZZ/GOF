#include <iostream>

#include "PluginBase/PluginManager.h"

using namespace std;

int main() {
    PluginManager* plugin = PluginManager::GetInstance();
    plugin->Init();
    plugin->Register();
    plugin->Run();
    plugin->Reset();
}