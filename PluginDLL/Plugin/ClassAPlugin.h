#pragma once

#include "../PluginBase/PluginBase.h"

class ClassA : public PluginBase {
public:
    void Init();

    void Register();

    void Run();

    void Reset();
};

extern "C" {
PluginBase* GetInstance() {
    static ClassA ca;
    return &ca;
}
}