#pragma once

class PluginBase {
public:
    PluginBase() {}
    virtual ~PluginBase() {}

    virtual void Init() {}

    virtual void Register() {}

    virtual void Run() {}

    virtual void Reset() {}
};