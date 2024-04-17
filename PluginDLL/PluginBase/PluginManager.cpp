#include "PluginManager.h"

void PluginManager::Init() {
    ReadConfig();

    void* handle;
    handle = dlopen(_dllpath.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cout << "load dll falure" << std::endl;
        return;
    }

    PluginBase* (*func)();
    auto dllfunc = dlsym(handle, "GetInstance");
    if (!dllfunc) {
        std::cout << "load dll func falure" << std::endl;
        return;
    }

    func = reinterpret_cast<PluginBase* (*)()>(dllfunc);
    _impl = func();
    if (!_impl) {
        return;
    }
    _impl->Init();
}

void PluginManager::Register() {
    if (_impl) {
        _impl->Register();
    }
}

void PluginManager::Run() {
    if (_impl) {
        _impl->Run();
    }
}

void PluginManager::Reset() {
    if (_impl) {
        _impl->Reset();
    }
}

void PluginManager::ReadConfig() {
    std::ifstream Rfile;
    Rfile.open("config.txt", std::ios::in);
    if (!Rfile.is_open()) {
        return;
    }
    Rfile >> _dllpath;
    Rfile.close();
}
