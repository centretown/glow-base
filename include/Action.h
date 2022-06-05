// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

template <class T>
class Action
{
protected:
    T &settings;

public:
    Action(T &settings) : settings(settings) {}
    ~Action() {}

    virtual void Setup() {}
    virtual void Tick() {}
    virtual void Reset() {}
    inline T &Settings() { return settings; }
};
